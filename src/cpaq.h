#ifndef _CPAQ_H_
#define _CPAQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

typedef struct {
	void *restrict *restrict Q;
	size_t n;
	size_t head;
	size_t tail;
} cpaq_t;

void init_queue (
	cpaq_t *restrict q,
	void const *arr[],
	size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

int alloc_queue (
	cpaq_t *restrict q,
	size_t n)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

void free_queue (cpaq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

/* ret type == elem type */
void const *dequeue (cpaq_t *restrict q)
__attribute__ ((nonnull (1), nothrow, warn_unused_result)) ;

/* returns err code */
void enqueue (
	cpaq_t *restrict q,
	void const *restrict elem)
__attribute__ ((nonnull (1, 2), nothrow)) ;

bool isempty (cpaq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool isfull (cpaq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

void const *gethead (cpaq_t const *restrict q)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;
/*
void dumpq(
	cpaq_t const *restrict q,
	int i)
__attribute__ ((nonnull (1), nothrow)) ;
*/
#ifdef TEST
int dequeue_chk (cpaq_t *restrict q, void *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;

int enqueue_chk (cpaq_t *restrict q, void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;
#endif
void const *gethead_chk (cpaq_t const *restrict q)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

void const *gettail (cpaq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

void *gettail_chk (cpaq_t const *restrict q)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t cpaqsz (size_t n)
__attribute__ ((const, leaf, nothrow, warn_unused_result)) ;

size_t cpaqsz2 (cpaq_t const *restrict cpaq)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

cpaq_t *ez_alloc_cpaq (size_t maxn)
__attribute__ ((nothrow, warn_unused_result)) ;

void ez_free_cpaq (cpaq_t *restrict cpaq)
__attribute__ ((leaf, nonnull (1), nothrow)) ;

size_t used_space_cpaq (cpaq_t const *restrict cpaq)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

size_t remaining_space_cpaq (cpaq_t const *restrict cpaq)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

#ifdef TEST
size_t indexOf_cpaq (cpaq_t const *restrict cpaq,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

bool contains_cpaq (cpaq_t const *restrict cpaq,
	void const *restrict e)
__attribute__ ((leaf, nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

ssize_t indexOf_cpaq_chk (cpaq_t const *restrict cpaq,
   void const *restrict e)
__attribute__ ((nonnull (1, 2), nothrow, pure, warn_unused_result)) ;

void *index_cpaq (cpaq_t const *restrict cpaq, size_t i)
__attribute__ ((leaf, nonnull (1), nothrow, pure, returns_nonnull, warn_unused_result)) ;
#endif

void enqueues (cpaq_t *restrict q,
	void const *restrict const *restrict e, size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

void dequeues (cpaq_t *restrict q,
	void const *restrict *restrict e, size_t n)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

typedef __attribute__ ((nonnull (1)))
void (*free_t) (void *restrict data) ;

void frees_cpaq (cpaq_t const *restrict cpaq, free_t cb)
__attribute__ ((leaf, nonnull (1, 2), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _CPAQ_H_ */