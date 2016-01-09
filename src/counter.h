#ifndef _COUNTER_H
#define _COUNTER_H

#include "digirule.h"

extern uint8_t counter_value;

extern void counter_init(void);
extern void counter_task(bool gray);

#endif
