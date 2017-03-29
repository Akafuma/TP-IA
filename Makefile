CC=gcc
CFLAGS=-std=c99

all: demo

demo: main.o generators.o backtrack.o forward-checking.o forward-checking-md.o pile.o util.o csp_output.o
	$(CC) -o $@ $^

main.o: main.c generators.h backtrack.h forward-checking.h forward-checking-md.h util.h csp_output.h
	$(CC) -o main.o -c main.c $(CFLAGS)

generators.o: generators.c generators.h
	$(CC) -o generators.o -c generators.c $(CFLAGS)
	
backtrack.o : backtrack.c backtrack.h
	$(CC) -o backtrack.o -c backtrack.c $(CFLAGS)
	
forward-checking.o: forward-checking.c forward-checking.h
	$(CC) -o forward-checking.o -c forward-checking.c $(CFLAGS)
	
forward-checking-md.o: forward-checking-md.c forward-checking-md.h
	$(CC) -o forward-checking-md.o -c forward-checking-md.c $(CFLAGS)
	
pile.o: pile.c pile.h
	$(CC) -o pile.o -c pile.c $(CFLAGS)
	
util.o: util.c util.h
	$(CC) -o util.o -c util.c $(CFLAGS)
	
csp_output.o: csp_output.c csp_output.h
	$(CC) -o csp_output.o -c csp_output.c $(CFLAGS)
	
clean:
	rm -rf *.o
	
mrproper: clean
	rm -rf demo
