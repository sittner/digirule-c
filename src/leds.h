#ifndef _LEDS_H
#define _LEDS_H

#include "digirule.h"

typedef struct {
  volatile uint8_t *port;
  uint8_t mask;
} PORTPIN_T;

typedef enum {
  LogicInputALED = 0,
  LogicInputBLED,
  NOTGateLED,
  ORGateLED,
  ANDGateLED,
  XORGateLED,
  NORGateLED,
  NANDGateLED,
  XNORGateLED,
  LogicGatesXLED,
  FlipFlopSJTDLED,
  FlipFlopClockLED,
  FlipFlopRKLED,
  SRFlipFlopLED,
  JKFlipFlopLED,
  TFlipFlopLED,
  DFlipFlopLED,
  FlipFlopQLED,
  FlipFlopNOTQLED,
  Counter8LED,
  Counter4LED,
  Counter2LED,
  Counter1LED,
} LED_ENUM_T;

extern const PORTPIN_T LED_ALL[];
extern const PORTPIN_T LED_LOGIC_FNK[];
extern const PORTPIN_T LED_LOGIC_BIN[];
extern const PORTPIN_T LED_FFLOP_FNK[];
extern const PORTPIN_T LED_FFLOP_BIN[];
extern const PORTPIN_T LED_COUNTER[];

extern void led_single(LED_ENUM_T led, bool state);
extern void led_group(const PORTPIN_T *group, bool state);
extern void led_binary(const PORTPIN_T *group, uint8_t val);
extern void led_select(const PORTPIN_T *group, uint8_t val);
extern void led_rand(const PORTPIN_T *group, uint16_t entrophy);

#endif
