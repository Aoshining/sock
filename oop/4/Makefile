all: pdadd pdlist pdshow pdremove

pdadd: pdadd.o diary.o
	g++ -o pdadd pdadd.o diary.o

pdlist: pdlist.o diary.o
	g++ -o pdlist pdlist.o diary.o

pdshow: pdshow.o diary.o
	g++ -o pdshow pdshow.o diary.o

pdremove: pdremove.o diary.o
	g++ -o pdremove pdremove.o diary.o

pdadd.o: pdadd.cpp diary.h
	g++ -c pdadd.cpp

pdlist.o: pdlist.cpp diary.h
	g++ -c pdlist.cpp

pdshow.o: pdshow.cpp diary.h
	g++ -c pdshow.cpp

pdremove.o: pdremove.cpp diary.h
	g++ -c pdremove.cpp

diary.o: diary.cpp diary.h
	g++ -c diary.cpp
	
clean:
	del pd*.exe pd*.o diary.o