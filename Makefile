CC=gcc

all: unisim test

unisim:	main.c sim.o loader.o
	$(CC) -o unisim main.c sim.o loader.o helper.o

sim.o: sim.c sim.h helper.h helper.o
	$(CC) -c sim.c

loader.o: loader.c loader.h helper.h helper.o
	$(CC) -c loader.c

helper.o: helper.c helper.h
	$(CC) -c helper.c

test: unisim hello
	./unisim hello

clean:
	rm *.o
