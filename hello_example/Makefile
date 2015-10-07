#Makefile for this way bad new RTD
#2015/10/06
#Author: S Dawg

CC=g++

CFLAGS=-c -Wall `wx-config --cxxflags`
LDFLAGS=`wx-config --libs`

SOURCES=hello.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hello

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS) 

.cpp.o:
	$(CC) $< -o $@ $(CFLAGS)
