CC = mpiicc
CFLAGS = -fopenmp -O3 -g
.PHONY = pivot

pivot: pivot.o
	$(CC) $(CFLAGS) $^ -o $@

pivot.o: pivot.c
	$(CC) $(CFLAGS) -c pivot.c -o pivot.o

clean:
	rm -f pivot.o pivot