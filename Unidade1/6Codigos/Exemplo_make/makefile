
CC = gcc
FLAGS = -Wall -pedantic     -O4

app: main.o teste.o outro.o
	$(CC) main.o teste.o outro.o -o app

outro.o: outro.c outro.h
	$(CC) outro.c $(FLAGS) -c

teste.o: teste.c teste.h
	$(CC) teste.c $(FLAGS) -c

install:
	cp app /bin/

clear:
	rm teste.o app outro.o main.o





