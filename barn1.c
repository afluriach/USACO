/*
ID: afluria1
LANG: C
TASK: barn1
*/

#include <stdio.h>
#include <assert.h>
#define DEBUG 1

int occ[200], board[200], cows, stalls, boards;

int first(void)
{
    int i;
    for(i=0;i<stalls;i++)
    {
        if(occ[i])
        {
            return i;   
        }
    }
    return -1;
}

int last(void)
{
    int i;
    for(i=stalls-1;i>= 0; i--)
    {
        if(occ[i])
        {
            return i;
        }
    }
    return -1;   
}

int incomplete(void)
{
    int i;
    for(i=0;i<stalls;i++)
    {
        if(!occ[i] && board[i])
        {
            return 1;   
        }   
    }
    return 0;
}

//count the number of contiguous vacant boarded stalls, starting at 1, counting the starting point
int contig_count(int n)
{
    int i, count;
    for(i=n, count=0; i < stalls;i++)
    {
        if(!occ[i] && board[i])
        {
            count++;
        }
        else break;
    }
    return count;
}


int main()
{
    int i, j, temp, longest, count, longest_start;
    FILE* fin = fopen("barn1.in", "r");
    FILE* fout = fopen("barn1.out", "w");
    assert (fin != NULL && fout != NULL);
    
    fscanf(fin, "%d%d%d", &boards, &stalls, &cows);
    assert(cows <= stalls), assert(stalls <= 200);
        
    for(i=0;i<stalls;i++)
    {
        occ[i] = 0;
        board[i] = 0;   
    }
    
    for(i=0;i<cows;i++)
    {
        fscanf(fin, "%d", &temp);
        assert(temp > 0 && temp <= stalls); 
        occ[temp-1] = 1;
    }
    
    for(i=first(); i <= last(); i++)
    {
        board[i] = 1;
    }
    boards -= 1;
    
    while(boards > 0 && incomplete())
    {
        longest=0, longest_start=0;
        for(i=0;i<stalls;i++)
        {
            if(!occ[i] && board[i])
            {
                temp = contig_count(i);  
                if(temp > longest)
                {
                    longest = temp;
                    longest_start = i;
                } 
            }
        }
        for(i=longest_start, j=0; j < longest; i++, j++)
        {
            board[i] = 0;
        }
        boards--;
    }
    
    for(i=0, count=0; i < stalls; i++)
    {
        if(board[i])
        {
            count++;
        }
    }
    
    fprintf(fout, "%d\n", count);
    exit(0);
    
}
