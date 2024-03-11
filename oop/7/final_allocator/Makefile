CC = g++
CFLAGS = -O3 -g
.PHONY = test

test: test.o
	$(CC) $(CFLAGS) $^ -o $@

test.o: test.cpp myallocator_1.h
	$(CC) $(CFLAGS) -c test.cpp -o test.o

clean:
	del test.o test.exe