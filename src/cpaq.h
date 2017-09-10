#ifndef _CAQ_H_
#define _CAQ_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <sys/types.h>

typedef struct {
	void **Q;
	size_t n;
	size_t head;
	size_t tail;
} cpaq_t;

void init_queue (cpaq_t *q, void *arr, size_t n);
int alloc_queue (cpaq_t *q, size_t n) ;
void free_queue (cpaq_t *q) ;

/* ret type == elem type */
void *dequeue (cpaq_t *q) ;
/* returns err code */
int enqueue (cpaq_t *q, void *elem) ;
bool isempty (cpaq_t *q)
__attribute__ ((pure)) ;
bool isfull (cpaq_t *q)
__attribute__ ((pure)) ;
void *gethead (cpaq_t *q)
__attribute__ ((pure)) ;
void dumpq(cpaq_t *q, int i) ;

#ifdef __cplusplus
}
#endif

#endif /* _CAQ_H_ */