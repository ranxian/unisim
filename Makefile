CC=gcc

OBJS=sim.o loader.o helper.o shifter.o memory.o extender.o syscall.o cache.o

all: unisim test test_cache

unisim:	main.c $(OBJS)
	$(CC) $(DFLAGS) -o unisim main.c $(OBJS)

test: test.c $(OBJS)
	$(CC) $(DFLAGS) -o test test.c $(OBJS)
	
sim.o: sim.c sim.h helper.h helper.o
	$(CC) $(DFLAGS) -c sim.c

loader.o: loader.c loader.h helper.h helper.o
	$(CC) $(DFLAGS) -c loader.c

helper.o: helper.c helper.h
	$(CC) $(DFLAGS) -c helper.c

shifter.o: shifter.c shifter.h
	$(CC) $(DFLAGS) -c shifter.c

memory.o: memory.c memory.h
	$(CC) $(DFLAGS) -c memory.c

extender.o: extender.c extender.h
	$(CC) $(DFLAGS) -c extender.c

syscall.o: syscall.c syscall.h
	$(CC) $(DFLAGS) -c syscall.c

cache.o: cache.c cache.h
	$(CC) $(DFLAGS) -c cache.c

test_cache: $(OBJS) test_cache.c
	$(CC) $(DFLAGS) -o test_cache $(OBJS) test_cache.c

correct:
	ruby correct.rb

benchmark:
	ruby benchmark.rb

sbench:
	BENCH=small ruby benchmark.rb

analyze:
	ruby analyze.rb

clean:
	rm *.o
	rm -rf results/*


