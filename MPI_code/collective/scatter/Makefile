CC=mpicc
CFLAGS=-Wall -lm

scatter : scatter.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f scatter
