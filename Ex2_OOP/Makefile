CC = g++
CFLAGS = -std=c++11 -Wextra -Wall -g


MIR: MIR.cpp ParameterParser.o QueryParser.o SongParser.o Lyrical.o Instrumental.o Parameter.o
	$(CC) $(CFLAGS) -c MIR.cpp
	$(CC) $(CFLAGS) QueryParser.o Parser.o ParameterParser.o SongParser.o Instrumental.o \
    Lyrical.o Song.o Parameter.o MIR.o -o MIR

QueryParser.o: QueryParser.h QueryParser.cpp Parser.o
	$(CC) $(CFLAGS) -c QueryParser.cpp

Parser.o: Parser.h Parser.cpp
	$(CC) $(CFLAGS) -c Parser.cpp

ParameterParser.o: ParameterParser.h ParameterParser.cpp Parser.o Parameter.o
	$(CC) $(CFLAGS) -c ParameterParser.cpp

SongParser.o: SongParser.h SongParser.cpp Parser.o Song.o
	$(CC) $(CFLAGS) -c SongParser.cpp

Song.o: Song.h Song.cpp
	$(CC) $(CFLAGS) -c Song.cpp

Lyrical.o: Lyrical.h Lyrical.cpp Song.o
	$(CC) $(CFLAGS) -c Lyrical.cpp

Instrumental.o: Instrumental.h Instrumental.cpp Song.o
	$(CC) $(CFLAGS) -c Instrumental.cpp

Parameter.o: Parameter.h Parameter.cpp
	$(CC) $(CFLAGS) -c Parameter.cpp
	
tar:
	tar cvf ex2.tar Song.h Song.cpp Instrumental.h Instrumental.cpp Lyrical.h \
    Lyrical.cpp MIR.cpp Parameter.cpp Parameter.h Parser.h Parser.cpp QueryParser.h \
	QueryParser.cpp SongParser.h SongParser.cpp ParameterParser.h \
	ParameterParser.cpp Makefile README

clean:
	rm -f Parser.o
	rm -f ParameterParser.o
	rm -f QueryParser.o
	rm -f SongParser.o
	rm -f Song.o
	rm -f Lyrical.o
	rm -f Instrumental.o
	rm -f Parameter.o
	rm -f MIR
	rm -f MIR.o
	rm -f ex2.tar

.PHONY: clean
