#include "leds.h"
#include "randgen2.h"

const PORTPIN_T LED_ALL[] = {
  { &PORTA, (1 << 2) },
  { &PORTA, (1 << 3) },
  { &PORTA, (1 << 4) },
  { &PORTA, (1 << 5) },
  { &PORTA, (1 << 6) },
  { &PORTA, (1 << 7) },
  { &PORTE, (1 << 0) },
  { &PORTE, (1 << 1) },
  { &PORTE, (1 << 2) },
  { &PORTC, (1 << 0) },
  { &PORTC, (1 << 1) },
  { &PORTC, (1 << 2) },
  { &PORTC, (1 << 3) },
  { &PORTC, (1 << 4) },
  { &PORTC, (1 << 5) },
  { &PORTD, (1 << 0) },
  { &PORTD, (1 << 1) },
  { &PORTD, (1 << 2) },
  { &PORTD, (1 << 3) },
  { &PORTD, (1 << 4) },
  { &PORTD, (1 << 5) },
  { &PORTD, (1 << 6) },
  { &PORTD, (1 << 7) },
  { 0, 0 }
};

const PORTPIN_T LED_LOGIC_FNK[] = {
  { &PORTA, (1 << 4) },
  { &PORTA, (1 << 5) },
  { &PORTA, (1 << 6) },
  { &PORTA, (1 << 7) },
  { &PORTE, (1 << 0) },
  { &PORTE, (1 << 1) },
  { &PORTE, (1 << 2) },
  { 0, 0 }
};

const PORTPIN_T LED_LOGIC_BIN[] = {
  { &PORTE, (1 << 2) },
  { &PORTE, (1 << 1) },
  { &PORTE, (1 << 0) },
  { &PORTA, (1 << 7) },
  { &PORTA, (1 << 6) },
  { &PORTA, (1 << 5) },
  { &PORTA, (1 << 4) },
  { 0, 0 }
};

const PORTPIN_T LED_FFLOP_FNK[] = {
  { &PORTC, (1 << 4) },
  { &PORTC, (1 << 5) },
  { &PORTD, (1 << 0) },
  { &PORTD, (1 << 1) },
  { 0, 0 }
};

const PORTPIN_T LED_FFLOP_BIN[] = {
  { &PORTD, (1 << 1) },
  { &PORTD, (1 << 0) },
  { &PORTC, (1 << 5) },
  { &PORTC, (1 << 4) },
  { 0, 0 }
};

const PORTPIN_T LED_COUNTER[] = {
  { &PORTD, (1 << 7) },
  { &PORTD, (1 << 6) },
  { &PORTD, (1 << 5) },
  { &PORTD, (1 << 4) },
  { 0, 0 }
};

static void set_led(const PORTPIN_T *led, bool state) {
  if (state) {
    *led->port |= led->mask;
  } else {
    *led->port &= ~led->mask;
  }
}

void led_single(LED_ENUM_T idx, bool state) {
  set_led(&LED_ALL[idx], state);
}

void led_group(const PORTPIN_T *group, bool state) {
  while (group->port) {
    set_led(group, state);
    group++;
  }
}

void led_binary(const PORTPIN_T *group, uint8_t val) {
  while (group->port) {
    set_led(group, val & 1);
    group++;
    val >>= 1;
  }
}

void led_select(const PORTPIN_T *group, uint8_t val) {
  while (group->port) {
    set_led(group, val == 0);
    group++;
    val--;
  }
}

void led_rand(const PORTPIN_T *group, uint16_t entrophy) {
  rand_set_max(entrophy);
  while (group->port) {
    set_led(group, rand_get() == 0);
    group++;
  }
}

