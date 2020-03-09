CC=mpicc
CFLAGS=-Wall

bcast : bcast.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f bcast