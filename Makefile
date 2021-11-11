all: prog

#executable deps & cmd
prog: test-suite.o library.o catch.o
	g++ catch.o library.o test-suite.o -o prog

catch.o: catch.cpp catch.h
	g++ -c catch.cpp -o catch.o

library.o: library.cpp library.h
	g++ -c library.cpp -o library.o

test-suite.o: test-suite.cpp catch.h library.h
	g++ -c test-suite.cpp -o test-suite.o

clean:
	rm -rf *.o prog