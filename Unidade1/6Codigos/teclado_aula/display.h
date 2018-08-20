
#ifndef _UTIL_
#define _UTIL_
#include <stdint.h>

#define HABILITA_DISPLAY0 PIN3_25
#define HABILITA_DISPLAY1 PIN3_26
#define HABILITA_DISPLAY2 PIN4_28
#define HABILITA_DISPLAY3 PIN4_29


void display_configura (void);
void display_7seg (uint16_t numero);

#endif
