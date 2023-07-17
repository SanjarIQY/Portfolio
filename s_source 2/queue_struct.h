#ifndef QUEUE_STRUCT_H
#define QUEUE_STRUCT_H

typedef struct queue
{
    char value;
    int operant;
    struct queue* next;
}queues;

void enque(queues** operators, char new_operator, int num);
void deque(queues** list);

#endif