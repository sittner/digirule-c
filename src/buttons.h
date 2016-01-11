#ifndef _BUTTONS_H
#define _BUTTONS_H

#include "digirule.h"

#define LogicInputA    (1 << 0)
#define LogicInputB    (1 << 1)
#define LogicSelect    (1 << 2)
#define FlipFlopSJTD   (1 << 3)
#define FlipFlopClock  (1 << 4)
#define FlipFlopRK     (1 << 5)
#define FlipFlopSelect (1 << 6)
#define CounterUp      (1 << 7)
#define CounterDown    (1 << 8)

extern uint16_t btn_state;
extern uint16_t btn_pressed;
extern uint16_t btn_released;

extern void btn_init(void);
extern void btn_update(void);

#endif
