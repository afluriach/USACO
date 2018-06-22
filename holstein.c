/*
ID: afluriac
PROB: holstein
LANG: C
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int solutionCombination[15];
int feedContents[15][25];
int vitaminReqs[25];
int nFeeds, nVitamins, minimumFeedCount=15;

int feedCount(int n)
{
    int i, feedC=0;
    for(i=0;i<nFeeds; i++)
    {
           if(n % 2 == 1)
           {
                feedC++;
            }
            n /= 2;
    }   
    return feedC;
}

void testSet(int subset)
{
       int crnt[25];
       memset(crnt, 0, 25*sizeof(int));
       int i, j, s;
       //for(i=0;i<25;i++)
       // printf("%d ", crnt[i]);
       // system("PAUSE");
        
       for(i=0,s=subset;i<nFeeds && subset > 0;i++)
       {
            if(s % 2)
            {
                for(j=0;j<nVitamins; j++)
                    crnt[j] += feedContents[i][j];   
            }
            s /= 2;
       }
       for(i=0;i<nVitamins;i++)
            if(crnt[i]<vitaminReqs[i])
                return;
        if(feedCount(subset) < minimumFeedCount)
        {
            minimumFeedCount = feedCount(subset);
                for(i=0;i<nFeeds; i++)
                {
                    solutionCombination[i] = (subset % 2);
                       subset /= 2;
                 }   
        }
}

int printResult(int n, FILE * fout)
{
    //printf("printing result %d\n", n);
    int i, isFirst=1;

    fprintf(fout, "%d ", minimumFeedCount);
    for(i=0;i<nFeeds; i++)
    {
           if(solutionCombination[i])
           {
                if(!isFirst)
                    fprintf(fout, " ");
                fprintf(fout, "%d", i+1);
                isFirst=0;
            }
    }
    fprintf(fout, "\n");
    
}

int main()
{
       FILE *fin=fopen("holstein.in", "r"), *fout=fopen("holstein.out", "w");
       int i, j, count;
       assert(fin!= NULL && fout != NULL);
       
       fscanf(fin, "%d", &nVitamins);
       for(i=0;i<nVitamins;i++)
            fscanf(fin, "%d", vitaminReqs+i);
       fscanf(fin, "%d", &nFeeds);
       for(i=0;i<nFeeds;i++)
            for(j=0;j<nVitamins; j++)
                fscanf(fin, "%d", &feedContents[i][j]);
                
        
       for(i=0, count = 1 << nFeeds; i < count; i++)
       {
            //printf("testing result %d\n", i);
           // system("PAUSE");
            testSet(i);
                    
       }
       printResult(i, fout);
       exit(0);
}
