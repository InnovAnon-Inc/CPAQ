#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mmalloc.h>

#include <cpaq.h>

/*#define n (4)*/

/*
int Q[n];
int head = 0;
int tail = 0;
*/

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void init_queue (
   cpaq_t *restrict q,
   void const *arr[],
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
   void const **restrict arr = malloc (n * sizeof (void *));
   error_check (arr == NULL) return -1;
   init_queue (q, arr, n);
   return 0;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void free_queue (cpaq_t const *restrict q) {
   free (q->Q);
}

__attribute__ ((nonnull (1, 2), nothrow))
void enqueue (
   cpaq_t *restrict q,
   void const *restrict elem) {
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_cpaq (q);
   size_t chk_used = used_space_cpaq (q);
#endif
	/*puts ("enqueue ()");*/
   /*error_check (isfull (q) != false) return -1;*/
   assert (! isfull (q));
   q->Q[q->tail] = elem;
   q->tail = (q->tail + 1) % q->n;
   assert (chk_rem  - 1 == remaining_space_cpaq (q));
   assert (chk_used + 1 == used_space_cpaq      (q));
}

#ifdef TEST
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int enqueue_chk (cpaq_t *restrict q, void const *restrict e) {
   error_check (isfull (q) != false) return -1;
   enqueue (q, e);
   return 0;
}
#endif

__attribute__ ((nonnull (1), nothrow, warn_unused_result))
void const *dequeue (cpaq_t *restrict q) {
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_cpaq (q);
   size_t chk_used = used_space_cpaq (q);
#endif
   void const *restrict x;
   /*error_check (isempty (q) != false) return NULL;*/
   assert (! isempty (q));
   x = q->Q[q->head];
   q->head = (q->head + 1) % q->n;
   assert (chk_rem  + 1 == remaining_space_cpaq (q));
   assert (chk_used - 1 == used_space_cpaq      (q));
   return x;
}

#ifdef TEST
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result))
int dequeue_chk (cpaq_t *restrict q, void *restrict e) {
   error_check (isempty (q) != false) return -1;
   dequeue (q, e);
   return 0;
}
#endif

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isempty (cpaq_t const *restrict q) {
   if (q->head == q->tail) {
      assert (used_space_cpaq (q) == 0);
      assert (remaining_space_cpaq (q) == q->n - 1);
      return true;
   }
   assert (used_space_cpaq (q) > 0);
   assert (remaining_space_cpaq (q) < q->n - 1);
   return false;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
bool isfull (cpaq_t const *restrict q) {
   if (q->head == (q->tail + 1) % q->n) {
      assert (used_space_cpaq (q) == q->n - 1);
      assert (remaining_space_cpaq (q) == 0);
      return true;
   }
   assert (used_space_cpaq (q) < q->n - 1);
   assert (remaining_space_cpaq (q) > 0);
   return false;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void const *gethead(cpaq_t const *restrict q) {
   assert (! isempty (q));
   return q->Q[q->head];
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void const *gethead_chk (cpaq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return gethead (q);
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
void const *gettail (cpaq_t const *restrict q) {
   assert (! isempty (q));
   return q->Q[(q->tail - 1) % q->array.n];
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
void *gettail_chk (cpaq_t const *restrict q) {
   error_check (isempty (q) != false) return NULL;
   return gettail (q);
}

TODO (generic dumpq)
/*
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
*/

__attribute__ ((const, leaf, nothrow, warn_unused_result))
size_t cpaqsz (size_t n) {
   return sizeof (cpaq_t) + datasz (sizeof (void *), n + 1);
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
size_t cpaqsz2 (cpaq_t const *restrict cpaq) {
   return cpaqsz (cpaq->n);
}

__attribute__ ((nothrow, warn_unused_result))
cpaq_t *ez_alloc_cpaq (size_t maxn) {
   void *restrict *restrict combined[2];
	size_t eszs[2];
	cpaq_t *restrict cpaq;
	void *restrict *restrict data;

	eszs[0] = sizeof (cpaq_t);
	eszs[1] = datasz  (sizeof (void **), maxn + 1);
   combined[0] = (void *restrict *restrict) &cpaq;
   combined[1] = (void *restrict *restrict) &data;
	error_check (mmalloc2 (combined, eszs,
		eszs[0] + eszs[1], ARRSZ (eszs)) != 0)
		return NULL;

   init_queue (cpaq, data, maxn);
	return cpaq;
}

__attribute__ ((leaf, nonnull (1), nothrow))
void ez_free_cpaq (cpaq_t *restrict cpaq) {
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wstrict-aliasing"
   mfree2 ((void *restrict) cpaq);
	#pragma GCC diagnostic pop
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result))
size_t used_space_cpaq (cpaq_t const *restrict cpaq) {
   size_t ret;
   if (cpaq->head <= cpaq->tail)
      ret = cpaq->tail - cpaq->head;
   else
      ret = cpaq->tail /*+ 1*/ + (cpaq->array.n - cpaq->head);
   assert (ret <= cpaq->n - 1);
   return ret;
}

__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result))
size_t remaining_space_cpaq (cpaq_t const *restrict cpaq) {
   size_t ret = cpaq->n - 1 - used_space_cpaq (cpaq);
   assert (ret <= cpaq->n - 1);
   return ret;
}

#ifdef TEST
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
size_t indexOf_cpaq (cpaq_t const *restrict cpaq,
	void const *restrict e) {
   /* check from head to tail */
   /* or check from head to end, then from 0 to tail */
   size_t ret;
   ssize_t r;
   array_t tmp;
   if (cpaq->head <= cpaq->tail) {
      init_array2 (&tmp, &(cpaq->array), cpaq->head,
         cpaq->tail - cpaq->head);
      return indexOf_array (&tmp, e);
   }
   init_array2 (&tmp, &(cpaq->array), cpaq->head, cpaq->array.n - cpaq->head);
   r = indexOf_array_chk (&tmp, e);
   if (r >= 0) return (size_t) r;
   init_array2 (&tmp, &(cpaq->array), (size_t) 0, cpaq->tail);
   return indexOf_array (&tmp, e);
}

__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result))
bool contains_cpaq (cpaq_t const *restrict cpaq,
	void const *restrict e) {
   array_t tmp;
   if (cpaq->head <= cpaq->tail) {
      init_array2 (&tmp, &(cpaq->array), cpaq->head,
         cpaq->tail - cpaq->head);
      return contains_array (&tmp, e);
   }
   init_array2 (&tmp, &(cpaq->array), cpaq->head, cpaq->array.n - cpaq->head);
   if (contains_array (&tmp, e)) return true;
   init_array2 (&tmp, &(cpaq->array), (size_t) 0, cpaq->tail);
   return contains_array (&tmp, e);
}

__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result))
ssize_t indexOf_cpaq_chk (cpaq_t const *restrict cpaq,
   void const *restrict e) {
   ssize_t ret;
   array_t tmp;
   if (cpaq->head <= cpaq->tail) {
      init_array2 (&tmp, &(cpaq->array), cpaq->head,
         cpaq->tail - cpaq->head);
      return indexOf_array_chk (&tmp, e);
   }
   init_array2 (&tmp, &(cpaq->array), cpaq->head, cpaq->array.n - cpaq->head);
   ret = indexOf_array_chk (&tmp, e);
   if (ret >= 0) return ret;
   init_array2 (&tmp, &(cpaq->array), (size_t) 0, cpaq->tail);
   ret = indexOf_array_chk (&tmp, e);
   assert (ret == (ssize_t) -1 || ret < (ssize_t) cpaq->array.n);
   assert (ret == (ssize_t) -1 || ret < (ssize_t) remaining_space_cpaq (cpaq));
   return ret;
}

__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result))
void *index_cpaq (cpaq_t const *restrict cpaq, size_t i) {
   return index_array (&(cpaq->array), (cpaq->head + i) % cpaq->array.n);
}
#endif

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void enqueues (cpaq_t *restrict q, void const *restrict *restrict e, size_t n) {
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_cpaq (q);
   size_t chk_used = used_space_cpaq (q);
#endif
   size_t diff = q->n - q->tail;
   assert (n == 0 || ! isfull (q));
   assert (remaining_space_cpaq (q) >= n);
   if (q->head > q->tail || n <= diff)
      memcpy (q->Q + q->tail, e, n);
   else {
      memcpy (e + 0   , q->Q + q->tail, diff);
      memcpy (e + diff, q->Q + 0,       n - diff);
   }
   q->tail = (q->tail + n) % q->n;
   assert (chk_rem  - n == remaining_space_cpaq (q));
   assert (chk_used + n == used_space_cpaq      (q));
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void dequeues (cpaq_t *restrict q, void *restrict e, size_t n) {
#ifndef NDEBUG
   size_t chk_rem  = remaining_space_cpaq (q);
   size_t chk_used = used_space_cpaq (q);
#endif
   size_t diff = q->n - q->head;
   assert (n == 0 || ! isempty (q));
   assert (used_space_cpaq (q) >= n);
   if (q->tail > q->head || n <= diff)
      memcpy (e, q->Q + q->head, n);
   else {
      memcpy (e + 0,    q->Q + q->head, diff);
      memcpy (e + diff, q->Q + 0,       n - diff);
   }
   q->head = (q->head + n) % q->n;
   assert (chk_rem  + n == remaining_space_cpaq (q));
   assert (chk_used - n == used_space_cpaq      (q));
}

__attribute__ ((leaf, nonnull (1, 2), nothrow))
void frees_cpaq (cpaq_t const *restrict cpaq, free_t f) {
   size_t i;
   if (cpaq->head <= cpaq->tail) {
	#pragma GCC ivdep
      for (i = cpaq->head; i != cpaq->tail; i++)
         f (cpaq->Q[i]);
   } else {
	#pragma GCC ivdep
      for (i = cpaq->head; i != cpaq->n;    i++)
         f (cpaq->Q[i]);
	#pragma GCC ivdep
      for (i = 0;          i != cpaq->tail; i++)
         f (cpaq->Q[i]);
   }
}
