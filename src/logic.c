#include "logic.h"
#include "counter.h"
#include "buttons.h"
#include "leds.h"

typedef enum {
  logicNOT = 0,
  logicOR,
  logicAND,
  logicXOR,
  logicNOR,
  logicNAND,
  logicNXOR,
  LOGIC_FUNCTION_COUNT
} LOGIC_FUNCTION_T;

static LOGIC_FUNCTION_T function;
static uint8_t in_a;
static uint8_t in_b;

void logic_init(void) {
  function = logicNOT;
  in_a = 0;
  in_b = 0;
}

static void select_function(void) {
  if (btn_pressed & LogicSelect) {
    function++;
    if (function >= LOGIC_FUNCTION_COUNT) {
      function = 0;
    }
  }
}

void logic_task(void) {
  uint8_t out = 0;

  // gate select
  select_function();
  if (btn_pressed & LogicSelect) {
    in_a = 0;
    in_b = 0;
  }

  // toggle inputs
  if (btn_pressed & LogicInputA) {
    in_a = !in_a;
  }
  if (btn_pressed & LogicInputB) {
    in_b = !in_b;
  }
  
  // calculate output
  switch (function) {
    case logicNOT:
      in_b = 0;
      out = !in_a;
      break;
    case logicOR:
      out = in_a || in_b;
      break;
    case logicAND:
      out = in_a && in_b;
      break;
    case logicXOR:
      out = (in_a && !in_b) || (!in_a && in_b);
      break;
    case logicNOR:
      out = !(in_a || in_b);
      break;
    case logicNAND:
      out = !(in_a && in_b);
      break;
    case logicNXOR:
      out = !((in_a && !in_b) || (!in_a && in_b));
      break;
  }

  // update display
  led_single(LogicInputALED, in_a);
  led_single(LogicInputBLED, in_b);
  led_select(LED_LOGIC_FNK, function);
  led_single(LogicGatesXLED, out);
}

void logic_4bit_task(void) {
  uint8_t out = 0;

  // update counter
  counter_task(false);

  // gate select
  select_function();

  // set inputs
  if (btn_pressed & LogicInputA) {
    in_a = counter_value;
  }
  if (btn_pressed & LogicInputB) {
    in_b = counter_value;
  }
  
  // calculate output
  switch (function) {
    case logicNOT:
      out = in_a ^ 0x0f;
      break;
    case logicOR:
      out = in_a | in_b;
      break;
    case logicAND:
      out = in_a & in_b;
      break;
    case logicXOR:
      out = in_a ^ in_b;
      break;
    case logicNOR:
      out = (in_a | in_b) ^ 0x0f;
      break;
    case logicNAND:
      out = (in_a & in_b) ^ 0x0f;
      break;
    case logicNXOR:
      out = (in_a ^ in_b) ^ 0x0f;
      break;
  }

  // update display
  led_select(LED_LOGIC_FNK, function);
  led_binary(LED_FFLOP_BIN, out);
}

