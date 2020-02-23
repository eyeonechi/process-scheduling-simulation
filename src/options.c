/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : options.c
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include "options.h"

/* Initialises an Option structure */
Options* initOptions() {
	Options *o = (Options *) malloc(sizeof(o));
	assert(o);
	o->filename = (char *) malloc(MAX_FILENAME_LEN * sizeof(o->filename));
	o->algorithm = (char *) malloc(MAX_ALGORITHM_LEN * sizeof(o->algorithm));
	assert(o->filename);
	assert(o->algorithm);
	o->memory = 0;
	o->quantum = 0;
	return o;
}

/* Loads option arguments from command line using getopt.c */
void loadOptions(Options *o, int argc, char **argv) {
	extern int optind;
	extern char *optarg;
	char input;
	if (argc <= 1) {
		printUsage();
		exit(EXIT_FAILURE);
	}
	while ((input = getopt(argc, argv, "f:a:m:q:")) != EOF) {
		switch ( input ) {
		case 'f':
			o->filename = optarg;
			break;
		case 'a':
			o->algorithm = optarg;
			break;
		case 'm':
			o->memory = atoi(optarg);
			break;
		case 'q':
			o->quantum = atoi(optarg);
			break;
		default:
			printUsage();
			break;
		}
	}
	if (!o->filename || o->memory == 0 || o->quantum == 0) {
		printError();
	}
}

/* Displays the options entered */
void printOptions(Options *o) {
	fprintf(stderr, FILENAME, o->filename);
	fprintf(stderr, ALGORITHM, o->algorithm);
	fprintf(stderr, MEMORY, o->memory);
	fprintf(stderr, QUANTUM, o->quantum);
}

/* Prints usage instructions of the program */
void printUsage() {
	fprintf(stderr, USAGE);
	fprintf(stderr, USAGE_DETAILS);
	exit(EXIT_FAILURE);
}

/* Prints error messages */
void printError() {
	fprintf(stderr, ERROR);
	fprintf(stderr, ERROR_DETAILS);
	printUsage();
	exit(EXIT_FAILURE);
}
