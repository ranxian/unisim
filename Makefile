CC=gcc

all: unisim test_sim

unisim:	main.c sim.o loader.o shifter.o mmu.o extender.o syscall.o
	$(CC) -o unisim main.c sim.o loader.o helper.o shifter.o mmu.o extender.o syscall.o

sim.o: sim.c sim.h helper.h helper.o
	$(CC) -c sim.c

loader.o: loader.c loader.h helper.h helper.o
	$(CC) -c loader.c

helper.o: helper.c helper.h
	$(CC) -c helper.c

shifter.o: shifter.c shifter.h
	$(CC) -c shifter.c

mmu.o: mmu.c mmu.h
	$(CC) -c mmu.c

extender.o: extender.c extender.h
	$(CC) -c extender.c

test: unisim hello
	./unisim hello

test_sim: sim.o test_sim.c
	$(CC) -o test_sim test_sim.c sim.h

syscall.o: syscall.c syscall.h
	$(CC) -c syscall.c

clean:
	rm *.o
