

CC=avr-g++

FLAGS=  -fpermissive -Os -Wall -mcall-prologues -mmcu=atmega328p -DF_CPU=16000000UL 

LINKER= avr-objcopy

UPLOADER=avrdude 

transmite.hex: transmite.o recebe.o
	$(LINKER)  -O ihex transmite.o transmite.hex
	$(LINKER)  -O ihex recebe.o recebe.hex

transmite.o:   mensagens.o nrf24.o main_transmite.o spi.o   digital.o uart.o
	$(CC) $(FLAGS) mensagens.o nrf24.o main_transmite.o spi.o   digital.o uart.o -o transmite.o

recebe.o:   mensagens.o nrf24.o main_recebe.o spi.o   digital.o uart.o
	$(CC) $(FLAGS) mensagens.o nrf24.o main_recebe.o spi.o   digital.o uart.o -o recebe.o

main_transmite.o: mensagens.o nrf24.o  digital.o  main_transmite.cpp nrf24.o uart.o
	$(CC) $(FLAGS) main_transmite.cpp -c

main_recebe.o: mensagens.o nrf24.o   digital.o main_recebe.cpp nrf24.o uart.o
	$(CC) $(FLAGS) main_recebe.cpp -c



filas.o: filas.cpp filas.h
	$(CC) $(FLAGS) filas.cpp -c

mensagens.o:	mensagens.cpp mensagens.h
	$(CC) $(FLAGS) mensagens.cpp -c
	
spi.o:	spi.cpp digital.o spi.h
	$(CC) $(FLAGS) spi.cpp -c

nrf24.o:	mensagens.o spi.o  nrf24.cpp nrf24.h
	$(CC) $(FLAGS) nrf24.cpp -c

int_ext.o: int_ext.cpp int_ext.h 
	$(CC) $(FLAGS) int_ext.cpp -c

#int_tempo.o: int_tempo.cpp int_tempo.h 
#	$(CC) $(FLAGS) int_tempo.cpp -c

uart.o: uart.cpp 
	$(CC) $(FLAGS) uart.cpp -c

digital.o: digital.cpp digital.h
	$(CC) $(FLAGS) digital.cpp -c

clean:
	rm -f *.o *.hex *~

upload_2009:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 57600  -U flash:w:final.hex

upload_r:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200  -U flash:w:recebe.hex

upload_t:
	${UPLOADER} -F -V -v -c arduino -p ATMEGA328P -P /dev/ttyACM1 -b 115200  -U flash:w:transmite.hex
