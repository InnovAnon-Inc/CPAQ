#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cpaq.h"

/*#define n (4)*/

/*
int Q[n];
int head = 0;
int tail = 0;
*/

void init_queue (cpaq_t *q, void *arr, size_t n) {
	q->Q = arr;
	q->n = n;
	q->head = 0;
	q->tail = 0;
}

int alloc_queue (cpaq_t *q, size_t n) {
	void *arr = malloc (n * sizeof (void *));
	if (arr == NULL) return -1;
	init_queue (q, arr, n);
	return 0;
}

void free_queue (cpaq_t *q) {
	free (q->Q);
}

int enqueue (cpaq_t *q, void *elem) {
	/*puts ("enqueue ()");*/
   if (isfull (q)) return -1;
   (char *) q->Q[q->tail] = elem;
   q->tail = (q->tail + 1) % q->n;
   return 0;
}

void *dequeue (cpaq_t *q) {
   void *x;
   if (isempty (q)) return NULL;
   x = q->Q[q->head];
   q->head = (q->head + 1) % q->n;
   return x;
}

__attribute__ ((pure))
bool isempty (cpaq_t *q) {
   return q->head == q->tail;
}

__attribute__ ((pure))
bool isfull (cpaq_t *q) {
   return q->head == (q->tail + 1) % q->n;
}

__attribute__ ((pure))
void *gethead(cpaq_t *q) {
   if (isempty (q)) return NULL;
   return q->Q[q->head];
}


void dumpq(cpaq_t *q, int i) {
   void *head = gethead (q);
   printf("i:%i, head:%i,", i, (int) q->head);
   if (head == NULL)
      printf(" tail:%i, Q[head]:NULL\n",
      (int) q->tail);
   else
      printf(" tail:%i, Q[head]:%i\n",
         (int) q->tail, *(int *) head);
}