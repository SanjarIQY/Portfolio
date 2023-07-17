#include "queue_struct.h"
#include <stdlib.h>

void enque(queues** operators, char new_operator, int num)
{
    queues* new = (queues*)malloc(sizeof(queues));
    new->value = new_operator;
    new->operant = num; 
    new->next = NULL;

    if(*operators == NULL)
        *operators = new;
    else {
        queues* for_loop = *operators;
        while(for_loop->next != NULL)
            for_loop = for_loop->next;
        for_loop->next = new;
    }
}

void deque(queues** list)
{
    queues* temp = *list;
    *list = (*list)->next;
    free(temp);
}
