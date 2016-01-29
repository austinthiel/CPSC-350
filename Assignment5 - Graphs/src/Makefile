# A simple Makefile for CPSC 350
# Assumes the following directory hierarchy:
# Assignment X
# 	src
#       include

#this Makefile goes in the src directory

#change this to the correct assignment #
EXECUTABLE := Assignment5

# the source files to be built
SOURCES := *.cpp

#stuff you don't need to worry about
INCLUDES := -I ../include -I /usr/include/boost
EXT := exe
CC := g++

all:
	$(CC) $(INCLUDES) -L /usr/lib64/boost $(SOURCES) -lboost_system -o $(EXECUTABLE).$(EXT)

realclean:
	find . -type f -name "*.o" -exec rm '{}' \;
	find . -type f -name "*.exe" -exec rm '{}' \;

# this line required by make - don't delete
