/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : heap.h
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#ifndef HEAP_H
#define HEAP_H

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "other.h"

#define INITSIZE 20
#define LCHILD 2 * i + 1
#define RCHILD 2 * i + 2
#define PARENT ((int)i - 1) / 2

typedef struct node_t Node;
typedef struct heap_t Heap;

struct node_t {
	Elem *data;  /* Data Elem pointer          */
};

struct heap_t {
	Node *nodes; /* Heap as an array of Nodes  */
	uint num;    /* Number of elements in heap */
	uint size;   /* Maximum size of heap       */
};

/* Initialises the heap */
Heap *initHeap(
);

/* Increases the size of the heap */
Heap *growHeap(
	Heap *H
);

/* Inserts an element into the heap */
void insertIntoHeap(
	Heap *H,
	Elem *data,
	bool (*cmp)(Elem *parent, Elem *child)
);

/* Removes an element from the heap */
Elem* removeFromHeap(
	Heap *H,
	Elem *p,
	bool (*cmp)(Elem *parent, Elem *child),
	bool (*eq)(Elem *aim, Elem *data)
);

/* Removes the root of the heap */
Elem* removeTopFromHeap(
	Heap *H,
	bool (*cmp)(Elem *parent, Elem *child)
);

/* Prints the heap to stdout */
void displayHeap(
	Heap *H,
	Node *node,
	uint i,
	void (*pr)(Node *node, Node *left, Node *right)
);

/* Returns true if an element is found in the heap */
bool searchHeap(
	Heap *H,
	Node *node,
	uint i,
	Elem *p,
	bool (*eq)(Elem *aim, Elem *data)
);

/* Traverses the heap and returns data equal to the aim */
Elem* traverseHeap(
	Heap *H,
	Node *node,
	uint i,
	Elem *p,
	bool (*eq)(Elem *aim, Elem *data)
);

/* Swaps the last node up until the heap property is restored */
void siftUp(
	Heap *H,
	uint i,
	bool (*cmp)(Elem *parent, Elem *child)
);

/* Swaps the first node down until the heap property is restored */
void siftDown(
	Heap *H,
	uint i,
	bool (*cmp)(Elem *parent, Elem *child)
);

/* Swaps data contained in two nodes */
void swapData(
	Node *node1,
	Node *node2
);

#endif
