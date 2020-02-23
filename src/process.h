/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : process.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <stdbool.h>

#include "list.h"
#include "options.h"

typedef struct process_t Process;
typedef struct processes_t Processes;

struct process_t {
	int id;        /* Process ID                           */
	int job;       /* Job time for process to complete     */
	int size;      /* Memory footprint of process          */
	int time;      /* Time process is created              */
	int execute;   /* Time process started executing       */
	int inactive;  /* Time process is inserted into disk   */
	int inMemory;  /* Time process is inserted into memory */
};

struct processes_t {
	int size;   /* Number of processes      */
	List *list; /* Linked list of processes */
};

/* Initialises a Processes structure */
Processes* initProcesses(
);

/* Initialises a process */
Process* initProcess(
	int id,
	int job,
	int size,
	int time
);

/* Adds a process to processes */
void addProcess(
	Processes *p,
	Process *x
);

/* Returns the next process */
void* getProcess(
	Processes *p
);

/* Loads process details from an input file */
void loadProcesses(
	Processes *p,
	Options *o
);

/* Prints processes to screen */
void displayProcesses(
	Processes *p
);

/* Helper print function */
void printProcess(
	List *node
);

/* Returns true if a new process is arriving */
bool processCreated(
	Processes *p,
	int time
);

/* Returns true if there are still processes to arive */
bool hasProcesses(
	Processes *p
);

#endif
