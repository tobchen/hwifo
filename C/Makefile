CFLAGS=-g -Wall -Wextra

test: test.o hifo.o
	gcc -o test test.o hifo.o $(CFLAGS)

test.o: test.c hifo.h
	gcc -o test.o -c test.c $(CFLAGS)

hwifo.o: hifo.c hifo.h
	gcc -o hifo.o -c hifo.c $(CFLAGS)

clean:
	rm -f *.o test