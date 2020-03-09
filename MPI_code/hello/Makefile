CC=mpicc
CFLAGS=-Wall
SRC=mpi_hello.c
EXE=mpi_hello

release : ${SRC}
	$(CC) -o ${EXE} $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f ${EXE}