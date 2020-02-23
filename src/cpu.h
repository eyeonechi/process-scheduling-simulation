/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : cpu.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#ifndef CPU_H
#define CPU_H

#include <stdbool.h>
#include <stdio.h>

#include "list.h"
#include "process.h"

#define HEADER_CPU "CPU:\n"
#define PROCESS_CPU " -> {id:%d, ex:%d, jt=%d}\n"

typedef struct cpu_t CPU;

struct cpu_t {
	int size;    /* Number of processes in the CPU */
	List *queue; /* Round Robin queue of the CPU   */
};

/* Initialises a CPU structure */
CPU* initCPU(
);

/* Loads a process into the CPU */
void loadIntoCPU(
	CPU *c,
	void *data
);

/* Removes a process if found */
void* removeFromCPU(
	CPU *c,
	int id
);

/* Removes the head of the queue */
void* removeCPUHead(
	CPU *c,
	int time
);

/* Removes the tail of the queue */
void* removeCPUTail(
	CPU *c
);

/* Updates the run time of the running process */
void updateProcess(
	CPU *c
);

/* Prints the CPU to the screen */
void displayCPU(
	CPU *c
);

/* Helper print function */
void printCPU(
	List *node
);

/* Returns true if the quantum has expired for a running process */
bool quantumExpired(
	CPU *c,
	int time,
	int offset,
	int quantum
);

/* Returns true if the running process has terminated */
bool processTerminated(
	CPU *c
);

/* Returns true if there are still processes in the queue */
bool isRunning(
	CPU *c
);

/* Returns true if a process is found in the queue */
bool inCPU(
	CPU *c,
	Process *p
);

/* Finds a process equal to the target */
bool equalQueue(
	int id,
	Elem *data
);

#endif