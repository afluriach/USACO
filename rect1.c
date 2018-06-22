/*
ID: afluria1
LANG: C
TASK: rect1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_RECTS 10000

typedef struct TreeNode
{
    TreeNode *l, *r;
    Rect * d;
}TreeNode;

typedef struct
{
    int x, y, h, w, endX, endY;
}Rect;


int startXComp(const void * a, const void * b)
{
    const Rect *x = a, *y = b;
    if(x->x < y->x)
        return -1;
    else if (x->x > y->x)
        return 1;
    else return 0;
}

int startYComp(const void * a, const void * b)
{
    const Rect *x = a, *y = b;
    if(x->y < y->y)
        return -1;
    else if (x->y > y->y)
        return 1;
    else return 0;
}

typedef struct
{
    int nRects;
    Rect arr[MAX_RECTS];
    TreeNode * startX;
    TreeNode * startY;
}RectList;

void addRect(RectList * rl, Rect * r)
{
    assert(rl->nRects < MAX_RECTS);
    memcpy(rl->arr+rl->nRects++, r, sizeof(Rect));
    addNode(rl->startX, rl->arr+nRects-1, startXComp);
    addNode(rl->startY, rl->arr+nRects-1, startYComp);
}


int main()
{
	FILE *fin=fopen("rect1.in", "r"), *fout=fopen("rect1.out", "w");
	assert (fin!= NULL && fout != NULL);


	
	exit(0);
}
