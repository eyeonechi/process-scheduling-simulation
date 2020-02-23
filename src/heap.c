/* COMP30023 Computer Systems
 * Semester 1 2017
 * Project 1     : heap.c
 * Student Name  : Ivan Ken Weng Chee
 * Student ID    : 736901
 * Student Email : ichee@student.unimelb.edu.au
 */

#include "heap.h"

/* Initialises the heap */
Heap *initHeap() {
	Heap *H = (Heap *)malloc(sizeof(*H));
	assert(H);
	H->nodes = (Node *)malloc((H->size = INITSIZE) * sizeof(*(H->nodes)));
	assert(H->nodes);
	H->num = 0;
	uint i;
	for (i = 0; i < H->size; i ++) {
		(H->nodes + i)->data = (Elem *)malloc(sizeof((H->nodes + i)->data));
		assert((H->nodes + i)->data);
	}
	return H;
}

/* Increases the size of the heap */
Heap *growHeap(Heap *H) {
	uint i = H->size;
	H->nodes = (Node *)realloc(H->nodes, (H->size *= 2) * sizeof(H->nodes));
	assert(H);
	for (; i < H->size; i ++) {
		(H->nodes + i)->data = (Elem *)malloc(sizeof((H->nodes + i)->data));
		assert((H->nodes + i)->data);
	}
	return H;
}

/* Inserts an element into the heap */
void insertIntoHeap(Heap *H, Elem *data,
	bool (*cmp)(Elem *parent, Elem *child)) {
	if (H) {
		(H->nodes + H->num ++)->data = data;
		if (H->num == H->size) {
			H = growHeap(H);
		}
		siftUp(H, H->num - 1, cmp);
	}
}

/* Removes an element from the heap */
Elem* removeFromHeap(Heap *H, Elem *p, bool (*cmp)(Elem *parent, Elem *child),
	bool (*eq)(Elem *aim, Elem *data)) {
	if (H && H->num > 0) {
		Elem *x = traverseHeap(H, H->nodes, 0, p, eq);
		H->num --;
		siftDown(H, 0, cmp);
		return x;
	}
	return NULL;
}

/* Removes the root of the heap */
Elem* removeTopFromHeap(Heap *H, bool (*cmp)(Elem *parent, Elem *child)) {
	if (H && H->num > 0) {
		swapData(H->nodes, H->nodes + H->num - 1);
		H->num --;
		siftDown(H, 0, cmp);
		return (H->nodes + H->num)->data;
	}
	return NULL;
}

/* Prints the heap to stdout */
void displayHeap(Heap *H, Node *node, uint i,
	void (*pr)(Node *node, Node *left, Node *right)) {
	if (node && i < H->num) {
		pr(
			node,
			((uint) LCHILD < H->num) ? H->nodes + LCHILD : NULL,
			((uint) RCHILD < H->num) ? H->nodes + RCHILD : NULL
		);
		displayHeap(H, H->nodes + LCHILD, LCHILD, pr);
		displayHeap(H, H->nodes + RCHILD, RCHILD, pr);
	}
}

/* Returns true if an element is found in the heap */
bool searchHeap(Heap *H, Node *node, uint i, Elem *p,
	bool (*eq)(Elem *aim, Elem *data)) {
	return (traverseHeap(H, node, i, p, eq));
}

/* Traverses the heap and returns data equal to the aim */
Elem* traverseHeap(Heap *H, Node *node, uint i, Elem *p,
	bool (*eq)(Elem *aim, Elem *data)) {
	if (node && i < H->num) {
		if (eq(p, node->data)) {
			Elem *x = node->data;
			node->data = (H->nodes + H->num - 1)->data;
			return x;
		}
		Elem *x = traverseHeap(H, H->nodes + LCHILD, LCHILD, p, eq);
		return (x)? x : traverseHeap(H, H->nodes + RCHILD, RCHILD, p, eq);
	}
	return NULL;
}

/* Swaps the last node up until the heap property is restored */
void siftUp(Heap *H, uint i, bool (*cmp)(Elem *parent, Elem *child)) {
	if (i > 0 && PARENT >= 0
		&& cmp((H->nodes + i)->data, (H->nodes + PARENT)->data)) {
		swapData(H->nodes + i, H->nodes + PARENT);
		siftUp(H, (uint) PARENT, cmp);
	}
}

/* Swaps the first node down until the heap property is restored */
void siftDown(Heap *H, uint i, bool (*cmp)(Elem *parent, Elem *child)) {
	if (RCHILD < H->num) {
		/* Left child is greater than Right child */
		if (cmp((H->nodes + LCHILD)->data, (H->nodes + RCHILD)->data)) {
			if (cmp((H->nodes + LCHILD)->data, (H->nodes + i)->data)) {
				swapData(H->nodes + i, H->nodes + LCHILD);
				siftDown(H, (uint) LCHILD, cmp);
			} else {
				if (cmp((H->nodes + RCHILD)->data, (H->nodes + i)->data)) {
					swapData(H->nodes + i, H->nodes + RCHILD);
					siftDown(H, (uint) RCHILD, cmp);
				}
			}
		} else {
			if (cmp((H->nodes + RCHILD)->data, (H->nodes + i)->data)) {
				swapData(H->nodes + i, H->nodes + RCHILD);
				siftDown(H, (uint) RCHILD, cmp);
			}
		}
	} else if (LCHILD < H->num) {
		if (cmp((H->nodes + LCHILD)->data, (H->nodes + i)->data)) {
			swapData(H->nodes + i, H->nodes + LCHILD);
			siftDown(H, (uint) LCHILD, cmp);
		}
	}
}

/* Swaps data contained in two nodes */
void swapData(Node *node1, Node *node2) {
	Elem *data = node1->data;
	node1->data = node2->data;
	node2->data = data;
}
