#include "shiftreg.h"
#include "buttons.h"
#include "leds.h"

static bool in;
static uint8_t reg;

void shiftreg_init(void) {
  in = false;
  reg = 0;
}

void shiftreg_task(void) {
  // check input A button (this is the data input)
  if (btn_pressed & LogicInputA) {
    in = !in;
  }

  // check input B button (this is the reset input)
  if (btn_pressed & LogicInputB) {
    reg = 0;
  }

  // check the change gate button  (this is now our shift register clock)
  if (btn_pressed & LogicSelect) {
    reg = (reg << 1) | (in ? 1 : 0);
  }

  // update display
  led_single(LogicInputALED, in);
  led_binary(LED_LOGIC_FNK, reg);
}

