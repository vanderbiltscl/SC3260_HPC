CC=mpicc
CFLAGS=-Wall

student : student.c
	$(CC) -o $@ $< ${CFLAGS}

.PHONY: clean

clean:
	rm -f student