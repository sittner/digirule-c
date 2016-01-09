#include "counter.h"
#include "buttons.h"
#include "leds.h"

static const uint8_t graycode[] = {
  0b0000, 0b0001, 0b0011, 0b0010,
  0b0110, 0b0111, 0b0101, 0b0100,
  0b1100, 0b1101, 0b1111, 0b1110,
  0b1010, 0b1011, 0b1001, 0b1000
};

uint8_t counter_value;

void counter_init(void) {
  counter_value = 0;
}

void counter_task(bool gray) {
  // check for buttons
  if (btn_pressed & CounterUp) {
    counter_value++;
  }
  if (btn_pressed & CounterDown) {
    counter_value--;
  }

  // limit value to 4 bit
  counter_value &= 0x0f;

  // display value
  if (gray) {
    led_binary(LED_COUNTER, graycode[counter_value]);
  } else {
    led_binary(LED_COUNTER, counter_value);
  }
}

