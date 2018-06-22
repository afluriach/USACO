/*
ID: afluria1
LANG: C
TASK: castle
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct SetNode{
	short int count, isRoot, height, x, y;
	struct SetNode * parent;
	char n, s, w, e;
} SetNode;

typedef struct {
	char dir;
	int h, w, max;
} Wall;

SetNode rooms[50][50];
int width, height;


SetNode * getRoot(SetNode * s)
{
	//printf("getting root of room %d-%d\n", s->x, s->y);
	while(!s->isRoot){
		s = s->parent;
		//printf("getting root of room %d-%d\n", s->x, s->y);
	}
//	printf("it is room %d-%d\n", s->x, s->y);
	return s;
}

int getCount(SetNode * s)
{
	//printf("count: %d root count %d\n", s->count, getRoot(s)->count);
	return getRoot(s)->count;
}
void join(SetNode *a, SetNode * b)
{
	
	//printf("attempting to joinroom %d-%d and %d-%d\n", a->x, a->y, b->x, b->y);
	
	SetNode * aR = getRoot(a);
	SetNode * bR = getRoot(b);
	/*
	if(aR->height == 0)
		assert(aR->count==1);
	if(aR->height != 0)
		assert(aR->count != 1);
	if(bR->height == 0)
		assert(bR->count==1);
	if(bR->height != 0)
		assert(bR->count != 1);
	*/
	//printf("which are actually roots: %d-%d and %d-%d\n", a->x, a->y, b->x, b->y);
	
	if(aR == bR){
		//printf("join not completed\n");
		return;
	}
	/*
	if(aR->height > bR->height)
	{
		aR->parent = bR;
		aR->isRoot = 0;
		bR->count += aR-> count;
	}
	else if(aR->height < bR ->height)
	{
		bR->parent = aR;
		bR->isRoot = 0;
		aR->count += bR->count;
	}
	else
	{
		bR->parent = aR;
		bR->isRoot = 0;
		aR->count += bR->count;
		aR->height++;
	}
	 */
	 
	bR->parent = aR;
	bR->isRoot = 0;
	int total = aR->count + bR->count;
	aR->count = bR->count = total;
	
	
	printf("joined %d-%d and %d-%d\n", a->x, a->y, b->x, b->y);
	
	 
	//printf("join completed\n");
}

void joinRooms()
{
	int i, j;
	//join rooms north-south
	for(i=0; i < width; i++)
	{
		for(j=0;j<height-1;j++)
		{
			assert(rooms[i][j].s == rooms[i][j+1].n);
			if(rooms[i][j].s)
				join(&rooms[i][j], &rooms[i][j+1]);
		}
	}
	
	//join rooms east-west
	for(i=0;i<width-1; i++)
	{
		for(j=0;j<height; j++)
		{
			assert(rooms[i][j].e == rooms[i+1][j].w);
			if(rooms[i][j].e)
				join(&rooms[i][j], &rooms[i+1][j]);
		}
	}
}

Wall * findWall()
{
	int i, j, max=0, h, w;
	char dir;
	
	//test rooms east-west
	for(i=0;i<width-1; i++)
	{
		for(j=0;j<height; j++)
		{
			if(!rooms[i][j].e)
			{
				int test = testJoin(&rooms[i][j], &rooms[i+1][j]);
				if(test > max || (test == max && i+1 < w) || (test==max && i+1 == w && j+1 > h) )
				{
					dir = 'E';
					max = test;
					w = i +1;
					h = j+1;
				}
			}
		}
	}
	
	//test rooms north-south
	for(i=0; i < width; i++)
	{
		for(j=0;j<height-1;j++)
		{
			if(!rooms[i][j].s)
			{
				int test = testJoin(&rooms[i][j], &rooms[i][j+1]);
				if(test > max || (test == max && i+1 < w) || (test==max && i+1 == w && j+2 >= h) ) 
				{
					dir = 'N';
					max = test;
					w = i+1;
					h = j + 2;
				}
			}
		}
	}
	
	Wall * wall = malloc(sizeof(Wall));
	wall->max = max;
	wall->w = w;
	wall->h = h;
	wall->dir = dir;
	return wall;
	
	
}

int findLargest()
{
	int i, j, max=0, temp;
	for(i=0;i<width;i++)
		for(j=0;j<height;j++)
		{
			temp=getCount(&rooms[i][j]);
			if(temp > max)
				max = temp;
		}
		return max;
}

int testJoin(SetNode * a, SetNode * b)
{
	//printf("Getting root of %d-%d\n", a->x, a->y);
	a = getRoot(a);
	//printf("It is: %d-%d\n", a->x, a->y);
	//printf("Getting root of %d-%d\n", b->x, b->y);
	b = getRoot(b);
//	printf("It is: %d-%d\n", b->x, b->y);
	if(a==b)
		return a->count;
	else
		return a->count + b->count;
	
}

int countRooms()
{
	int i, j, rootCount=0;
	for(i=0;i<width;i++)
		for(j=0;j<height;j++)
			if(rooms[i][j].isRoot)
				rootCount++;
	return rootCount;
}

int main()
{
	FILE *fin = fopen("castle.in", "r"), *fout = fopen("castle.out", "w");
	assert(fin != NULL && fout != NULL);
	fscanf(fin, "%d %d", &width, &height);
	
	int i, j, len;
	
	for(i=0;i<width;i++)
		for(j=0;j<height;j++){
			rooms[i][j].isRoot =1;
			rooms[i][j].count = 1;
			rooms[i][j].parent = NULL;
			rooms[i][j].height = 0;
			rooms[i][j].x = i+1;
			rooms[i][j].y = j+1;
		}
	
	for(i=0;i<height;i++)
	{
		for(j=0;j<width; j++)
		{
			int r;
			fscanf(fin, "%d", &r);
			
			rooms[j][i].w = !(r & 1);
			rooms[j][i].n = !(r>>1 & 1);
			rooms[j][i].e = !(r>>2 & 1);
			rooms[j][i].s = !(r>>3 & 1);
		}
	}
	
	joinRooms();
	Wall * w = findWall();
	fprintf(fout, "%d\n%d\n%d\n%d %d %c\n", countRooms(), findLargest(), w->max, w->h, w->w, w->dir);
	exit(0);
}