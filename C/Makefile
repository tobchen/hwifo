CFLAGS=-g -Wall -Wextra

test: test.o hwifo.o
	gcc -o test test.o hwifo.o $(CFLAGS)

test.o: test.c hwifo.h
	gcc -o test.o -c test.c $(CFLAGS)

hwifo.o: hwifo.c hwifo.h
	gcc -o hwifo.o -c hwifo.c $(CFLAGS)

clean:
	rm -f *.o test