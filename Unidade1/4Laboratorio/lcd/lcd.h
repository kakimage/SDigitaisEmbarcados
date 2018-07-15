
#ifndef _LCD_
#define _LCD_

#include "digital.h"

#define LCD_D0 PIN0_04
#define LCD_D1 PIN0_05
#define LCD_D2 PIN0_06
#define LCD_D3 PIN0_07
#define LCD_D4 PIN0_08
#define LCD_D5 PIN0_09
#define LCD_D6 PIN0_10
#define LCD_D7 PIN0_11

#define LCD_EN PIN2_13
#define LCD_RS PIN2_12

// Listagem de comandos
#define LCD_DISPLAY_CLEAR 1
#define LCD_ENTRY_MODE   0x6

#include <stddef.h>

int _write (int fd, const void *buf, size_t count);
int _read (int fd, const void *buf, size_t count);


void LCD_inicializa(void);
void LCD_escreve(char *st);
void LCD_limpa_tela(void);

#endif
