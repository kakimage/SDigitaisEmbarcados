
CC = gcc
FLAGS = -Wall -pedantic  -g   

app: main.o teste.o outro.o
	$(CC) main.o teste.o outro.o -o app

main.o: teste.h outro.h
	$(CC) main.c $(FLAGS) -c

outro.o: outro.c outro.h
	$(CC) outro.c $(FLAGS) -c

teste.o: teste.c teste.h
	$(CC) teste.c $(FLAGS) -c

install:
	cp app /bin/

clear:
	rm teste.o app outro.o main.o





