

CC=avr-gcc

FLAGS= -g -Os -Wall -mcall-prologues -mmcu=atmega328p -DF_CPU=16000000UL 

LINKER= avr-objcopy

UPLOADER=avrdude 

final.hex: final.o
	$(LINKER)  -O ihex final.o final.hex

final.o: uart.o digital.o spi.o testa_nrf.o
	$(CC) $(FLAGS) uart.o digital.o spi.o testa_nrf.o -o final.o


spi.o: spi.c spi.h
	$(CC) $(FLAGS) spi.c -c

uart.o: uart.c uart.h
	$(CC) $(FLAGS) uart.c -c

digital.o: digital.c digital.h
	$(CC) $(FLAGS) digital.c -c

testa_nrf.o: uart.o testa_nrf.c spi.o
	$(CC) $(FLAGS) testa_nrf.c -c


clean:
	rm -f *.o *.hex

upload:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200  -U flash:w:final.hex


