/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : options.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#ifndef OPTIONS_H
#define OPTIONS_H

#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALGORITHM_LEN 20
#define MAX_FILENAME_LEN 50

#define FILENAME "Filename: %s\n"
#define ALGORITHM "Algorithm: %s\n"
#define MEMORY "Memory: %d\n"
#define QUANTUM "Quantum: %d\n\n"

#define USAGE "Usage:\n"
#define USAGE_DETAILS "./swap -f <filename> -a <algorithm> -m <memory> -q <quantum>\n"
#define ERROR "Error:\n"
#define ERROR_DETAILS "Incorrect arguments entered\n"

typedef struct opts_t Options;

struct opts_t {
	char *filename;  /* Input file name           */
	char *algorithm; /* Scheduling algorithm      */
	int memory;      /* Memory size to simulate   */
	int quantum;     /* Quantum time of a process */
};

/* Initialises an Option structure */
Options* initOptions(
);

/* Loads option arguments from command line using getopt.c */
void loadOptions(
	Options *o,
	int argc,
	char **argv
);

/* Displays the options entered */
void printOptions(
	Options *o
);

/* Prints usage instructions of the program */
void printUsage(
);

/* Prints error messages */
void printError();

#endif
