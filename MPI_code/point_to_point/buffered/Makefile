CC=mpicc
CFLAGS=-Wall

buffered : buffered.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f buffered