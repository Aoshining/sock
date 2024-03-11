Adventure: main.o Adventure.o
	g++ -o Adventure main.o Adventure.o

main.o: main.cpp Adventure.h
	g++ -c main.cpp

Adventure.o: Adventure.cpp Adventure.h
	g++ -c Adventure.cpp
	
clean:
	del Adventure.exe Adventure.o main.o