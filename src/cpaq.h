#ifndef _CPAQ_H_
#define _CPAQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>

#include <glitter.h>

typedef struct {
	void const **restrict Q;
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
int enqueue (
	cpaq_t *restrict q,
	void const *restrict elem)
__attribute__ ((nonnull (1, 2), nothrow, warn_unused_result)) ;

bool isempty (cpaq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

bool isfull (cpaq_t const *restrict q)
__attribute__ ((leaf, nonnull (1), nothrow, pure, warn_unused_result)) ;

void const *gethead (cpaq_t const *restrict q)
__attribute__ ((nonnull (1), nothrow, pure, warn_unused_result)) ;

void dumpq(
	cpaq_t const *restrict q,
	int i)
__attribute__ ((nonnull (1), nothrow)) ;

#ifdef __cplusplus
}
#endif

#endif /* _CPAQ_H_ */