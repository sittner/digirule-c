#include "flipflop.h"
#include "buttons.h"
#include "leds.h"

typedef enum {
  ffSR = 0,
  ffJK,
  ffT,
  ffD,
  FF_FUNCTION_COUNT
} FF_FUNCTION_T;

static FF_FUNCTION_T function;
static bool in_sjtd;
static bool in_rk;
static bool out;
static bool out_not;

void flipflop_init(void) {
  function = ffSR;
  in_sjtd = false;
  in_rk = false;
  out = false;
  out_not = true;
}

void flipflop_task(void) {
  // type select
  if (btn_pressed & FlipFlopSelect) {
    function++;
    if (function >= FF_FUNCTION_COUNT) {
      function = 0;
    }
    in_sjtd = false;
    in_rk = false;
    out = false;
    out_not = true;
  }

  // toggle inputs
  if (btn_pressed & FlipFlopSJTD) {
    in_sjtd = !in_sjtd;
  }
  if (btn_pressed & FlipFlopRK) {
    in_rk = !in_rk;
  }

  // calculate output
  switch (function) {
    case ffSR:
      if (btn_pressed & FlipFlopClock) {
        if (!in_sjtd && in_rk) {
          out = false;
          out_not = true;
        }
        if (in_sjtd && !in_rk) {
          out = true;
          out_not = false;
        }
        if (in_sjtd && in_rk) {
          out = false;
          out_not = false;
        }
      }
      break;
    case ffJK:
      if (btn_pressed & FlipFlopClock) {
        if (!in_sjtd && in_rk) {
          out = false;
          out_not = true;
        }
        if (in_sjtd && !in_rk) {
          out = true;
          out_not = false;
        }
        if (in_sjtd && in_rk) {
          out = !out;
          out_not = !out_not;
        }
      }
      break;
    case ffT:
      in_rk = false;
      if (btn_pressed & FlipFlopClock) {
        if (in_sjtd) {
          out = !out;
          out_not = !out_not;
        }
      }
      break;
    case ffD:
      in_rk = false;
      if (btn_pressed & FlipFlopClock) {
        out = in_sjtd;
        out_not = !in_sjtd;
      }
      break;
  }

  // update display
  led_single(FlipFlopSJTDLED, in_sjtd);
  led_single(FlipFlopClockLED, btn_state & FlipFlopClock);
  led_single(FlipFlopRKLED, in_rk);
  led_select(LED_FFLOP_FNK, function);
  led_single(FlipFlopQLED, out);
  led_single(FlipFlopNOTQLED, out_not);
}

