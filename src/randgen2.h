/****************************************************************************
*  Name    : randgen2.h                                                     *
*  Author  : Ahmed Lazreg (Octal)                                           *
*            octal@pocketmt.com   http://www.pocketmt.com                   *
*  Notice  : Copyright (c) 2007                                             *
*          : All Rights Reserved                                            *
*  Date    : 06/10/2007                                                     *
*  Version : 1.0                                                            *
*                                                                           *
*  Notes   : A Rudimentary Pseudo Random Number Generator (Modulo based)    *
*                                                                           *
*  Usage   : Call Initialize() to initialize the Initial value of the       *
*            generator. The generator gives better values when the initial  *
*            seed value is a Prime Number.                                  *
*            For the same Initial Seed, you will get the same serie of      *
*            generated values. This let you repeat some experiences (and    *
*            this is why it's called a PSEUDO-random number generator.      *
*            If you need an automatic different initial value each time you *
*            start the number generator, you can set the initial value to   *
*            the read of an ADC value on a FLOATING Analog PIN of a PIC.    *
*            Call Rand() to get/generate a new random value                 *
*                                                                           *
*            You can try to change the Magic Values to change the           *
*            Pseudo-Random Number Generator Behaviour                       *
*                                                                           *
****************************************************************************/

#ifndef _RANDGEN2_H
#define _RANDGEN2_H

#include <stdint.h>

void rand_init(uint32_t init_seed);
void rand_set_max(uint16_t val);
uint16_t rand_get(void);

#endif


