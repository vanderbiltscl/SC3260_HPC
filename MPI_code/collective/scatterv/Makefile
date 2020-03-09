CC=mpicc
CFLAGS=-Wall -lm

scatterv : scatterv.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f scatterv
