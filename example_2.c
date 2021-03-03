#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "constants.h"

pthread_t tid[2];
int counterShared;
pthread_mutex_t lock_mutex;

// Return a random number 0<->2
int getRandNumber()
{
   return (rand() % 2) * 0.01;
}

void *increaseCounter(void *arg)
{
   int myId = 2;

   unsigned long i = 0;
   pthread_t id = pthread_self();

   if (pthread_equal(id, tid[0]))
      myId = 1;

   if (myId == 1)
      printf("\n Job %s<%d>\033[0m started", GREEN, myId);
   else
      printf("\n Job %s<%d>\033[0m started", YELLOW, myId);

   for (size_t i = 0; i < ITERATIONS; i++)
   {
      pthread_mutex_lock(&lock_mutex);

      counterShared++;
      if (myId == 1)
         printf("\n %s<%d>\033[0m counterShared %s>\033[0m %d", GREEN, myId, GREEN, counterShared);
      else
         printf("\n %s<%d>\033[0m counterShared %s>\033[0m %d", YELLOW, myId, YELLOW, counterShared);

      pthread_mutex_unlock(&lock_mutex);

      sleep(getRandNumber());
   }

   if (myId == 1)
      printf("\n    %s Job %d finished \033[0m \n", GREEN, myId);
   else
      printf("\n    %s Job %d finished \033[0m \n", YELLOW, myId);


   return NULL;
}

int main(void)
{
   int i = 0;
   int err;

   if (pthread_mutex_init(&lock_mutex, NULL) != 0)
   {
      printf("\n mutex init failed\n");
      return 1;
   }

   while (i < 2)
   {
      err = pthread_create(&(tid[i]), NULL, &increaseCounter, NULL);
      if (err != 0)
         printf("\ncan't create thread :[%s]", strerror(err));
      i++;
   }

   pthread_join(tid[0], NULL);
   pthread_join(tid[1], NULL);
   pthread_mutex_destroy(&lock_mutex);

   return 0;
}