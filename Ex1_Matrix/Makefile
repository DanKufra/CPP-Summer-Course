CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -g

IntMatrixMainDriver: IntMatrix.o IntMatrixDriver.cpp
	$(CC) $(CFLAGS) IntMatrixDriver.cpp IntMatrix.o -o IntMatrixMainDriver
	
all: tar IntMatrixMainDriver IntMatrix

IntMatrix: IntMatrix.cpp IntMatrix.h
	$(CC) $(CFLAGS) -c IntMatrix.cpp 
	
tar: IntMatrix.h IntMatrix.cpp IntMatrixDriver.cpp Makefile
	tar cvf ex1.tar IntMatrix.cpp IntMatrix.h IntMatrixDriver.cpp Makefile
	
clean:
	rm -f IntMatrix.o
	rm -f IntMatrixMainDriver
	rm -f ex1.tar

.PHONY: clean all IntMatrix
