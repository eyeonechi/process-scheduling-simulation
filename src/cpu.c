/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : cpu.c
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include "cpu.h"

/* Initialises a CPU structure */
CPU* initCPU() {
	CPU *c = (CPU *)malloc(sizeof(c));
	assert(c);
	c->size = 0;
	return c;
}

/* Loads a process into the CPU */
void loadIntoCPU(CPU *c, void *data) {
	if (c->queue) {
		append(c->queue, NULL, data, ((Process *) data)->size);
	} else {
		c->queue = initList(data, ((Process *) data)->size);
	}
	c->size ++;
}

/* Removes a process if found */
void* removeFromCPU(CPU *c, int id) {
	if (c->queue) {
		c->size --;
		Process *p = removeNode(c->queue, c->queue->next, id, equalQueue);
		if (c->size == 0) {
			free(c->queue);
			c->queue = NULL;
		}
		return p;
	}
	return NULL;
}

/* Removes the head of the queue */
void* removeCPUHead(CPU *c, int time) {
	if (c->queue) {
		c->size --;
		Process *p = popHead(&(c->queue), c->queue->next, true);
		if (c->queue) {
			((Process *)c->queue->data)->execute = time;
		}
		if (c->size == 0) {
			free(c->queue);
			c->queue = NULL;
		}
		return p;
	}
	return NULL;
}

/* Removes the tail of the queue */
void* removeCPUTail(CPU *c) {
	c->size --;
	void *data = popTail(c->queue, NULL);
	return data;
}

/* Updates the run time of the running process */
void updateProcess(CPU *c) {
	if (c->queue) {
		Process *x = (Process *)c->queue->data;
		x->job --;
	}
}

/* Prints the CPU to the screen */
void displayCPU(CPU *c) {
	fprintf(stdout, HEADER_CPU);
	displayList(c->queue, printCPU);
	fprintf(stdout, NEWLINE);
}

/* Helper print function */
void printCPU(List *node) {
	if (node && node->data) {
		Process *p = ((Process *)node->data);
		fprintf(stdout, PROCESS_CPU,
			p->id, p->execute, p->job);
	}
}

/* Returns true if the quantum has expired for a running process */
bool quantumExpired(CPU *c, int time, int offset, int quantum) {
	if (c->size > 0) {
		if (time > 0) {
			return ((time - offset) % quantum == 0);
		}
	}
	return false;
}

/* Returns true if the running process has terminated */
bool processTerminated(CPU *c) {
	if (c->queue) {
		if (((Process *)c->queue->data)->job == 0) {
			return true;
		}
	}
	return false;
}

/* Returns true if there are still processes in the queue */
bool isRunning(CPU *c) {
	return !(c->size == 0);
}

/* Returns true if a process is found in the queue */
bool inCPU(CPU *c, Process *p) {
	List *node = c->queue;
	while (node) {
		if (((Process *)node->data)->id == p->id) {
			return true;
		}
		node = node->next;
	}
	return false;
}

/* Finds a process equal to the target */
bool equalQueue(int id, Elem *data) {
	return (data) ? (id == ((Process *) data)->id) : false;
}
