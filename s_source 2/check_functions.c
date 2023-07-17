#include "my_string_lib.h"

int is_num(char p1)
{
    if(p1 >= 48 && p1 <= 57)
        return 1;

    return 0;
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

int check_for_one_number(char* task)
{
    for(int i = 0; i < my_strlen(task);i++)
    {
        if(is_num(task[i]) == 0)
            return 1;
    }
    return 0;
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