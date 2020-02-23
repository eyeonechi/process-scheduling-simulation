/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : other.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#ifndef OTHER_H
#define OTHER_H

#include <assert.h>
#include <stdlib.h>

#define NEWLINE "\n"

typedef void Elem;
typedef unsigned int uint;

typedef struct time_t Time;

struct time_t {
	int time;
	int offset;
};

/* Initialises a Time structure */
Time* initTime();

/* Simulates a clock */
void tick(Time *t);

/* Sets an offset time */
void setOffset(Time *t);

#endif
