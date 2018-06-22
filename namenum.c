/*
ID: afluria1
LANG: C
TASK: namenum
*/

#include <stdio.h>
#include <stdlib.h>

struct node
{
    char name[16], number[16];
    struct node* l, *r, *s;
};

char digitlookup(char ch)
{
    if(ch >= 'W')
        return '9';
    if(ch >= 'T')
        return '8';
    if(ch >= 'P')
        return '7';
    if(ch >= 'M')
        return '6';
    if(ch >= 'J')
        return '5';
    if(ch >= 'G')
        return '4';
    if(ch >= 'D')
        return '3';
    else return '2';   
}

void insert(struct node * n, struct node**root)
{
    if(*root == NULL)
    {
        *root = n;
        return;
    }
    if(strcmp(n->number, (*root)->number) < 0)
        insert(n, &((*root)->l));
    else if(strcmp(n->number, ((*root)->number)) > 0)
        insert(n, &((*root)->r));
    else
        insert(n, &((*root)->s));
}

void create(FILE* fin, struct node**root)
{
    int i;
    char name[16];
    fscanf(fin, "%s", name);
    struct node* n = malloc(sizeof(struct node));
    n->l = NULL, n->r = NULL, n->s = NULL;
    strcpy(n->name, name);
    for(i=0;i<strlen(name);i++)
    {
        n->number[i] = digitlookup(name[i]);
    }
    insert(n, root);
}

void printall(struct node* root, FILE* fout)
{
    if(root == NULL)
        return;
    fprintf(fout, "%s\n", root->name);
    printall(root->s, fout);
}

int search(char* numstr, struct node* root, FILE* fout)
{
    if(root == NULL)
        return 0;
    if(strcmp(numstr, root->number) < 0)
        return search(numstr, root->l, fout);
    else if(strcmp(numstr, root->number) > 0)
        return search(numstr, root->r, fout);
    else
	 {
	 	printall(root, fout);
		return 1;
	}
}


int main()
{
    char number[16];
    FILE* fin = fopen("namenum.in", "r");
    FILE* fout = fopen("namenum.out", "w");
    FILE* dict = fopen("dict.txt", "r");
    
    struct node* root = NULL;
    
    while(!feof(dict))
    {
        create(dict, &root);
    }
    
    fscanf(fin, "%s", number);
    if(!search(number, root, fout))
	 	fprintf(fout, "NONE\n");
    
    exit(0);
}
