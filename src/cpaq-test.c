#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cpaq.h"

#define N (4)

int main(void) {
   int arr[] = {101, 202, 303, 404, 505};
   int const *tmp;

   cpaq_t q;
   alloc_queue (&q, (size_t) N);

   dumpq(&q, 1);
   enqueue (&q, arr + 0);dumpq(&q, 2);
   enqueue (&q, arr + 1);dumpq(&q, 3);
   enqueue (&q, arr + 2);dumpq(&q, 4);
   enqueue (&q, arr + 3);dumpq(&q, 5);
   enqueue (&q, arr + 4);dumpq(&q, 6);
   /*memset (arr, 0, sizeof (arr));*/
   printf("%i\n", *(int const *) dequeue(&q));
      dumpq(&q, 7);
   printf("%i\n", *(int const *) dequeue(&q));
      dumpq(&q, 8);
   printf("%i\n", *(int const *) dequeue(&q));
      dumpq(&q, 9);
   tmp = (int const *) dequeue (&q);
   if (tmp == NULL) puts ("NULL");
   else printf("%i\n", *tmp);
      dumpq(&q, 10);
   tmp = (int const *) dequeue (&q);
   if (tmp == NULL) puts ("NULL");
   else printf ("%i\n", *tmp);
      dumpq(&q, 11);

   free_queue (&q);
   return EXIT_SUCCESS;
}