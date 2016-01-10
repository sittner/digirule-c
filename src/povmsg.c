#include "povmsg.h"
#include "buttons.h"
#include "leds.h"

#define SYM_END 0xff

#define SYM_BORDER \
  0, 0, 0, 0, 0, 0, 0, 0, \
  0, 0, 0, 0, 0, 0, 0, 0, \
  0, 0, 0, 0, 0, 0, 0, 0, \
  0, 0, 0, 0, 0, 0, 0, 0

#define SYM_WAVE \
  0b0000100, \
  0b0000010, \
  0b0000001, \
  0b0000001, \
  0b0000001, \
  0b0000001, \
  0b0000001, \
  0b0000001, \
  0b0000001, \
  0b0000001, \
  0b0000001, \
  0b0000010, \
  0b0000110, \
  0b0001000, \
  0b0010000, \
  0b0110000, \
  0b0100000, \
  0b0100000, \
  0b0100000, \
  0b0100000, \
  0b0100000, \
  0b0010000, \
  0b0011000

#define SYM_SMILE \
  0b0111110, \
  0b1000001, \
  0b1101001, \
  0b1000101, \
  0b1000101, \
  0b1101001, \
  0b1000001, \
  0b0111110

#define SYM_SPACE \
  0b0000000, \
  0b0000000

#define SYM_EXCLAM \
  0b0111101, \
  0b0111101, \
  0b0000000

#define SYM_T \
  0b0110000, \
  0b0100001, \
  0b0111111, \
  0b0111111, \
  0b0100001, \
  0b0110000, \
  0b0000000

#define SYM_H \
  0b0100001, \
  0b0111111, \
  0b0111111, \
  0b0001000, \
  0b0111111, \
  0b0111111, \
  0b0100001, \
  0b0000000

#define SYM_E \
  0b0100001, \
  0b0111111, \
  0b0111111, \
  0b0101001, \
  0b0101001, \
  0b0110011, \
  0b0000000

#define SYM_D \
  0b0100001, \
  0b0111111, \
  0b0111111, \
  0b0100001, \
  0b0100001, \
  0b0111111, \
  0b0011110, \
  0b0000000

#define SYM_I \
  0b0100001, \
  0b0111111, \
  0b0111111, \
  0b0100001, \
  0b0000000

#define SYM_G \
  0b0011110, \
  0b0111111, \
  0b0100001, \
  0b0100111, \
  0b0110111, \
  0b0000100, \
  0b0000000

#define SYM_R \
  0b0100001, \
  0b0111111, \
  0b0111111, \
  0b0100100, \
  0b0111111, \
  0b0011011, \
  0b0000001

#define SYM_U \
  0b0100000, \
  0b0111110, \
  0b0111111, \
  0b0000001, \
  0b0100001, \
  0b0111110, \
  0b0100000, \
  0b0000000

#define SYM_L \
  0b0100001, \
  0b0111111, \
  0b0111111, \
  0b0100001, \
  0b0000011, \
  0b0000000

#define SYM_S \
  0b0011001, \
  0b0111101, \
  0b0101101, \
  0b0101111, \
  0b0100110, \
  0b0000000

static const uint8_t msg_wave[] = {
  SYM_WAVE,
  SYM_END
};

static const uint8_t msg_text[] = {
  SYM_BORDER,
  SYM_T,
  SYM_H,
  SYM_E,
  SYM_SPACE,
  SYM_D,
  SYM_I,
  SYM_G,
  SYM_I,
  SYM_R,
  SYM_U,
  SYM_L,
  SYM_E,
  SYM_SPACE,
  SYM_R,
  SYM_U,
  SYM_L,
  SYM_E,
  SYM_S,
  SYM_EXCLAM,
  SYM_BORDER,
  SYM_END
};

static const uint8_t msg_smile[] = {
  SYM_SPACE,
  SYM_SMILE,
  SYM_SPACE,
  SYM_END
};

static const uint8_t * msg_tab[] = {
  msg_wave,
  msg_text,
  msg_smile,
  0
};

static const uint8_t **msg;
static const uint8_t *pos;

void povmsg_init(void) {
  msg = msg_tab;
  pos = *msg;
}

void povmsg_task(void) {
  if (*pos == SYM_END) {
    pos = *msg;
  }
  led_binary(LED_LOGIC_BIN, *pos);
  pos++;

  if (btn_pressed & LogicInputB) {
    msg++;
    if (*msg == 0) {
      msg = msg_tab;
    }
    pos = *msg;
  }
}

