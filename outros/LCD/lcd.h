
#ifndef __LCD__
#define __LCD__

#include "digital.h"

#define COMANDO 0
#define DADO    1

#define B0 PIN0_04
#define B1 PIN0_05
#define B2 PIN0_06
#define B3 PIN0_07
#define B4 PIN0_08
#define B5 PIN0_09
#define B6 PIN0_10
#define B7 PIN0_11

#define RS PIN2_12
#define E  PIN2_13

#define CONFIGURA_LCD    0x38
#define CONTROLE_DISPLAY 0x0F
#define CLS              0x01
#define FIXA             0x06


class meuLCD {

	private:
		void modo (int x);
	public:
		void init (void);
		void escreve (char *st);
		void escreve (char A);
		void clear(void);
		void gotoxy(int x, int y);
};

extern meuLCD LCD;
#endif
