/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : disk.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#ifndef DISK_H
#define DISK_H

#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "process.h"

#define HEADER_DISK "Disk:\n"
#define PROCESS_DISK_NODE " Node: id=%d td=%d\n"
#define PROCESS_DISK_LEFT "    Left: id=%d td=%d\n"
#define PROCESS_DISK_RIGHT "    Right: id=%d td=%d\n"

typedef struct disk_t Disk;

struct disk_t {
	int size;   /* Number of elements in the disk */
	Heap *heap; /* Heap used for disk storage     */
};

/* Initialises a disk structure */
Disk* initDisk(
);

/* Loads a process into the disk */
void loadIntoDisk(
	Disk *d,
	Process *p,
	int time
);

/* Removes a matching process from the disk */
Process* removeProcessFromDisk(
	Disk *d,
	Process *p
);

/* Removes the highest priority process from the disk */
Process* removeFromDisk(
	Disk *d
);

/* Prints the disk */
void displayDisk(
	Disk *d
);

/* Helper print function */
void printDisk(
	Node *node,
	Node *left,
	Node *right
);

/* Returns true if a process is in the disk */
bool inDisk(
	Disk *d,
	Process *p
);

/* Returns true if there are processes in disk waiting to be loaded */
bool processToLoad(
	Disk *d
);

/* Returns true if process1 is greater than process2 */
bool greaterThan(
	void *process1,
	void *process2
);

/* Returns true process1 is equal to process2 */
bool equalTo(
	void *process1,
	void *process2
);

#endif
