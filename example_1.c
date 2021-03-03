#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "constants.h"

pthread_t tid[3];
pthread_t tid_example_1[3];

int ret1, ret2;

int counter;
int done = 0;
pthread_mutex_t lock;

struct Node *head_1 = NULL;
struct Node *head_2 = NULL;

// Custom printf
void printf_(int id, char msg[], char charMsg[], int intMsg)
{
    if (SHOW_PRINTS)
    {
        if (id == 0) // string
            printf(msg, charMsg);
        else if (id == 1) // int
            printf(msg, intMsg);
        else
            printf(msg, intMsg, intMsg);
    }
}

// Append new element to array
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
        printf_(1, " %d ", "", node->number);
        node = node->next;
    }
    printf_(0, "\n", "", -1);
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

// Return a random number
int getRandNumber()
{
    return rand() % MAX_RANGE + MIN_RANGE;
}

// Thread to array_1
void *threadArray_1(void *arg)
{
    pthread_t id = pthread_self();

    while (lengthList(head_1) <= MAX_LENGTH)
    {
        sleep(INTERVAL_1);
        insertAtEnd(&head_1, getRandNumber());
        printf_(1, "< 1 > Added number \n", "", -1);
    }

    printf_(1, "Linked list 1: ", "", -1);
    printList(head_1);

    if (pthread_equal(id, tid[0]))
    {
        printf_(1, "\n First thread processing done\n", "", -1);
        ret1 = 100;
        pthread_exit(&ret1);
    }
    else
    {
        printf_(1, "\n Second thread processing done\n", "", -1);
        ret2 = 200;
        pthread_exit(&ret2);
    }

    return NULL;
}

// Thread to array_2
void *threadArray_2(void *arg)
{
    pthread_t id = pthread_self();

    while (lengthList(head_2) <= MAX_LENGTH)
    {
        sleep(INTERVAL_2);
        insertAtEnd(&head_2, getRandNumber());
        printf_(1, "< 2 > Added number\n", "", -1);
    }

    printf_(1, "Linked list 2: ", "", -1);
    printList(head_2);

    if (pthread_equal(id, tid[0]))
    {
        printf_(1, "\n First thread processing done\n", "", -1);
        ret1 = 100;
        pthread_exit(&ret1);
    }
    else
    {
        printf_(1, "\n Second thread processing done\n", "", -1);
        ret2 = 200;
        pthread_exit(&ret2);
    }

    return NULL;
}

// Thread to final process
void *threadFinal(void *arg)
{
    int final_loop = 0;

    printf("Test %d\n", 1);
    while (final_loop < MAX_LENGTH)
    {
        int a = getValue(head_1, final_loop);
        int b = getValue(head_2, final_loop);
        int c = a ^ b;

        printf_(2, "\n %d : %c \n", "", c);
        final_loop++;
    }

    printf_(1, "\n Finish....\n", "", -1);

    return NULL;
}

// Main
int main(void)
{
    int i = 0;
    int err;
    int *ptr[2];

    srand(time(NULL));

    while (i < 2)
    {
        if (i == 0)
            err = pthread_create(&(tid[i]), NULL, &threadArray_1, NULL);
        else
            err = pthread_create(&(tid[i]), NULL, &threadArray_2, NULL);

        if (err != 0)
            printf_(0, "\ncan't create thread :[%s]", strerror(err), -1);
        else
            printf_(1, "\n Thread created successfully\n", "", -1);

        i++;
    }

    pthread_join(tid[0], (void **)&(ptr[0]));
    pthread_join(tid[1], (void **)&(ptr[1]));

    printf_(1, "\n return value from first thread is [%d]\n", "", *ptr[0]);
    printf_(1, "\n return value from second thread is [%d]\n", "", *ptr[1]);

    err = pthread_create(&(tid[2]), NULL, &threadFinal, NULL);
    if (err != 0)
        printf_(0, "\ncan't create thread :[%s]", strerror(err), -1);
    else
        printf_(1, "\n Thread FINAL created successfully\n", "", -1);

    pthread_join(tid[2], NULL);

    head_1 = NULL;
    head_2 = NULL;

    return 0;
}