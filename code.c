#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "code.h"
// #include "list.h"

pthread_t tid[2];
pthread_t tid_example_1[3];

int counter;
int done = 0;
pthread_mutex_t lock;

struct Node *head_1 = NULL;
struct Node *head_2 = NULL;

void insertAtEnd(struct Node **ref, int data)
{
   struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
   struct Node *last = *ref;

   new_node->number = data;
   new_node->next = NULL;

   if (*ref == NULL)
   {
      *ref = new_node;
      return;
   }

   while (last->next != NULL)
      last = last->next;

   last->next = new_node;
   return;
}

// Print the linked list
void printList(struct Node *node)
{
   while (node != NULL)
   {
      printf(" %d ", node->number);
      node = node->next;
   }
   printf("\n");
}

// Return the length linked list
int lengthList(struct Node *node)
{
   int length = 0;
   while (node != NULL)
   {
      length++;
      node = node->next;
   }
   return length;
}

// Return the value of a Node from linked list, by position
int getValue(struct Node *node, int position)
{
   int i = 0;
   int value = -1;
   while (node != NULL)
   {
      if (i == position)
      {
         value = node->number;
         break;
      }
      i++;
      node = node->next;
   }

   return value;
}

int getRandNumber()
{
   return rand() % MAX_RANGE + MIN_RANGE;
}

void *doSomeThing(void *arg)
{
   pthread_mutex_lock(&lock);

   unsigned long i = 0;
   counter += 1;
   printf("\n Job %d started\n", counter);

   for (i = 0; i < (0xFFFFFFFF); i++)
      ;

   printf("\n Job %d finished\n", counter);

   pthread_mutex_unlock(&lock);

   return NULL;
}

void *threadArray_1(void *arg)
{
   while (lengthList(head_1) <= MAX_LENGTH)
   {
      sleep(INTERVAL_1);
      insertAtEnd(&head_1, getRandNumber());
      printf("1 > Added..\n");
   }

   printf("Linked list 1: ");
   printList(head_1);

   return NULL;
}

void *threadArray_2(void *arg)
{
   while (lengthList(head_2) <= MAX_LENGTH)
   {
      sleep(INTERVAL_2);
      insertAtEnd(&head_2, getRandNumber());
      printf("2 > Added..\n");
   }

   printf("Linked list 2: ");
   printList(head_2);

   return NULL;
}

int main(void)
{
   srand(time(NULL));

   int count = 10000;
   int i = 0;
   int err;

   while (i < 2)
   {
      if (i == 0)
      {
         err = pthread_create(&(tid_example_1[i]), NULL, &threadArray_1, NULL);
      }
      else
      {
         err = pthread_create(&(tid_example_1[i]), NULL, &threadArray_2, NULL);
      }

      if (err != 0)
         printf("\ncan't create thread :[%s]", strerror(err));
      else
         printf("\n Thread created successfully\n");

      i++;
   }

   sleep(5);
   return 0;

   // ------------------- Example 1

   pthread_t tid_1;
   pthread_create(&tid_1, NULL, &threadArray_1, NULL);

   pthread_t tid_2;
   pthread_create(&tid_2, NULL, &threadArray_2, NULL);

   while (1 < 5000)
   {
      i++;
   }

   return 0;

   // ------------------- Example 2

   if (pthread_mutex_init(&lock, NULL) != 0)
   {
      printf("\n mutex init failed\n");
      return 1;
   }

   while (i < 2)
   {
      err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
      if (err != 0)
         printf("\ncan't create thread :[%s]", strerror(err));
      i++;
   }

   pthread_join(tid[0], NULL);
   pthread_join(tid[1], NULL);
   pthread_mutex_destroy(&lock);

   return 0;
}

// printf("Linked list: ");
// printList(head);

// printf("Value : %d\n", getValue(head, 1));
// printf("Length : %d\n", lengthList(head));