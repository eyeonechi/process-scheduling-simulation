/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : processes.c
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include "process.h"

/* Initialises a Processes structure */
Processes* initProcesses() {
	Processes *p = (Processes *) malloc(sizeof(p));
	assert(p);
	p->size = 0;
	p->list = NULL;
	return p;
}

/* Initialises a process */
Process* initProcess(int id, int job, int size, int time) {
	Process *p = (Process *) malloc(sizeof(p));
	assert(p);
	p->id = id;
	p->job = job;
	p->size = size;
	p->time = time;
	return p;
}

/* Adds a process to processes */
void addProcess(Processes *p, Process *x) {
	if (p->list) {
		append(p->list->next, p->list, x, x->size);
	} else {
		p->list = initList(x, x->size);
	}
}

/* Loads process details from an input file */
void loadProcesses(Processes *p, Options *o) {
	FILE *file = fopen(o->filename, "r");
	assert(file);
	int time, id, size, job;
	while (fscanf(file, "%d %d %d %d\n", &time, &id, &size, &job) == 4) {
		Process *x = initProcess(id, job, size, time);
		addProcess(p, x);
		p->size ++;
	}
}

/* Returns the next process */
void* getProcess(Processes *p) {
	p->size --;
	return popHead(&(p->list), p->list->next, true);
}

/* Prints processes to screen */
void displayProcesses(Processes *p) {
	fprintf(stdout, "PROCESS:\n");
	displayList(p->list, printProcess);
	fprintf(stdout, NEWLINE);
}

/* Helper print function */
void printProcess(List *node) {
	if (node && node->data) {
		Process *p = ((Process *)node->data);
		fprintf(stdout, " -> {tc:%d, id:%d, ms=%d, jt=%d}\n",
			p->time, p->id, p->size, p->job);
	}
}

/* Returns true if a new process is arriving */
bool processCreated(Processes *p, int time) {
	if (p->list && p->list->data) {
		return (((Process *)p->list->data)->time == time);
	}
	return false;
}

/* Returns true if there are still processes to arive */
bool hasProcesses(Processes *p) {
	return (p->size != 0);
}
