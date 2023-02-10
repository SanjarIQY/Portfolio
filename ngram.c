#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int arr_length(char **p)
{    int sum = 0;
    for(int i = 0; p[i]; i++)
    {
        int j=0;
        while(p[i][j]){
            j++;
            sum++;
        }
    } return sum;
}

int length(char *p1)
{
    int i = 0;
    while(p1[i])
    {
        i++;
    } return i;
}

char* check(char **argv)
{ 
    int k = 0, j = 0;
    char* all = malloc(sizeof(char) * arr_length(argv));
    for(int i = 1; argv[i]; i++)
    {
        for(k = 0; argv[i][k]; k++) all[j++] = argv[i][k];      
    } return all;
}

int compare(char*p1, char p2)
{
    for(int i = 0; p1[i]; i++) if(p1[i] == p2) return 1;
    return 0;
}

char* putch(char *p1)
{
    int info, ind = 0;
    char *fixed = malloc(sizeof(char) * length(p1));
    for(int i = 0; p1[i]; i++)
    {
        if((info = compare(fixed,p1[i])) == 0) fixed[ind++] = p1[i];
    } return fixed;
}

void sort(char* p1, char* p2)
{
    int x[128] = {0};
    for(int i = 0; p1[i]; i++)
    {
        for(int j = 0; p2[j]; j++)
        {
            if(p1[i] == p2[j]) x[(int)p1[i]]++;
        }
    }
    
    for(int i = 0; i < 128; i++)
    {
        if(x[i] != 0) printf("%c:%d\n", i ,x[i]);
    }
}

int main(int argc, char **argv)
{
    if(argc){};
    char* original = check(argv);
    char* fixed = putch(original);
    sort(fixed, original);
}