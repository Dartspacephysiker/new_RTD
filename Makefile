#Makefile for this way bad new RTD
#2015/10/06
#Author: S Dawg

CC=g++

CFLAGS=-c -Wall `wx-config --cxxflags` -ggdb
LDFLAGS=`wx-config --libs` -lfftw3

SRC=dartRTD.cpp dartRTD_confeditor.cpp RTD_conf_reader.c
OBJ=$(SRC:.cpp=.o)
HDR = dartRTD.h dartRTD_confeditor.h   RTD_conf_reader.h dartRTD_structs.h

EXEC=dartRTD

all: $(SRC) $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS) 

.cpp.o: ${HDR}
	$(CC) $< -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(EXEC)
