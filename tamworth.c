/*
ID: afluria1
LANG: C
TASK: ttwo
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>



typedef enum
{
    up=0, right, down, left
} direction;

char state[10][10][10][10][4][4];
char obs[10][10];
//first for the cows, x then y, second for the farmer, x then y

int canMove(int x, int y, direction d)
{
    switch(d)
    {
        case up:
            return (y+1 < 10 && !obs[x][y+1]);
        case down:
            return (y-1 >= 0 && !obs[x][y-1]);
        case left:
            return x - 1 >= 0 && !obs[x-1][y];
        case right:
            return x+1 < 10 && !obs[x+1][y];
        default:
            printf("Invalid direction.\n");
    }
}

int move(int * x, int * y, direction d)
{
    switch(d)
    {
        case up:
            *y += 1;
            break;
        case down:
            *y -= 1;
            break;
        case left:
            *x -= 1;
            break;
        case right:
            *x += 1;
            break;
        default:
            printf("Invalid direction.\n");
    }
}

void rotate(direction * d)
{
    //printf("rotate: before %d", *d);
    *d += 1;
    *d %= 4;
    //printf("after %d\n", *d);
}
int main()
{
	FILE *fin=fopen("ttwo.in", "r"), *fout=fopen("ttwo.out", "w");
	assert (fin!= NULL && fout != NULL);
	assert(sizeof(char)==1);
	memset(state, 0, 160000);
    memset(obs, 0, 100);
    
    //printf("up %d right %d down %d left %d", up, right, down, left);
    
    int i, j, cx, cy, fx, fy, minutes=0;
    direction cd = up, fd = up;
    char c;
    for(i=9;i >= 0; i--)
    {
        for(j=0;j<10;j++)
        {
            fscanf(fin, "%c", &c);
            switch(c)
            {
                case '*':
                    obs[j][i] = 1;
                    break;
                case 'C':
                     cx = j;
                     cy = i;
                     break;
                case 'F':
                    fx = j;
                    fy = i;
                    break;
            }   
        }
        fscanf(fin, "%c", &c);
    }
    

    while(1)
    {
        minutes++;
        printf("minute %d, FJ: %d,%d; cows: %d,%d\n", minutes, fx, fy, cx, cy);
        assert(!(cx < 0 || fx < 0 || cy < 0 || fy < 0));
        assert(!(cx >9 || fx > 9 || cy > 9 || fy > 9));
        if(state[cx][cy][fx][fy][cd][fd]){
            minutes=0;
            break;
        }
        state[cx][cy][fx][fy][cd][fd] = 1;
        
        if(canMove(cx, cy, cd))
            move(&cx, &cy, cd);
        else
            rotate(&cd);
            
        
        if(canMove(fx, fy, fd))
            move(&fx, &fy, fd);
        else
            rotate(&fd);
        
        if(fx == cx && fy == cy)
            break;
       
    }
    
    fprintf(fout, "%d\n", minutes);
	
	exit(0);
}
