student2: main.o student2.o
	g++ -o student2 main.o student2.o

main.o: main.cpp student2.h
	g++ -c main.cpp

student2.o: student2.cpp student2.h
	g++ -c student2.cpp

clean:
	del student2.exe student2.o main.o