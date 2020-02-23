/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : other.c
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include "other.h"

/* Initialises a Time structure */
Time* initTime() {
	Time *t = (Time *) malloc(sizeof(t));
	assert(t);
	t->time = 0;
	t->offset = 0;
	return t;
}

/* Simulates a clock */
void tick(Time *t) {
	t->time ++;
}

/* Sets an offset time */
void setOffset(Time *t) {
	t->offset = t->time;
}
