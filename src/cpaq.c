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

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_queue (
   cpaq_t *restrict q,
   void *restrict arr,
   size_t n) {
   q->Q = arr;
   q->n = n;
   q->head = 0;
   q->tail = 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
int alloc_queue (
   cpaq_t *restrict q,
   size_t n) {
   void *restrict arr = malloc (n * sizeof (void *));
   error_check (arr == NULL) return -1;
   init_queue (q, arr, n);
   return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_queue (cpaq_t *restrict q) {
   free (q->Q);
}

__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int enqueue (
   cpaq_t *restrict q,
   void const *restrict elem) {
	/*puts ("enqueue ()");*/
   error_check (isfull (q) != false) return -1;
   q->Q[q->tail] = elem;
   q->tail = (q->tail + 1) % q->n;
   return 0;
}

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
void const *dequeue (cpaq_t *restrict q) {
   void const *restrict x;
   error_check (isempty (q) != false) return NULL;
   x = q->Q[q->head];
   q->head = (q->head + 1) % q->n;
   return x;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isempty (cpaq_t const *restrict q) {
   return q->head == q->tail;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isfull (cpaq_t const *restrict q) {
   return q->head == (q->tail + 1) % q->n;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void const *gethead(cpaq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return q->Q[q->head];
}

__attribute__ ((nonnull (1), nothrow))
void dumpq(
   cpaq_t const *restrict q,
   int i) {
   void const *restrict head = gethead (q);
   printf("i:%i, head:%i,", i, (int) q->head);
   if (head == NULL)
      printf(" tail:%i, Q[head]:NULL\n",
      (int) q->tail);
   else
      printf(" tail:%i, Q[head]:%i\n",
         (int) q->tail, *(int const *) head);
}