#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int adress_write(char* p1)
{
    char *ox = malloc(2);
    ox = "0x";
    write(1, ox, 2);
    int i = 0;
    while(p1[i])
        write(1, &p1[i++], 1);
    return i + 2;
    free(ox);
}

char* adress(unsigned long num)
{
    char* res = malloc(sizeof(char) * 14);
    int i = 0;
    
    while(num != 0)
    {
        int rm = num % 16;
        if(rm < 10) 
        {
            res[i] = rm + '0';
        }
        else 
        {
            res[i] = rm + 87;
        }
        num /= 16;
        i++;
    }

    int k = 0;
    char *finalRes = malloc(sizeof(char)* strlen(res));
    for(int i = strlen(res) - 1; i >= 0; i--)
    {
        finalRes[k++] = res[i];
    }
    return finalRes;
    free(res);
    free(finalRes);
}

char* hecadecimal(int num)
{
    char* res = malloc(sizeof(char*));
    int i = 0;
    
    while(num != 0)
    {
        int rm = num % 16;
        if(rm < 10) 
        {
            res[i] = rm + '0';
        }
        else 
        {
            res[i] = rm + 55;
        }
        num /= 16;
        i++;
    }

    int k = 0;
    char *finalRes = malloc(sizeof(char) * strlen(res));
    for(int i = strlen(res) - 1; i != -1; i--)
    {
        finalRes[k++] = res[i];
    }
    return finalRes;
    free(res);
    free(finalRes);
}

char* octal(int num)
{
    char* res = malloc(sizeof(char));
    int i = 0;
    if(num < 0) num *= -1;
    while(num != 0)
    {
        res[i] = num % 8 + 48;
        num /= 8;
        i++;
    } 
    
    int k = 0;
    char *finalRes = malloc(sizeof(char) * strlen(res));
    for(int i = strlen(res) - 1; i != -1; i--)
    {
        finalRes[k++] = res[i];
    }
    return finalRes;
    free(res);
    free(finalRes);
}

int my_write(char* p1)
{
    int i = 0;
    while(p1[i])
        write(1, &p1[i++], 1);
    return i;
}

char* un_de(int a)
{
    if(a == 0) return "0";
    char *res = malloc(5);
    int i = 0;
    
    if(a < 0) a *= -1;
    while(a != 0)
    {
        res[i++] = a % 10 + 48;
        a = a / 10;
    }

    int k = 0;
    char *finalRes = malloc(sizeof(char) * strlen(res));
    for(int i = strlen(res) - 1; i != -1; i--)
    {
        finalRes[k++] = res[i];
    }
    return finalRes;
    free(res);
    free(finalRes);
}

char* int_to_char(int a)
{
    if(a == 0) return "0";
    char *res = malloc(5);
    int i = 0;
    int flag;
    if(a < 0) a *= -1, flag = 1;
    char minus = '-';
    
    while(a != 0)
    {
        res[i] = a % 10 + 48;
        a = a / 10;
        i++;
    }
    int length = strlen(res);
    if(flag == 1) 
        res[length] = minus;

    int k = 0;
    char *finalRes = malloc(sizeof(char) * strlen(res));
    for(int i = strlen(res) - 1; i != -1; i--)
    {
        finalRes[k++] = res[i];
    }
    return finalRes;
    free(res);
    free(finalRes);
}

int my_printf(char* ident, ...)
{
    va_list ap;
    va_start(ap, ident);
    int i = 0, count = 0;
    char *buff, *buff2, *buff3, *buff4, *buff5, *buff6;
    
    while(ident[i])
    {
        if(ident[i] == '%')
        {
            i++;
            if(ident[i] == 'c'){
                char charr = va_arg(ap, int);
                write(1, &charr,1);
                count++;
            }
            else if(ident[i] == 's')
            {
                buff = va_arg(ap, char*);
                if(buff == (char*)NULL){
                    buff = "(null)";
                }
                count += my_write(buff);
            }
            else if(ident[i] == 'd')
            {
                int digit = va_arg(ap, int);
                buff2 = int_to_char(digit);
                count += my_write(buff2);
            }
            else if(ident[i] == 'o')
            {
                int oct = va_arg(ap, int);
                buff3 = octal(oct);
                count += my_write(buff3);
            }
            else if(ident[i] == 'u')
            {
                int uns = va_arg(ap, int);
                buff4 = un_de(uns);
                count += my_write(buff4);
            }
            else if(ident[i] == 'x')
            {
                int x = va_arg(ap, int);
                buff5 = hecadecimal(x);
                count += my_write(buff5);
            }
            else if(ident[i] == 'p')
            {
                unsigned long p =  (unsigned long)va_arg(ap, void*);
                buff6 = adress(p);
                count += adress_write(buff6);
            }
        }   
        else
        {
            write(1,&ident[i],1);
            count++;
        } 
        i++;

    }
    va_end(ap);   
    return count;
    free(buff); free(buff2); free(buff3); free(buff4); free(buff5); free(buff6);
}


int main()
{
    my_printf("%p\n", "qwert");
    printf("%p", "qwert");
}