#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct options 
{
    int a,t, at, minus_one;
} options;

typedef struct linked_list
{
    char *name;
    struct linked_list* next;
    struct stat info;
} listnode;

void print_line(listnode *node, int flag, int minus)
{
    if(flag == 1)
    {
        while(node)
        {
            if(minus == 0)  
                printf("%s  ", node->name);
            else if(minus == 1)
                printf("%s\n", node->name);
            node = node->next;
        }
    }
    else if(flag == 2)
    {
         while(node)
        {
            if(node->name[0] != '.')
            {
                if(minus == 0)  
                    printf("%s  ", node->name);
                else if(minus == 1)
                    printf("%s\n", node->name);
            }
            node = node->next;
        }
    }
    if(minus == 0)
        putchar('\n'); 
    free(node);
}

void new_list(listnode** list, char *name, struct stat info)
{
    listnode* node = (listnode*)malloc(sizeof(listnode));
    listnode* forward = *list;
    node->name = malloc(sizeof(char) * strlen(name));
    node->info = info;
    node->name = name;
    node->next = NULL;

    if(*list == NULL)
        *list = node;

    else
    {
        while(forward->next)
            forward = forward->next;
        forward->next = node;
    }
}

void swap(listnode *list1, listnode *list2)
{
    listnode *temp = (listnode*)malloc(sizeof(listnode));
    temp->name = malloc(sizeof(char) * strlen(list1->name));
    temp->info = list1->info;
    temp->name = list1->name;

    list1->name = list2->name;
    list1->info = list2->info;

    list2->info = temp->info;
    list2->name = temp->name;

    free(temp);
}

void sort_by_last_mod(listnode** list)
{
    listnode *node1 = *list;
    listnode *node2 = NULL;
    
    while(node1)
    {
        node2 = node1->next;
        while(node2)
        {
            if(node1->info.st_mtim.tv_sec == node2->info.st_mtim.tv_sec)
            {
                if(node1->info.st_mtim.tv_nsec <= node2->info.st_mtim.tv_nsec)
                    swap(node1, node2);
            }
            else if(node1->info.st_mtim.tv_sec < node2->info.st_mtim.tv_sec)
                    swap(node1, node2);
            node2 = node2->next;
        }
        node1 = node1->next;
    }
    free(node1);
    free(node2);
}

void sort_by_ascii(listnode* list)
{
    listnode *node1 = list;
    listnode *node2 = NULL;

    while(node1)
    {
        node2 = node1->next;
        while(node2)
        {
            if(strcmp(node1->name, node2->name) > 0)
                swap(node1, node2);
            node2 = node2->next;
        }
        node1 = node1->next;
    }
    free(node1);
    free(node2);
}

listnode* all_dirs(char *dir)
{
    listnode *list = NULL;
    DIR* directory;
    directory = opendir(dir);
    struct dirent* page;

    while((page = readdir(directory)))
    {
        struct stat info;
        stat(page->d_name, &info);
        new_list(&list, page->d_name, info);
    }
    return list;
    free(list);
    closedir(directory);
    free(dir);
    free(page);
}

void print_option(options* sort, int minus, listnode* list)
{
    if(sort->at == 1 || (sort->a == 1 && sort->t == 1))
    {
        sort_by_last_mod(&list);
        print_line(list, 1, minus);
    }  
    else if(sort->t == 1)
    {
        sort_by_last_mod(&list);
        print_line(list, 2, minus);
    }
    else if(sort->a == 1)
    {
        sort_by_ascii(list);
        print_line(list, 1, minus);
    }
    else 
    {
        sort_by_ascii(list);
        print_line(list, 2, minus);
    }
    // free(list);
}

void files_folders(char **arr, options* opt)
{
    listnode* files = NULL;
    listnode* folders = NULL;
    int file = 0, folder = 0, j = 0, k = 0;

    for(int i = 0; arr[i]; i++)
    {
        if(open(arr[i], O_RDONLY) > 0)
        {
            struct stat mode;
            stat(arr[i], &mode);            
            if(S_ISDIR(mode.st_mode))
            {
                new_list(&folders, arr[i], mode);
                folder++;
            }
            else
            {
                new_list(&files, arr[i], mode);
                file++;
            }
        }
        else {
            printf("ls: cannot access '%s': No such file or directory\n", arr[i]);
            j++;
        }
    }

    if(file)
    {
        print_option(opt, opt->minus_one, files);
    }
    
    if(folders)
    {
        sort_by_ascii(folders);
        while(folders)
        {
            if(file || j || folder > 1)
            {
                if(k != 0)
                        putchar('\n');
                printf("%s:\n", folders->name);
            }      
            listnode* new = all_dirs(folders->name);
            print_option(opt , opt->minus_one, new);
            folders = folders->next;
            k++;
        }
    }
    free(folders);
    free(files);
}

void out(options* opt, char** str, int j)
{
    if(j)
        files_folders(str, opt);
    else
        print_option(opt, opt->minus_one, all_dirs("."));
}

int main(int argc, char** argv)
{ 
    options input;
    input.a = 0; input.t = 0; input.at = 0; input.minus_one = 0;
    char** str = malloc(sizeof(char*) * argc); int j = 0;

    for(int i = 1; i < argc; i++) 
    {
        if(strcmp("-a", argv[i]) == 0)
            input.a++;
        else if(strcmp("-t", argv[i]) == 0)
            input.t++;
        else if(strcmp("-at", argv[i]) == 0 || strcmp("-ta", argv[i]) == 0 )
            input.at++;
        else if(strcmp("-1", argv[i]) == 0 )
            input.minus_one++;
        else {
            str[j] = malloc(strlen(argv[i]));
            strcpy(str[j], argv[i]);
            j++;
        }
    }
    out(&input, str, j);
    free(str);
}
