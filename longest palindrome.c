/*
ID: afluria1
LANG: C
TASK: calfflac
*/

#include <stdio.h>
#include <assert.h>
#define DEBUG 0
    

char rawstr[20001], sanstr[20001];
int strmap[20001];

int origlookup(int san)
{
    return strmap[san];
}

int main()
{
    FILE* fin = fopen("calfflac.in", "r");
    FILE* fout = fopen("calfflac.out", "w");
    int i=0, j, k, sl, ssl;
    int lstart=0, lend=0, tstart, tend;
    char c;
    
    assert(fin != NULL && fout != NULL);
    
    while((c=fgetc(fin)) != EOF)
    {
        rawstr[i] = c;
        i++;
    }
    
    rawstr[i] = '\0';
    assert(i < 20000);
    
    
    //put the sanitized version of the string in sanstr, and keep track of where
    //it came from in strmap
    
    for(i=0, j=0, sl=strlen(rawstr);i<sl;i++)
    {
        assert(rawstr[i] != '\0');
        assert(i >=0), assert(j>=0);
        assert(i < sl), assert(j < sl);
        
        if(isalpha(rawstr[i]))
        {
            sanstr[j] = tolower(rawstr[i]), strmap[j] = i;
            j++;
        }
    }
    //i will represent the starting point of the left side of the palidrome
    int skipflag=0;
    for(i=0, ssl=strlen(sanstr);i<ssl;i++)
    {
        
        if(sl-1-i < lend-lstart)
            break;
        
        assert(i >=0), assert(i < ssl);
        //the right side, k, back until it finds a match
        
        if(DEBUG)
            printf("Starting at i=%d\n", i);
        for(j=i, k=ssl-1; sanstr[j] != sanstr[k] && j<k; k--)
        {
            skipflag=0;
            //don't both testing a palindrome smaller that what's already been detected
            
            if(k-j < lend - lstart)
            {
                skipflag = 1;
                break;
            }
            
            if(DEBUG)
                printf("j=%d, k=%d\n, comparing %c against %c\n", j, k, sanstr[j], sanstr[k]);
                
            assert(j >=0), assert(j < ssl);
            assert(k >=0), assert(k < ssl);
        }
        if(k==j || skipflag)
            continue;

        tstart = j, tend = k;
        
        
        //don't both testing a palindrome smaller that what's already been detected
        if(k-j < lend - lstart)
            {
                continue;
            }
        
        for(;j<ssl && k >=0; j++, k--)
        {
            if(sanstr[j] != sanstr[k])
            {
                for(j=i; sanstr[j] != sanstr[k] && j<k; k--)
                    ;
                if(j>k)
                    break;
                else
                {
                    tstart = j, tend=k;
                    continue;
                }
            }
            if(DEBUG)
                printf("j=%d, k=%d\n, comparing %c against %c", j, k, sanstr[j], sanstr[k]);
            assert(j >=0), assert(j < ssl);
            assert(k >=0), assert(k < ssl);
            //palindrome found
            if(j >= k)
            {
                if(tend - tstart > lend - lstart)
                {
                    lend = tend;
                    lstart = tstart;
                    break;
                }
            }
        }
    }
    if(DEBUG)
    {
        printf("string map:\n");
        printf("lstart=%d, lend=%d\n", lstart, lend);
        for(i=0;i<sl;i++)
            printf("pos %d: %d\n", i, strmap[i]);
    }
    fprintf(fout, "%d\n", lend-lstart+1);
    for(i=strmap[lstart], j=strmap[lend];i<=j;i++)
        fprintf(fout, "%c", rawstr[i]);
        
    fprintf(fout, "\n");
    
    if(DEBUG)
        system("PAUSE");
        
    
    
    exit(0);
    
}
