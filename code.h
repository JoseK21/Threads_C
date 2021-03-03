#ifndef CODE_H_ 
#define CODE_H_

// STRUCT
struct Node
{
    int number;
    struct Node *next;
};

// ARRAY' LENGTH
int MAX_LENGTH = 100;

// INTERVAL
int MAX_RANGE = 256;
int MIN_RANGE = 0;

// ARRAY_1 INTERVAL (ms)
float INTERVAL_1 = 0.001;
float INTERVAL_2 = 0.005;

// Display Prints
int SHOW_PRINTS = 1;

#endif 