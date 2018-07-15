

CC=avr-gcc

FLAGS=   -O2 -Wall -mcall-prologues -mmcu=atmega328p -DF_CPU=16000000UL 

LINKER= avr-objcopy

UPLOADER=avrdude 

final_mesa.hex: final_mesa.o final_servidor.o
	$(LINKER)  -O ihex final_mesa.o     final_mesa.hex
	$(LINKER)  -O ihex final_servidor.o final_servidor.hex

final_servidor.o:   interrupcao_externa.o nrf24.o servidor.o spi.o   digital.o uart.o
	$(CC) $(FLAGS)  interrupcao_externa.o nrf24.o servidor.o spi.o   digital.o uart.o -o final_servidor.o

final_mesa.o:   interrupcao_externa.o nrf24.o mesa.o spi.o   digital.o uart.o
	$(CC) $(FLAGS)  interrupcao_externa.o nrf24.o mesa.o spi.o   digital.o uart.o -o final_mesa.o

interrupcao_externa.o: interrupcao_externa.c 
	$(CC) $(FLAGS) interrupcao_externa.c -c

mesa.o: mesa.c delay.h  nrf24.o   uart.o spi.o digital.o
	$(CC) $(FLAGS) mesa.c -c

servidor.o: servidor.c delay.h  nrf24.o   uart.o spi.o digital.o
	$(CC) $(FLAGS) servidor.c -c

	
spi.o:	spi.c delay.h digital.o spi.h
	$(CC) $(FLAGS) spi.c -c

nrf24.o:	 spi.o delay.h  nrf24.c nrf24.h
	$(CC) $(FLAGS) nrf24.c -c



uart.o: uart.c 
	$(CC) $(FLAGS) uart.c -c

digital.o: digital.c digital.h
	$(CC) $(FLAGS) digital.c -c

clean:
	rm -f *.o *.hex *~

upload_2009:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 57600  -U flash:w:final.hex

upload_mesa:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200  -U flash:w:final_mesa.hex

upload_servidor:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200  -U flash:w:final_servidor.hex
