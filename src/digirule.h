#ifndef _DIGIRULE_H
#define _DIGIRULE_H

#include <pic18.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
  volatile uint8_t *port;
  uint8_t mask;
} PORTPIN_T;

#endif

