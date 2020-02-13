CC=nvcc
CFLAGS=

vec_add : vector_add.cu
	$(CC) -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f vec_add