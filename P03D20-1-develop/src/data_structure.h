#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INIT_LEN 128

typedef unsigned int uint;

typedef struct s_dstack {
    char **arr;
    int size;
    int top;
} t_dstack;

t_dstack *InitStack();
void FreeStack(t_dstack *);
int IsEmpty(t_dstack *);
int IsFull(t_dstack *);
void Push(t_dstack *, char *);
char *Pop(t_dstack *);
char *Peek(t_dstack *);

#endif