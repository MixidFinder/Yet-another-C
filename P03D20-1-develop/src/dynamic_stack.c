#include "data_structure.h"

int IsEmpty(t_dstack *stack) { return (stack->top < 0); }
int IsFull(t_dstack *stack) { return (stack->top == stack->size - 1); }
/*
    input: stack pointer
    output: NULL if empty, value otherwise
*/
char *Pop(t_dstack *stack) { return (IsEmpty(stack) ? NULL : stack->arr[stack->top--]); }
char *Peek(t_dstack *stack) { return (IsEmpty(stack) ? NULL : stack->arr[stack->top]); }

t_dstack *InitStack() {
    t_dstack *stack = malloc(sizeof(t_dstack));

    stack->arr = malloc(INIT_LEN * sizeof(char *));
    stack->size = INIT_LEN;
    stack->top = -1;
    return stack;
}

void FreeStack(t_dstack *stack) {
    free(stack->arr);
    free(stack);
}

void Push(t_dstack *stack, char *elem) {
    if (stack) {
        if (IsFull(stack)) {
            stack->arr = realloc(stack->arr, (stack->size *= 2) * sizeof(char *));
        }
        stack->top += 1;
        stack->arr[stack->top] = elem;
    }
}
