#if HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <cpaq.h>

#define N (4)

int main(void) {
#ifdef TEST
   int arr[] = {101, 202, 303, 404, 505};
   int const *tmp;

   cpaq_t q;
   if (alloc_queue (&q, (size_t) N) != 0) return EXIT_FAILURE;

   dumpq(&q, 1);
   if (enqueue (&q, arr + 0) != 0) return EXIT_FAILURE;dumpq(&q, 2);
   if (enqueue (&q, arr + 1) != 0) return EXIT_FAILURE;dumpq(&q, 3);
   if (enqueue (&q, arr + 2) != 0) return EXIT_FAILURE;dumpq(&q, 4);
   if (enqueue (&q, arr + 3) != 0) puts ("overflow");dumpq(&q, 5);
   if (enqueue (&q, arr + 4) != 0) puts ("overflow");dumpq(&q, 6);
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
#endif
   return EXIT_SUCCESS;
}