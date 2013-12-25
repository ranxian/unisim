CC=gcc

# CFLAGS=-DDEBUG
CFLAGS=-DBENCH

OBJS=sim.o loader.o helper.o shifter.o memory.o extender.o syscall.o cache.o

all: unisim test_sim test_cache

unisim:	main.c $(OBJS)
	$(CC) $(CFLAGS) -o unisim main.c $(OBJS)

test: test.c $(OBJS)
	$(CC) $(CFLAGS) -o test test.c $(OBJS)
	
sim.o: sim.c sim.h helper.h helper.o
	$(CC) $(CFLAGS) -c sim.c

loader.o: loader.c loader.h helper.h helper.o
	$(CC) $(CFLAGS) -c loader.c

helper.o: helper.c helper.h
	$(CC) $(CFLAGS) -c helper.c

shifter.o: shifter.c shifter.h
	$(CC) $(CFLAGS) -c shifter.c

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

extender.o: extender.c extender.h
	$(CC) $(CFLAGS) -c extender.c

test_sim: sim.o test_sim.c
	$(CC) $(CFLAGS) -o test_sim test_sim.c 

syscall.o: syscall.c syscall.h
	$(CC) $(CFLAGS) -c syscall.c

cache.o: cache.c cache.h
	$(CC) $(CFLAGS) -c cache.c

test_cache: $(OBJS) test_cache.c
	$(CC) $(CFLAGS) -o test_cache $(OBJS) test_cache.c

clean:
	rm *.o
