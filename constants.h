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

// DISPLAY PRINTS
int SHOW_PRINTS = 1;

// ITERATIONS
int ITERATIONS = 100;

// COLORS
char GREEN[] = "\033[0;32m";
char YELLOW[] = "\033[0;33m";

#endif 