#include "buttons.h"

const PORTPIN_T BTN_ALL[] = {
  { &PORTB, (1 << 1) },
  { &PORTB, (1 << 2) },
  { &PORTB, (1 << 3) },
  { &PORTB, (1 << 4) },
  { &PORTB, (1 << 5) },
  { &PORTB, (1 << 6) },
  { &PORTB, (1 << 7) },
  { &PORTA, (1 << 1) },
  { &PORTA, (1 << 0) },
  { 0, 0 }
};

#define DEBOUNCE_TIME 20

uint16_t btn_state = 0;
uint16_t btn_pressed = 0;
uint16_t btn_released = 0;

static uint8_t debounce = 0;

void btn_update(void) {
  const PORTPIN_T *btn;
  uint16_t mask, old;

  if (debounce > 0) {
    debounce--;
    btn_pressed = 0;
    btn_released = 0;
    return;
  }
  debounce = DEBOUNCE_TIME - 1;

  old = btn_state;
  btn_state = 0;

  for (btn = BTN_ALL, mask = 1; btn->port; btn++, mask <<= 1) {
    if (*btn->port & btn->mask) {
      btn_state |= mask;
    }
  }

  btn_pressed = btn_state & ~old;
  btn_released = ~btn_state & old;
}

