CC = g++
STANDART = --std=c++11
COMPILER_FLGS = -Werror 
LINKER_FLGS = -lboost_system

ROOT_DIR = ../

vpath %.hpp $(ROOT_DIR)/priority_queue/
vpath %.cpp $(ROOT_DIR)/priority_queue/

INCL = -I $(ROOT_DIR)/priority_queue/

all: test

test: priority_queue.o
	$(CC) $(STANDART) -o $@ $^ $(LINKER_FLGS)

priority_queue.o: priority_queue.cpp priority_queue.hpp
	$(CC) $(STANDART) $(COMPILER_FLGS) -c $< $(INCL)

clean:
	rm -f *.o
	rm -f test
