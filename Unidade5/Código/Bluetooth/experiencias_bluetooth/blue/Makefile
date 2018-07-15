

CC=avr-gcc

FLAGS= -g -Os -Wall -mcall-prologues -mmcu=atmega328p -DF_CPU=16000000UL 

LINKER= avr-objcopy

UPLOADER=avrdude 

final.hex: final.o
	$(LINKER)  -O ihex final.o final.hex

final.o: uart.o testa_blue.o digital.o  serial.o int_ext.o 
	$(CC) $(FLAGS) uart.o digital.o testa_blue.o serial.o int_ext.o  -o final.o


digital.o: digital.c digital.h
	$(CC) $(FLAGS) digital.c -c


testa_blue.o: testa_blue.c
	$(CC) $(FLAGS) testa_blue.c -c

serial.o: serial.c serial.h digital.o int_ext.o 
	$(CC) $(FLAGS) serial.c -c

uart.o: uart.c uart.h 
	$(CC) $(FLAGS) uart.c -c

int_ext.o:	int_ext.c int_ext.h
	$(CC) $(FLAGS) int_ext.c -c




clean:
	rm -f *.o *.hex *~

upload_UNO:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200  -U flash:w:final.hex


upload_2009:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 57600  -U flash:w:final.hex

