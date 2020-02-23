/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : memory.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "options.h"
#include "process.h"

#define HEADER_MEMORY "Memory:\n"
#define PROCESS_MEMORY " -> {id:%d, sz:%d, in=%d}\n"

typedef struct memory_t Memory;

struct memory_t {
	int capacity; /* Maximum memory capacity       */
	int size;     /* Number of processes in memory */
	int recent;   /* Most recently added process   */
	List *list;   /* Linked list of memory nodes   */
};

/* Initialises a Memory structure */
Memory* initMemory(
	int capacity
);

/* Loads a process into memory and returns true if successful */
bool loadIntoMemory(
	Memory *m,
	Process *data,
	char *algorithm,
	int time
);

/* Removes a process from memory */
Process* removeFromMemory(
	Memory *m,
	int id
);

/* Removes the oldest non-executing process sitting in memory */
Process* removeOldestFromMemory(
	Memory *m,
	List *running,
	int time,
	int quantum
);

/* Searches for the oldest non-executing process sitting in memory */
Process* searchForOldest(
	List *node,
	Process *old,
	Process *run,
	int time
);

/* Returns the first process in memory */
Process* getMemoryHead(
	Memory *m
);

/* Returns the last process in memory */
Process* getMemoryTail(
	Memory *m
);

/* Merges adjacent free holes together */
void mergeHoles(
	Memory *m
);

/* Used by mergeHoles() */
void recursiveMerge(
	List *node,
	List *prev
);

/* Prints the memory to screen */
void displayMemory(
	Memory *m
);

/* Helper print function */
void printMemory(
	List *node
);

/* Returns true if memory is empty */
bool isEmpty(
	Memory *m
);

/* Retruns true if a process is present in memory */
bool inMemory(
	Memory *m,
	Process *p
);

/* Returns true if there is enough space in the memory for a process */
bool enoughSpace(
	Memory *m,
	void *data
);

/* Returns true if a process is terminated */
bool isExpired(
	Process *p,
	int time,
	int quantum
);

/* Returns the memory usage percentage */
int getMemorySize(
	Memory *m
);

/* Returns true if a list node contains a matching process */
bool equalMemory(
	int id,
	Elem *data
);

/* Returns the number of holes in memory */
int getHoles(
	Memory *m
);

/* Rounds up a number */
int roundUp(
	double num
);

/* First Fit algorithm */
bool firstFit(
	List *node,
	void *data
);

/* Best Fit algorithm */
bool bestFit(
	List *node,
	void *data
);

/* Used by bestFit() */
List* recursiveBestFit(
	List *node,
	void *data,
	List *best
);

/* Worst Fit algorithm */
bool worstFit(
	List *node,
	void *data
);

/* Used by worstFit() */
List* recursiveWorstFit(
	List *node,
	void *data,
	List *worst
);

#endif
