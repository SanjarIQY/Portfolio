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

void my_strcpy(char *dest, char *source)
{
    for(int i = 0; i < my_strlen(source); i++)
        dest[i] = source[i];
}

void my_strncpy(char *dest, char *source, int size)
{
    for(int i = 0; i < size; i++)
        dest[i] = source[i];
}

void fill_with_null(char *string, int size)
{
    for(int i = 0; i < size; i++)
        string[i] = '\0';
}