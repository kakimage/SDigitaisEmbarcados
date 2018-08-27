#ifndef __DISPLAY__
#define __DISPLAY__

#include "digital.h"


#define ENABLE_DISP0 PIN_3_25
#define ENABLE_DISP1 PIN_3_26
#define ENABLE_DISP2 PIN_4_28
#define ENABLE_DISP3 PIN_4_29

#define SEGA PIN_0_04
#define SEGB PIN_0_05
#define SEGC PIN_0_06
#define SEGD PIN_0_07
#define SEGE PIN_0_08
#define SEGF PIN_0_09
#define SEGG PIN_0_10





void display_init(void);
void display(char c);

#endif