/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : swap.c
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cpu.h"
#include "disk.h"
#include "memory.h"
#include "process.h"
#include "options.h"
#include "other.h"

#define PRINT_STATUS "time %d, %d loaded, numprocesses=%d, numholes=%d, memusage=%d%%\n"
#define PRINT_FINISH "time %d, simulation finished.\n"

/* Simulates the environment where processes get passed around */
void simulate(
	CPU *c,
	Disk *d,
	Memory *m,
	Processes *p,
	Options *o,
	Time *t
);

/* Swaps processes from disk to memory and cpu */
bool swapAndSchedule(
	CPU *c,
	Disk *d,
	Memory *m,
	Options *o,
	Time *t
);

/* Prints the required output to the screen */
void printStatus(
	CPU *c,
	Memory *m,
	Time *t
);

/* Prints the end of the simulation */
void printFinish(
	Time *t
);

/* Main function that drives the program */
int main(int argc, char **argv) {
	/* Read in arguments */
	Options *o = initOptions();
	loadOptions(o, argc, argv);
	/* Load processes from file */
	Processes *p = initProcesses();
	loadProcesses(p, o);
	/* Initialises structures */
	Time *t = initTime();
	CPU *c = initCPU();
	Disk *d = initDisk();
	Memory *m = initMemory(o->memory);
	/* Runs simulation */
	simulate(c, d, m, p, o, t);
	return(EXIT_SUCCESS);
}

/* Simulates the environment where processes get passed around */
void simulate(CPU *c, Disk *d, Memory *m, Processes *p, Options *o, Time *t) {
	/* Loop executes while there are new processes being created or until *
	 * the CPU finishes executing all processes in the queue              */
	while (hasProcesses(p) || isRunning(c)) {
		updateProcess(c);
		mergeHoles(m);
		/* A new process is created */
		if (processCreated(p, t->time)) {
			while (processCreated(p, t->time)) {
				Process *y = (Process*)getProcess(p);
				loadIntoDisk(d, y, t->time);
			}
		}
		/* E1 : A process has been created and memory is currently empty */
		if (isEmpty(m)) {
			swapAndSchedule(c, d, m, o, t);
		}
		/* E3 : A process that was running on the CPU has terminated */
		if (processTerminated(c)) {
			Process *x = removeCPUHead(c, t->time);
			removeFromMemory(m, x->id);
			mergeHoles(m);
			swapAndSchedule(c, d, m, o, t);
			setOffset(t);
		}
		/* E2 : The quantum has expired for the process running on the CPU */
		else if (quantumExpired(c, t->time, t->offset, o->quantum)) {
			if (!swapAndSchedule(c, d, m, o, t)) {
				Process *e = removeCPUHead(c, t->time);
				loadIntoCPU(c, e);
			}
		}
		/* Updates time */
		tick(t);
	}
	/* Simulation finished */
	printFinish(t);
}

/* Swaps processes from disk to memory and cpu */
bool swapAndSchedule(CPU *c, Disk *d, Memory *m, Options *o, Time *t) {
	bool removedHead = false;
	bool ableToFit = true;
	/* There is a process waiting in the disk */
	if (processToLoad(d)) {                                    
		Process *x = removeFromDisk(d);
		/* Enough space in memory for the process */
		if (enoughSpace(m, x)) {
			loadIntoMemory(m, x, o->algorithm, t->time);
			loadIntoCPU(c, x);
		} else {
			/* Keeps removing the longest idle process from memory *
			 * until there is enough space                         */
			while (!enoughSpace(m, x)) {
				Process *y = removeOldestFromMemory(
					m, c->queue, t->time, o->quantum);
				/* An idle process is removed from memory */
				if (y) {
					/* Removed process is the current expired process */
					if (y->id == ((Process *)c->queue->data)->id) {
						removedHead = true;
					}
					ableToFit = true;
					removeFromCPU(c, y->id);
					loadIntoDisk(d, y, t->time);
					mergeHoles(m);
				}
				/* Not possible for the new process to fit */
				else {
					ableToFit = false;
					loadIntoDisk(d, x, t->time);
					break;
				}
			}
			/* Finally inserts the process */
			if (ableToFit) {
				loadIntoMemory(m, x, o->algorithm, t->time);
				loadIntoCPU(c, x);
			}
		}
		printStatus(c, m, t);
	}
	return removedHead;
}

/* Prints the required output to the screen */
void printStatus(CPU *c, Memory *m, Time *t) {
	fprintf(stdout,
		PRINT_STATUS,
		t->time, m->recent, c->size, getHoles(m), getMemorySize(m));
}

/* Prints the end of the simulation */
void printFinish(Time *t) {
	fprintf(stdout, PRINT_FINISH, t->time - 1);
}
