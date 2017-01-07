all: test

CC = g++
CC_OPTS = -c -g -fpermissive -std=c++11
LINKER = g++ -g -std=c++11 -fpermissive

test: cfg.o main.cpp 
	$(LINKER) -o test main.cpp cfg.o

cfg.o: cfg.h cfg.cpp
	$(CC) $(CC_OPTS) cfg.cpp

.PHONY: clean
clean:
	rm *.o test
