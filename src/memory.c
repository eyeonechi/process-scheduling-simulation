/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : memory.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include "memory.h"

/* Initialises a Memory structure */
Memory* initMemory(int capacity) {
	Memory *m = (Memory *)malloc(sizeof(m));
	assert(m);
	m->capacity = capacity;
	m->size = 0;
	m->list = initList(NULL, capacity);
	return m;
}

/* Loads a process into memory and returns true if successful */
bool loadIntoMemory(Memory *m, Process *data, char *algorithm, int time) {
	data->inMemory = time;
	m->size ++;
	m->recent = data->id;
	if (m->list) {
		if (strcmp(algorithm, "first") == 0) {
			return firstFit(m->list, data);
		} else if (strcmp(algorithm, "best") == 0) {
			return bestFit(m->list, data);
		} else {
			return worstFit(m->list, data);
		}
	}
	return false;
}

/* Removes a process from memory */
Process* removeFromMemory(Memory *m, int id) {
	bool (*eq)(int, Elem*) = &equalMemory;
	Process *p = removeData(m->list, id, eq);
	m->size --;
	return p;
}

/* Removes the oldest non-executing process sitting in memory */
Process* removeOldestFromMemory(Memory *m, List *run, int time, int quantum) {
	Process *p = NULL;
	if (run && isExpired(run->data, time, quantum)) {
		p = searchForOldest(m->list, NULL, NULL, time);
	} else {
		p = searchForOldest(m->list, NULL, run->data, time);
	}
	m->size --;
	if (p) {
		return removeFromMemory(m, p->id);
	}
	return NULL;
}

/* Searches for the oldest non-executing process sitting in memory */
Process* searchForOldest(List *node, Process *old, Process *run, int time) {
	if (node) {
		if (node->data) {
			/*
			if (run) {
				if (((Process *) node->data)->id != run->id) {
					if (old) {
						if ((time - ((Process *) node->data)->inMemory)
							> (time - old->inMemory)) {
							old = node->data;
						}
					} else {
						old = node->data;
					}
				}
			} else {
			*/
				if (old) {
					if ((time - ((Process *) node->data)->inMemory)
						> (time - old->inMemory)) {
						old = node->data;
					}
				} else {
					old = node->data;
				}
			}
		//}
		return searchForOldest(node->next, old, run, time);
	}
	return old;
}

/* Returns the first process in memory */
Process* getMemoryHead(Memory *m) {
	List *node = m->list;
	while (node) {
		if (node->data) {
			Process *p = popHead(&node, node->next, false);
			m->size --;
			return p;
		} else {
			node = node->next;
		}
	}
	return NULL;
}

/* Returns the last process in memory */
Process* getMemoryTail(Memory *m) {
	Process *p = popTail(m->list, NULL);
	m->size --;
	return p;
}

/* Merges adjacent free holes together */
void mergeHoles(Memory *m) {
	if (m->list) {
		recursiveMerge(m->list, m->list->next);
	}
}

/* Used by mergeHoles() */
void recursiveMerge(List *node, List *next) {
	if (node && next) {
		if (!node->data && !next->data) {
			node->next = next->next;
			node->size += next->size;
			List *list = next->next;
			free(next);
			recursiveMerge(node, list);
		} else {
			recursiveMerge(next, next->next);
		}
	}
}

/* Prints the memory to screen */
void displayMemory(Memory *m) {
	fprintf(stdout, HEADER_MEMORY);
	displayList(m->list, printMemory);
	fprintf(stdout, NEWLINE);
}

/* Helper print function */
void printMemory(List *node) {
	if (node && node->data) {
		Process *p = ((Process *)node->data);
		fprintf(stdout, PROCESS_MEMORY,
			p->id, p->size, p->inMemory);
	}
}

/* Returns true if memory is empty */
bool isEmpty(Memory *m) {
	return (m->list->size == m->capacity) ? true : false;
}

/* Retruns true if a process is present in memory */
bool inMemory(Memory *m, Process *p) {
	List *node = m->list;
	while (node) {
		if (((Process *)node->data)->id == p->id) {
			return true;
		}
		node = node->next;
	}
	return false;
}

/* Returns true if there is enough space in the memory for a process */
bool enoughSpace(Memory *m, void *data) {
	List *list = m->list;
	while (list) {
		if (!list->data) {
			if (list->size >= ((Process *) data)->size) {
				return true;
			}
		}
		list = list->next;
	}
	return false;
}

/* Returns the memory usage percentage */
int getMemorySize(Memory *m) {
	double size = 0;
	List *node = m->list;
	while (node) {
		if (node->data) {
			size += node->size;
		}
		node = node->next;
	}
	return roundUp(100 * size / m->capacity);
}

/* Returns true if a list node contains a matching process */
bool equalMemory(int id, Elem *data) {
	return (data) ? (id == ((Process *) data)->id) : false;
}

/* Returns true if a process is terminated */
bool isExpired(Process *p, int time, int quantum) {
	return ((time - p->execute) == quantum);
}

/* Returns the number of holes in memory */
int getHoles(Memory *m) {
	if (getMemorySize(m) == m->capacity) {
		return 0;
	}
	int holes = 0;
	List *node = m->list;
	while (node) {
		holes += (node->data) ? 0 : 1;
		node = node->next;
	}
	return holes;
}

/* Rounds up a number */
int roundUp(double num) {
	if (num > (int)num) {
		return (int)(num + 1);
	}
	return (int)num;
}

/* First Fit algorithm */
bool firstFit(List *node, void *data) {
	if (node) {
		if (!node->data) {
			if (node->size >= ((Process *)data)->size) {
				node->data = data;
				int remain = node->size - ((Process *)data)->size;
				node->size = ((Process *)data)->size;
				if (remain > 0) {
					List *new = initList(NULL, remain);
					new->next = node->next;
					node->next = new;
				}
				return true;
			} else {
				return firstFit(node->next, data);
			}
		} else {
			return firstFit(node->next, data);
		}
	}
	return false;
}

/* Best Fit algorithm */
bool bestFit(List *node, void *data) {
	List *best = recursiveBestFit(node, data, NULL);
	if (best) {
		best->data = data;
		int remain = best->size - ((Process *) data)->size;
		best->size = ((Process *) data)->size;
		if (remain > 0) {
			List *new = initList(NULL, remain);
			new->next = best->next;
			best->next = new;
		}
		return true;
	}
	return false;
}

/* Used by bestFit() */
List* recursiveBestFit(List *node, void *data, List *best) {
	if (node) {
		if (!node->data) {
			if (node->size >= ((Process *)data)->size) {
				if (best) {
					if (node->size < best->size) {
						best = node;
					}
				} else {
					best = node;
				}
			}
		}
		return recursiveBestFit(node->next, data, best);
	}
	return best;
}

/* Worst Fit algorithm */
bool worstFit(List *node, void *data) {
	List *worst = recursiveWorstFit(node, data, NULL);
	if (worst) {
		worst->data = data;
		int remain = worst->size - ((Process *) data)->size;
		worst->size = ((Process *) data)->size;
		if (remain > 0) {
			List *new = initList(NULL, remain);
			new->next = worst->next;
			worst->next = new;
		}
		return true;
	}
	return false;
}

/* Used by worstFit() */
List* recursiveWorstFit(List *node, void *data, List *worst) {
	if (node) {
		if (!node->data) {
			if (node->size >= ((Process *)data)->size) {
				if (worst) {
					if (node->size > worst->size) {
						worst = node;
					}
				} else {
					worst = node;
				}
			}
		}
		return recursiveWorstFit(node->next, data, worst);
	}
	return worst;
}
