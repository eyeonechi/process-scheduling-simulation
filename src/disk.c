/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : disk.c
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include "disk.h"
#include "heap.h"

/* Initialises a disk structure */
Disk* initDisk() {
	Disk *d = (Disk *)malloc(sizeof(d));
	d->heap = initHeap();
	d->size = 0;
	return d;
}

/* Loads a process into the disk */
void loadIntoDisk(Disk *d, Process *p, int time) {
	p->inactive = time;
	d->size ++;
	insertIntoHeap(d->heap, (Elem *) p, greaterThan);
}

/* Removes a matching process from the disk */
Process* removeProcessFromDisk(Disk *d, Process *p) {
	d->size --;
	bool (*cmp)(void*, void*) = &greaterThan;
	bool (*eq)(void*, void*) = &equalTo;
	Process *x = removeFromHeap(d->heap, p, cmp, eq);
	x->inactive = 0;
	return x;
}

/* Removes the highest priority process from the disk */
Process* removeFromDisk(Disk *d) {
	d->size --;
	bool (*cmp)(void*, void*) = &greaterThan;
	Process *x = removeTopFromHeap(d->heap, cmp);
	return x;
}

/* Prints the disk */
void displayDisk(Disk *d) {
	fprintf(stdout, HEADER_DISK);
	displayHeap(d->heap, d->heap->nodes, 0, printDisk);
	fprintf(stdout, NEWLINE);
}

/* Helper print function */
void printDisk(Node *node, Node *left, Node *right) {
	Process *n = (node) ? ((Process *)node->data) : NULL;
	Process *l = (left) ? ((Process *)left->data) : NULL;
	Process *r = (right) ? ((Process *)right->data) : NULL;
	fprintf(stdout, PROCESS_DISK_NODE, n->id, n->inactive);
	if (l) {
		fprintf(stdout, PROCESS_DISK_LEFT, l->id, l->inactive);
	}
	if (r) {
		fprintf(stdout, PROCESS_DISK_RIGHT, r->id, r->inactive);
	}
}

/* Returns true if a process is in the disk */
bool inDisk(Disk *d, Process *p) {
	bool (*eq)(void*, void*) = &equalTo;
	return searchHeap(d->heap, d->heap->nodes, 0, p, eq);
}

/* Returns true if there are processes in disk waiting to be loaded */
bool processToLoad(Disk *d) {
	return (d->heap->num > 0);
}

/* Returns true if process1 has been inactive longer than process2 */
bool greaterThan(void *process1, void *process2) {
	if (((Process *) process1)->inactive < ((Process *) process2)->inactive) {
		return true;
	} else if (((Process *) process1)->inactive
		== ((Process *) process2)->inactive) {
		if (((Process *) process1)->id < ((Process *) process2)->id) {
			return true;
		}
		return false;
	}
	return false;
}

/* Returns true process1 is equal to process2 */
bool equalTo(void *process1, void *process2) {
	return (((Process *) process1)->id == ((Process *) process2)->id);
}
