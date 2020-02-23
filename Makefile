# COMP30023 Computer Systems
# Semester 1 2017
# Project 1     : Makefile
# Student Name  : Ivan Ken Weng Chee
# Student ID    : 736901
# Student Email : ichee@student.unimelb.edu.au

## CC  = Compiler.
## CFLAGS = Compiler flags.
CC	= gcc
CFLAGS =	-Wall -Wextra -ansi -std=gnu99 -g -O0

## OBJ = Object files.
## SRC = Source files.
## EXE = Executable name.

SRC =	src/swap.c src/cpu.c src/disk.c src/memory.c src/options.c src/process.c src/list.c src/heap.c src/other.c
OBJ =	src/swap.o src/cpu.o src/disk.o src/memory.o src/options.o src/process.o src/list.o src/heap.o src/other.o
EXE = bin/swap

## Run: Automatically run the provided tests 
run:
	echo "Running automated test cases..."
	echo "Test 1: input.txt:"
	$(EXE) -f test/input.txt -a first -m 1000 -q 7 > test/out.txt
	diff test/out.txt test/output.txt
	$(EXE) -f test/testFirst1.txt -a first -m 1000 -q 7 > test/out.txt
	diff test/out.txt test/testFirst1.out.txt
	$(EXE) -f test/testBest1.txt -a best -m 1000 -q 7 > test/out.txt
	diff test/out.txt test/testBest1.out.txt
	$(EXE) -f test/testWorst1.txt -a worst -m 1000 -q 7 > test/out.txt
	diff test/out.txt test/testWorst1.out.txt
	rm test/out.txt

## Compile:
compile: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJ) -lm

## Usage:
usage:
	$(EXE)

## Clean: Remove object files and core dump files.
clean:
	rm $(OBJ) 

## Clobber: Performs Clean and removes executable file.
clobber: clean
	rm $(EXE) 

## Dependencies
src/swap.o    : src/cpu.h src/disk.h src/memory.h src/process.h src/other.h
src/cpu.o     : src/cpu.h src/process.h
src/disk.o    : src/disk.h
src/memory.o  : src/memory.h
src/options.o : src/options.h
src/process.o : src/process.h src/options.h
src/list.o    : src/list.h src/other.h
src/heap.o    : src/heap.h src/other.h
src/other.o   : src/other.h
