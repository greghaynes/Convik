#ifndef CONVIK_BEMF_SENSE_H
#define CONVIK_BEMF_SENSE_H

#include "motor.h"

#include <avr/io.h>

void bemf_sense_init(void);

void bemf_sense_set_winding(uint8_t winding);

#endif

