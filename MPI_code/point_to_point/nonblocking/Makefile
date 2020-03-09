CC=mpicc
CFLAGS=-Wall

nonblocking : nonblocking.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f nonblocking