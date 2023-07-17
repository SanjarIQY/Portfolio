#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "./s_source/my_string_lib.h"
#include "./s_source/stack_struct.h"
#include "./s_source/queue_struct.h"
#include "./s_source/check_functions.h"

stack* stack_list = NULL;
queues* queue_list = NULL;

char* print_error(char* task)
{
    if(check_for_error(task) == 1){
        write(2, "parse error\n", 12);
        return NULL;
    }
    if(check_for_parantheses_error(task) == 1){
        write(2, "parse error\n", 12);
        return NULL;
    }
    if(check_for_divide_error(task) == 1){
        write(2, "divide by zero\n", 15);
        return NULL;
    }
    if(check_for_char_error(task) == 1)
    {
        write(2, "parse error\n", 12);
        return NULL;
    }
    if(counting_equals(task) > 0){
        split_gaps(task);
        return task;
    }
    return task;
}

int priority(char operator)
{
    if(operator == '(') 
        return 0;
    else if(operator == '-' || operator == '+')
        return 1;
    else if(operator == '/' || operator == '*')
        return 2;
    return -1;
}

int operation_part(int left_side, int right_side, char operator)
{
    int result = 0;
    switch (operator) {
        case '+':
            result = left_side + right_side;
            break;
        case '-':
            result = left_side - right_side;
            break;
        case '*':
            result = left_side * right_side;
            break;
        case '/':
            if(right_side == 0) 
                return 0;
            result = left_side / right_side;
            break;
        case '%':
            result = left_side % right_side;
            break;
    }
    push(&stack_list, result);
    return 1;
}

void math_part()
{
    while(1){
        while(queue_list->value == '\0' && queue_list != NULL)
        {
            push(&stack_list, queue_list->operant);
            deque(&queue_list);
        }
        if(stack_list->next == NULL)
        {
            printf("%d\n",stack_list->value);
            return;
        }
            
        int right_side = pop(&stack_list);
        int left_side = pop(&stack_list);
        if(operation_part(left_side, right_side, queue_list->value) == 0)
        {
            write(2, "divide by zero\n", 15);
            return;
        }
        if(queue_list->next != NULL){
            deque(&queue_list);
        }
        else  {
            printf("%d\n",stack_list->value);
            return;
        }
    }
}

void convert_to_posfix(char* task)
{
    int i = 0;
    int flag = 0;

    while(i < my_strlen(task)){
        if(is_num(task[i]) == 1){
            flag = 0;
            char* num = malloc(sizeof(char) * (my_strlen(task) + 1));
            fill_with_null(num, (my_strlen(task) + 1));
            int ind = 0;
            while(is_num(task[i]) == 1){
                num[ind++] = task[i];
                i++;
            }
            int number =  char_to_dec(num);
            if(check_for_minus(task,i - my_strlen(num)) >= 2)
                number *= -1;
            
            enque(&queue_list, '\0', number);
            // printf("num: %s\n", num);
            free(num);
            i--;
        }
        else if(task[i] == '(')
            push(&stack_list, '(');
        else if(task[i] == ')'){
            while(stack_list->value != '('){
                enque(&queue_list, stack_list->value, 0);
                pop(&stack_list);
            }
            pop(&stack_list);
        }
        else{
            flag += 1;
            if(flag < 2){
                while(stack_list != NULL && priority(stack_list->value) >= priority(task[i])){
                    enque(&queue_list, stack_list->value, 0);
                    pop(&stack_list);
                }
                push(&stack_list, task[i]);
            }
        }
        i++;
    }

    while(stack_list != NULL){
        enque(&queue_list,stack_list->value, 0);
        pop(&stack_list);
    }
}

int main(int argc, char** argv)
{
    if(argc){}
    if(check_for_one_number(argv[1]) == 0)
    {
        printf("%s\n", argv[1]);
        return 0;
    }
    
    if(print_error(argv[1]) == NULL)
        return 1;
    else{
        char* task = calloc(sizeof(char), (my_strlen(argv[1]) + 1));
        // fill_with_null(task, (my_strlen(argv[1]) + 1));
        my_strcpy(task, print_error(argv[1]));
        convert_to_posfix(task);
        math_part();
        free(task);
        return 0;
    }
}