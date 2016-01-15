/***************************************************************************
* This is a 16 bit Galois linear feedback shift register                   *
* https://en.wikipedia.org/wiki/Linear_feedback_shift_register             *
****************************************************************************/

#include "randgen.h"

static uint16_t seed = 0xed25;

/***************************************************************************
* Name    : rand_get()                                                     *
* Purpose : Return a new Pseudo Random Number each time called             *
****************************************************************************/
uint8_t rand_get(uint8_t max) {
   seed = (seed >> 1) ^ (-(seed & 1) & 0xb400);
   return (seed >> 8) % max;
}

