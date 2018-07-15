#ifndef _UART_
#define _UART_
#include <stdio.h>

class HardwareSerial {

	public:
		HardwareSerial(void);  

};
extern HardwareSerial Serial;

extern FILE uart_output;
extern FILE uart_input ;
#endif
