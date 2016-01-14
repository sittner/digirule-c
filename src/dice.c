#include "dice.h"
#include "buttons.h"
#include "leds.h"
#include "randgen2.h"

#define SPEED_DONE 100
#define SPEED_INC  5

static uint8_t speed;
static uint8_t timer;
static uint8_t val;

void dice_init(void) {
  speed = SPEED_DONE;
  timer = 0;
  val = 0;
}

void dice_task(bool decimal) {
  // check the InputB button this will start the dice rolling
  if (btn_state & LogicInputB) {
    speed = 0;
    timer = 0;
  }

  // roll the dice
  if (speed < SPEED_DONE) {
    if (timer < speed) {
      timer++;
    } else {
      speed += SPEED_INC;
      timer = 0;
      val = rand_get(6);
    }
  }

  // update display
  if (decimal) {
    led_select(LED_LOGIC_FNK, val);
  } else {
    led_binary(LED_COUNTER, val + 1);
  }
}

