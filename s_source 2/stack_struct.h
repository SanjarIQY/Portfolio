#ifndef STACK_STRUCT_H
#define STACK_STRUCT_H

typedef struct stack_d
{
    int value;
    struct stack_d* next;
} stack;

void push(stack** stack_list ,int option);
int pop(stack** list);

#endif