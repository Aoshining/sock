Fraction: Fraction.o main.o
	g++ -o Fraction Fraction.o main.o

main.o: main.cpp Fraction.h
	g++ -c main.cpp Fraction.h

Fraction.o: Fraction.cpp Fraction.h
	g++ -c Fraction.cpp Fraction.h

clean:
	del Fraction.exe *.o