#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

int missplaced(char* p1, char* p2)
{
    int k = 0;
    for(int i = 0; p1[i]; i++)
    {
        for(int j = 0; p2[j]; j++)
        {
            if(p1[i] != p2[i] && p1[i] == p2[j]) k++;
        }
    } 
    return k;
}

int wellpaced(char* p1, char* p2)
{
    int j = 0;
    for(int i = 0; p1[i];i++){
        if(p1[i] == p2[i]) 
        j++;
    } 
    return j;
}

int strLength(char* p1)
{
    int i = 0;
    while(p1[i]) i++;
    return i;
}

int congratz(char* p1, char* p2)
{
    if(p1[0] == p2[0] && p1[1] == p2[1] && p1[2] == p2[2] && p1[3] == p2[3]) 
    return 1;
    else
    return 0;
}

int my_strchar(char* p1, char p2){
    for(int i = 0; p1[i] != '\0'; i++)
    {
        if(p1[i] == p2) return 1;
    } 
    return 0;
}

char* my_scanf()
{
    char b = '>';
    write(1, &b, 1);
    fflush(stdout);
    char* p1 = malloc(4);
    char rea;
    int i = 0;
    
    while(read(0,&rea,1))
    {
        if(rea == '\n') 
        return p1;
        p1[i++] = rea;
    } 
    return 0;
}

int re(char* p1)
{
    for(int i = 0; p1[i]; i++)
    {
        if(p1[i] >= 48 && p1[i] <= 57) return 1;
    } return 0;
}

int issdigit(char* p1)
{
    if(strLength(p1) != 4) return 0;
    for(int i = 0; p1[i]; i++)
    {   
        if(!(p1[i] >= '0' && p1[i] < '9' ))
        return 0;
    } 
    return 1;
}

int sorting(char* p1)
{
    for(int i = 0; i < strLength(p1) - 1; i++)
    {
        for(int j = i + 1; p1[j]; j++) 
        {
            if(p1[i] == p1[j]) 
            return 0;
        } 
    } return 1;
}

void m_round(int at, char* first_code){
    char* result;
    int flag = 0;
    for(int i = 0; i < at;i++){
        printf("---\nRound %d\n", i); 
        result = my_scanf();
        if(result == NULL) return;
        if(sorting(result) == 0 || issdigit(result) == 0)
        {
            printf("Wrong input\n"); 
            i -= 1; 
            flag = 1;         
        } 
        if(congratz(result, first_code)){ printf("Congratz! You did it!\n");break;} 
        if(flag == 0) printf("Well placed pieces: %d\n", wellpaced(result, first_code));
        if(flag == 0) printf("Misplaced pieces: %d\n", missplaced(first_code, result));
        flag = 0;
    } 
}

void intro()
{
    char *a = malloc(sizeof(char) * 60);
    a = "Will you find the secret code?\nPlease enter a valid guess\n";
    for(int i = 0; i < 60; i++)
    {
        write(1,&a[i],1);
    }
}

char* ranndom()
{
    int i = 0;

    char* strr = malloc(sizeof(char) * 4);
    srand(time(NULL));
    while(i < 4)
    {
        char random =  rand() % 9 + 48;
        if(my_strchar(strr,random ) == 0){
            strr[i++] = random;
        }
    }
    return strr;
}

char* secret_code(char** p1)
{
    char* x = malloc(sizeof(char) * 4);

    for(int i = 0; p1[i]; i++)
    {
        if(strcmp(p1[i], "-c") == 0) x = p1[i + 1];
    } if(strcmp(x, "") == 0) x = ranndom();
    return x;
}

int find_attemps(char **p1)
{
    int attempts = 10;

    for(int i = 0; p1[i]; i++)
    {
        if(strcmp(p1[i], "-t") == 0) 
        attempts = atoi(p1[i + 1]);
    } 
    return attempts;
}

int main(int argc, char *argv[])
{
    if(argc == 0) return 0;
    int atemp = find_attemps(argv);
    char* first_code = secret_code(argv);
    if((sorting(first_code)) == 0) printf("Wrong input");
    else
    {
        intro();
        m_round(atemp, first_code);
    }
    // printf("%d", congratz("1234", "1254"));
}

