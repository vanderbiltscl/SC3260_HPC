CC=mpicc
CFLAGS=-Wall -lm

scatter_gather : scatter_gather.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f scatter_gather
