CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -Wvla -pthread -g

Matrix: Matrix.hpp.gch
	

Matrix.hpp.gch: Matrix.hpp BadDimensionException.h
	$(CC) $(CFLAGS) -c Matrix.hpp

tar:
	tar cvf ex3.tar BadDimensionException.h Matrix.hpp README Makefile

clean:
	rm -f Matrix.hpp.gch
	rm -f ex3.tar

.PHONY: clean tar Matrix
