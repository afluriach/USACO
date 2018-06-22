/*
ID: afluriac
PROB: sort3
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
 
int sLen, seq[1000];


void printList()
{
    int i;
    for(i=0;i<sLen;i++)
        printf("%d ", seq[i]);
    printf("\n");
    system("PAUSE");
}

swap(int * a, int * b)
{
    //printList();
    int temp = *a;
    *a = *b;
    *b = temp;
 
}

int extras(int * arr, int count)
{
    int i;
    for(i=0;i<count;i++)
    {
        if(arr[count] != 1)
            return arr[count];
    }
}

int main()
{
       FILE *fin=fopen("sort3.in", "r"), *fout=fopen("sort3.out", "w");
       assert(fin!= NULL && fout != NULL);
       int i, j, oneCount=0, twoCount=0, threeCount=0, swaps=0;
       fscanf(fin, "%d", &sLen);
       for(i=0;i<sLen;i++)
        fscanf(fin, "%d", seq+i);

        for(i=0;i<sLen;i++)
        {
            switch(seq[i]){
                case 1:
                    oneCount++;
                    break;
                case 2:
                    twoCount++;
                    break;
                case 3:
                    threeCount++;   
            }
        }
        
        //swap ones and twos
        for(i=0;i<oneCount;i++)
        {
            for(j=0;j<twoCount;j++)
            {
                if(seq[i] == 2 && seq[oneCount+j] == 1)
                {
                    swap(seq+i, seq+oneCount+j);
                    swaps++;
                }
            }
        }
        
        
        
         //swap ones and threes;
        for(i=0;i<oneCount;i++)
        {
            for(j=0;j<threeCount;j++)
            {
                if(seq[i] == 3 && seq[oneCount+twoCount+j] == 1)
                {
                    swap(seq+i, seq+oneCount+twoCount+j);
                    swaps++;
                }
            }
        }
        
        //swap all ones into ones parition from either 2 or 3 partition
        
       for(i=0, j=oneCount;i<oneCount && j < sLen;i++, j++)
       {
            
            if(seq[i]==1){
                j--;
                continue;
            }
            if(seq[j] != 1){
                i--;
                continue;
            }
            swap(seq+i, seq+j);
            swaps++;
       }  
       
       //swap twos and threes
       
        for(i=0;i<twoCount;i++)
        {
            for(j=0;j<threeCount;j++)
            {
                if(seq[i+oneCount] == 3 && seq[oneCount+twoCount+j] == 2)
                {
                    swap(seq+i+oneCount, seq+oneCount+twoCount+j);
                    swaps++;
                }
            }
        }
        
        //printList();
        fprintf(fout, "%d\n", swaps);
        
       exit(0);
}
