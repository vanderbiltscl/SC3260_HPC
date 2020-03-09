CC=mpicc
CFLAGS=-Wall

reduce : reduce.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f reduce
