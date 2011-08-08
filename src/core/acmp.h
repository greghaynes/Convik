#ifndef CONVIK_ACMP_H
#define CONVIK_ACMP_H

#include <avr/io.h>

typedef void(*acmp_handler)(void);

/* Must be called before using the analog comparator */
void acmp_init(void);

void acmp_set_handler(acmp_handler handler);

#endif

