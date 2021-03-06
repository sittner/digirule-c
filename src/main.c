#include "digirule.h"
#include "leds.h"
#include "buttons.h"
#include "logic.h"
#include "flipflop.h"
#include "counter.h"
#include "shiftreg.h"
#include "povmsg.h"
#include "dice.h"
#include "game.h"

// Setup config options
#pragma config FOSC = INTIO67
#pragma config BOREN = 2 // brown-out disabled in sleep mode
#pragma config BORV = 3 // brown-out voltage 1.8V
#pragma config PWRT = ON
#pragma config WDTEN = OFF
#pragma config MCLRE = OFF
#pragma config XINST = OFF
#pragma config LVP = OFF // use PORTB5 as IO

typedef enum {
  // user modes
  modeSelect = 0,
  modeDefault,
  modeGrayCnt,
  modeSparkle,
  modeShiftReg,
  modeLightTest,
  modePOV,
  modeBinDice,
  modeGame,
  mode4BitLogic,
  modeDecDice,
  MODE_COUNT,
} MODE_T;

static MODE_T select;
static MODE_T mode;

#define SPARKLE_DELAY_INC  10
#define SPARKLE_DELAY_DFLT 20
#define SPARKLE_DELAY_MAX  250

static uint8_t sparkle_delay;
static uint8_t sparkle_timer;

#define SELECT_TIMEOUT  2000
#define IDLE_TIMEOUT   60000

#define WAKEUP_BUTTON  (PORTB & (1 << 1))

static uint16_t select_timer;
static uint16_t off_timer;
static uint16_t idle_timer;
static bool off_flag;

static void init_all(void) {
  led_group(LED_ALL, false);
  logic_init();
  flipflop_init();
  counter_init();
  shiftreg_init();
  povmsg_init();
  dice_init();
  game_init();
  select = modeDefault;
  mode = modeDefault;
  sparkle_delay = SPARKLE_DELAY_DFLT;
  sparkle_timer = 0;
  select_timer = 0;
  off_timer = 0;
  idle_timer = 0;
}

static void check_select(void) {
  if ((btn_state & LogicInputA) == 0) {
    select_timer = 0;
    return;
  }

  if (select_timer < SELECT_TIMEOUT) {
    select_timer++;
    return;
  }

  init_all();
  mode = modeSelect;
}

static void check_off(void) {
  if ((btn_state & LogicInputB) == 0) {
    off_timer = 0;
    return;
  }

  if (off_timer < SELECT_TIMEOUT) {
    off_timer++;
    return;
  }

  off_timer = 0;
  off_flag = true;
}

static void check_idle(void) {
  if (btn_pressed) {
    idle_timer = 0;
    return;
  }

  if (idle_timer < IDLE_TIMEOUT) {
    idle_timer++;
    return;
  }

  idle_timer = 0;
  off_flag = true;
}

static void switch_off(void) {
  // stop TIMER2
  TMR2ON = 0;
  TMR2 = 0;

  // all LEDs off
  led_group(LED_ALL, false);

  // enable sleep mode
  IDLEN = 0;

  do {
    // go to sleep till wakeup IRQ
    INT1IE = 1;
    Sleep();

    // filter out glitches
    __delay_ms(20);
  } while (!WAKEUP_BUTTON);

  // disable sleep mode
  IDLEN = 1;

  // initialize button state
  btn_init();

  // reenable TIMER2
  TMR2ON = 1;

  // reset idle timer
  idle_timer = 0;
}

static void mode_select(void) {
  // select mode
  if ((btn_pressed & CounterUp) && (select < (MODE_COUNT - 1))) {
    select++;
  }
  if ((btn_pressed & CounterDown) && (select > modeDefault)) {
    select--;
  }

  // display on counter LEDs
  led_binary(LED_COUNTER, select);

  // enter mode
  if (btn_pressed & LogicInputB) {
    led_group(LED_ALL, false);
    mode = select;
  }
}

static void sparkle_leds(void) {
  uint8_t i;

  // sparkle LEDs
  if (sparkle_timer > 0) {
    sparkle_timer--;
  } else {
    sparkle_timer = sparkle_delay;
    led_rand(LED_ALL, 50);
  }

  // change speed
  if ((btn_pressed & CounterUp) && (sparkle_delay >= SPARKLE_DELAY_INC)) {
    sparkle_delay -= SPARKLE_DELAY_INC;
  }
  if ((btn_pressed & CounterDown) && (sparkle_delay <= (SPARKLE_DELAY_MAX - SPARKLE_DELAY_INC))) {
    sparkle_delay += SPARKLE_DELAY_INC;
  }
}

// Interrupt Service Routine
void interrupt ISR() {
  // timer IRQ
  if (TMR2IF) {
    TMR2IF = 0;
  }

  // button wake up IRQ
  if (INT1IF) {
    INT1IE = 0;
    INT1IF = 0;
  }
}

// Start Of Program - this is where we setup everything before getting into the main loop
void main(void) {
  // Oscillator setup
  OSCCON = 0b11100000;          // device enters idle on Sleep(), 8Mhz Clock,
  OSCTUNE = 0b00000000;         // Internal oscillator low freq comes from 31Khz clock from LFINTOSC, PLL disabled

  // Analog / Digital pins setup
  ANSEL = 0b00000000;          // disable all analog inputs (make them all digital) must do this!
  ANSELH = 0b00000000;         // disable all analog inputs (make them all digital) must do this!

  // Tristate setup
  TRISA = 0b00000011;
  TRISB = 0b11111110;
  TRISC = 0b00000000;
  TRISD = 0b00000000;
  TRISE = 0b00000000;

  // configure TIMER2:
  // prescaler 16, period register for 1ms, timer stopped 
  T2CON = 0b00000010;
  TMR2 = 0;
  PR2 = _XTAL_FREQ / 1000 / 16 / 4;

  // initialize subsystems
  btn_init();
  init_all();

  // disable INT1, config for raising endge
  INT1IE = 0;
  INTEDG1 = 1;

  // enable interrupts
  TMR2IE = 1;  // TIMER2 interrupt
  PEIE = 1;    // peripheral interrupt
  GIE = 1;     // global interrupt enable

  // start TIMER2
  TMR2ON = 1;

  // main loop
  while (true) {
    off_flag = false;

    // go to idle and wait for timer
    Sleep();

    // read button inputs
    btn_update();

    // check for commands
    check_select();
    check_off();
    check_idle();

    // execute mode task
    switch (mode) {
      case modeSelect:
        mode_select();
        break;
      case modeSparkle:
        sparkle_leds();
        break;
      case modeShiftReg:
        shiftreg_task();
        break;
      case modeLightTest:
        led_group(LED_ALL, true);
        break;
      case modePOV:
        povmsg_task();
        break;
      case modeBinDice:
      case modeDecDice:
        dice_task(mode == modeDecDice);
        break;
      case modeGame:
        game_task();
        break;
      case mode4BitLogic:
        logic_4bit_task();
        break;
      default:
        logic_task();
        flipflop_task();
        counter_task(mode == modeGrayCnt);
    }

    if (off_flag) {
      switch_off();
    }
  }
}

