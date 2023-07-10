#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
 
typedef struct stack_d
{
    int operator;
    struct stack_d* next;
} stack;

typedef struct queue
{
    char operator;
    int operant;
    struct queue* next;
}queues;

stack* stack_list = NULL;
queues* queue_list = NULL;

int is_num(char p1)
{
    if(p1 >= 48 && p1 <= 57)
        return 1;

    return 0;
}

void push(stack** stack_list ,int option)
{
    stack* new = (stack*)malloc(sizeof(stack));
    new->operator = option;
    new->next = *stack_list;

    *stack_list = new;
}

int power(int num, int pw)
{
    int ret = 1;
    while(pw > 0)
    {
        ret *= num;
        pw--;
    }
    return ret;
}

int my_strlen(char* string)
{
    int i = 0;
    while(string[i] != '\0'){
        i++;
    }
    return i;
}

int  char_to_dec(char* str)
{
    int  num = 0;
    int i = 0;
    int  ind = power(10, my_strlen(str)) / 10;
    while(str[i])
    {
        num += (str[i] - 48) * ind;
        i++;
        ind /= 10;
    }
    return num;
}

void split_gaps(char* task)
{
    int length = my_strlen(task);
    for(int i = 0; i < length; i++)
    {
        if(task[i] == ' ')
        {
            int j = i;
            while(j < length)
            {
                task[j] = task[j + 1];
                j++;
            }
            i = 0;
            length--;
        }
    }
    task[length] = '\0';
}

int check_for_parantheses_error(char* task)
{
    for(int i = 0; i < my_strlen(task); i++)
    {
        if(task[i] == '(' && task[i + 1] == ')')
            return 1;
    }
    return 0;
}

int check_for_error(char* task)
{
    int count = 0;
    for(int i = 0; i < my_strlen(task); i++)
    {
        if(task[i] == '%' ||task[i] == '/' || task[i] == '*' || task[i] == '*' || task[i] == '-' || task[i] == '+')
        {
            count++;
            if(count > 2)
                return 1;
        }
        else
            count = 0;
    }
    return 0;
}

int counting_equals(char* task)
{
    for(int i = 0; i < my_strlen(task); i++)
    {
        if(task[i] == ' ')
            return 1;
    }
    return 0;
}

int check_for_divide_error(char* task)
{
    for(int i = 0; i < my_strlen(task); i++)
    {
        if(task[i] == '/' && task[i + 1] == '0')
            return 1; 
    }
    return 0;
}

int check_for_char_error(char* task)
{
    for(int i = 0; i < my_strlen(task); i++)
    {
        if(task[i] >= 65 && task[i] <= 90)
            return 1;
        else if(task[i] >= 97 && task[i] <= 122)
            return 1;
    }
    return 0;
}

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


void enque(queues** operators, char new_operator, int num)
{
    queues* new = (queues*)malloc(sizeof(queues));
    new->operator = new_operator;
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

int pop(stack** list)
{
    stack* temp = *list;
    int ret_num = temp->operator;
    *list = (*list)->next;
    free(temp);
    return ret_num;
}   

void deque(queues** list)
{
    queues* temp = *list;
    *list = (*list)->next;
    free(temp);
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

int check_for_minus(char* task, int index)
{
    int i = index - 1;
    int ind = 0;
    while(i >= 0)
    {
        if(is_num(task[i]) == 1)
            break;
        if(task[i] != ')' && task[i] != '(')
            ind++;
        i--;
    }
    return ind;
}

void operation_part(int left_side, int right_side, char operator)
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
            result = left_side / right_side;
            break;
        case '%':
            result = left_side % right_side;
            break;
    }
    push(&stack_list, result);
}

int check_for_one_number(char* task)
{
    for(int i = 0; i < my_strlen(task);i++)
    {
        if(is_num(task[i]) == 0)
            return 1;
    }
    return 0;
}

int math_part()
{
    while(1){
        while(queue_list->operator == '\0' && queue_list != NULL)
        {
            push(&stack_list, queue_list->operant);
            deque(&queue_list);
        }
        if(stack_list->next == NULL)
            return stack_list->operator;
        int right_side = pop(&stack_list);
        int left_side = pop(&stack_list);
        operation_part(left_side, right_side, queue_list->operator);
        if(queue_list->next != NULL){
            deque(&queue_list);
        }
        else  {
            return stack_list->operator;
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
            char* num = malloc(sizeof(char) * my_strlen(task));
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
            while(stack_list->operator != '('){
                enque(&queue_list, stack_list->operator, 0);
                pop(&stack_list);
            }
            pop(&stack_list);
        }
        else{
            flag += 1;
            if(flag < 2){
                while(stack_list != NULL && priority(stack_list->operator) >= priority(task[i])){
                    enque(&queue_list, stack_list->operator, 0);
                    pop(&stack_list);
                }
                push(&stack_list, task[i]);
            }
        }
        i++;
    }

    while(stack_list != NULL){
        enque(&queue_list,stack_list->operator, 0);
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
        char* task = malloc(sizeof(char) * my_strlen(argv[1]));
        strcpy(task, print_error(argv[1]));
        convert_to_posfix(task);
        printf("%d\n",math_part());
        free(task);
        return 0;
    }
    
}
