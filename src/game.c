#include "game.h"
#include "buttons.h"
#include "leds.h"

static uint8_t level;
static uint8_t timer;
static uint8_t pos;
static int8_t dir;

void game_init(void) {
  level = 0;
  timer = 0;
  pos = 0;
  dir = 0;
}

void game_task(void) {
  if (timer == 0) {
    // the higher the number, the slower the game speed it
    // keeps decreasing the number and increasing the
    // speed the more points you get.
    timer = 200 - (level * 10);

    // go to next position
    pos += dir;
    if (pos == 0) {
      dir = 1;
    }
    if (pos == 6) {
      dir = -1;
    }
  }

  timer--;

  // check the logic input B button which is our HIT button
  if (btn_pressed & LogicInputB) {
    // this means we have a hit!
    if (pos == 3) {
      if (level < 15) {
        level++;
      }
    } else {
      level = 0;
    }
  }

  // update display
  led_select(LED_LOGIC_FNK, pos);
  led_binary(LED_COUNTER, level);
}

