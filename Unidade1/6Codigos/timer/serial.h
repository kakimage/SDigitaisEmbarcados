#ifndef _SERIAL_
#define _SERIAL_
#include <stdint.h>
#include <stddef.h>
#include "LPC17xx.h"
void mensagem (char *st);

void serial_envia_letra(char c);
void serial_configura (void);
int _write (int fd, const void *buf, size_t count);

#endif

