CC = g++
COMPILER_FLGS = -fno-elide-constructors
STD_VERSION = -std=c++11
TRUNK = ../

vpath %.hpp $(TRUNK)/BigInteger
vpath %.cpp $(TRUNK)/BigInteger

all: main

INCL = -I ../BigInteger/

BigInteger.o: BigInteger.cpp BigInteger.hpp
	$(CC) $(STD_VERSION) $(COMPILER_FLGS) -c $< $(INCL)

main.o: main.cpp BigInteger.cpp BigInteger.hpp
	$(CC) $(STD_VERSION) $(COMPILER_FLGS) -c $< $(INCL)

main: main.o BigInteger.o
	$(CC) $(STD_VERSION) -o $@ $^ -lgtest

clean:
	rm -f *.o
	rm -f main
