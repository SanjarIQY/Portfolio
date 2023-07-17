#include <stdlib.h>
#include "stack_struct.h"

void push(stack** stack_list ,int option)
{
    stack* new = (stack*)malloc(sizeof(stack));
    new->value = option;
    new->next = *stack_list;

    *stack_list = new;
}

int pop(stack** list)
{
    stack* temp = *list;
    int ret_num = temp->value;
    *list = (*list)->next;
    free(temp);
    return ret_num;
}   