#Makefile for this way bad new RTD
#2015/10/06
#Author: S Dawg

CC=g++

CPPFLAGS=-c -Wall `wx-config --cxxflags` -ggdb
CFLAGS=-c -Wall `wx-config --cxxflags` -ggdb

LDFLAGS=`wx-config --libs` -lfftw3

SRC=dartRTD.cpp dartRTD_confeditor.cpp
OBJ=$(SRC:.cpp=.o)
HDR = dartRTD.h dartRTD_confeditor.h RTD_conf_structs.h

C_SRC = RTD_conf_reader.c
C_OBJ = $(C_SRC:.c=.o)
C_HDR = RTD_conf_reader.h RTD_conf_structs.h

EXEC=dartRTD

all: $(SRC) $(C_SRC) $(EXEC)

$(EXEC): $(OBJ) $(C_OBJ)
	$(CC) -o $@ $(OBJ) $(C_OBJ) $(LDFLAGS) 

.cpp.o: ${HDR}
	$(CC) $< -o $@ $(CPPFLAGS)

.c.o: ${C_HDR}
	gcc $< -o $@ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(EXEC)
