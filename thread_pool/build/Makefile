CC = g++
STANDART = --std=c++11
COMPILER_FLGS = -Werror
LINKER_FLGS = -pthread

ROOT_DIR = ..
HEADERS = $(ROOT_DIR)/headers
SOURCES = $(ROOT_DIR)/sources

INCL = -I $(HEADERS)

all: thread_pool

thread_pool: main.o thread_pool.o error_codes.o
	$(CC) -o $@ $^ $(LINKER_FLGS)

thread_pool.o: $(SOURCES)/thread_pool.cpp
	$(CC) $(STANDART) $(COMPILER_FLGS) -c $< $(INCL) 

error_codes.o: $(SOURCES)/error_codes.cpp
	$(CC) $(STANDART) $(COMPILER_FLGS) -c $< $(INCL) 

main.o: $(SOURCES)/main.cpp 
	$(CC) $(STANDART) $(COMPIELR_FLGS) -c $< $(INCL)

clean:
	rm -f thread_pool
	rm -f *.o
