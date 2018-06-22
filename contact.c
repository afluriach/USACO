/*
ID: afluria1
LANG: C
TASK: contact
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#define MAX_SEQ 200000

//offset in the main array for the nth string of a particular length.
int offset [14] = {-1, 0,2,6,14,30,62,126,254,510,1022,2046,4094, 8191};
int sCount[8191], minString, maxString, nFrequencies, seqLen, nResults=0;
char seq[MAX_SEQ+1];

typedef struct
{
    char s[13];
    int sVal, len, freq;
}String;

void itob(char * dest, int len, int value)
{
    //printf("len:%d value:%d\n", len, value);
    assert(value >= 0);
    assert(value < pow(2,len));
    dest[len]='\0';
    int i;
    for(i=0;i<len;i++)
        dest[len-i-1] = value >> i & 1 ? '1' : '0';
}

String results[8191];

int sSort(const void * a, const void * b)
{
    const String * x = a;
    const String * y = b;

    //first sort by descending frequency
    if(x->freq > y->freq)
        return -1;
    else if(x->freq < y->freq)
        return 1;
    //then ascending length
    if(x->len < y->len)
        return -1;
    else if(x->len > y->len)
        return 1;

    //then integer value
    if(x->sVal < y->sVal)
        return -1;
    else if(x->sVal > y->sVal)
        return 1;
    else
        assert(0);

}

void addResults()
{
    int i, j, k;
    for(i=minString; i <= maxString; i++)
    {
        //j = scount pos, k = int value of string
        for(k=0, j=offset[i]; j < offset[i+1]; j++, k++)
        {
            if(sCount[j] >0)
            {
                results[nResults].sVal = k;
                results[nResults].len = i;
                results[nResults].freq= sCount[j];
                itob(results[nResults].s, i, k);
                nResults++;
            }
        }
    }
}

void addString(int value, int len)
{
    //printf("addString: length: %d value: %d\n", len, value);
    assert(value >= 0);
    assert(value < pow(2, len));
    //char c[13];
    //itob(c, len, value);
    //printf("Added string: %s\n", c);
    sCount[offset[len] + value]++;
}

int btoi(char * str, int len)
{
    int sum=0, i;
    for(i=0;i<len;i++,  str++){
        sum *= 2;
        if(*str == '1')
            sum++;
        else assert(*str == '0');
    }
    return sum;
}

int main()
{
	FILE *fin=fopen("contact.in", "r"), *fout=fopen("contact.out", "w");
	assert (fin!= NULL && fout != NULL);

    memset(sCount, 0, 8191*sizeof(int));

    fscanf(fin, "%d%d%d", &minString, &maxString, &nFrequencies);
    int i=0, j, k;
    while(1)
    {
        //int ch;
        //do
        //    ch = getc(fin);
        //while(ch != '1' && ch != '0' && ch != EOF);
        //ungetc(ch, fin);
        int c = fscanf(fin, " %s ", seq+i);
        if(c == EOF)
            break;
        else while (seq[i] != '\0') i++;
    }
    seqLen = i;

    //printf("first char of seq: %c\n", seq[0]);

    for(i=0;i<seqLen;i++)
        for(j=minString; j<=maxString && i + j <= seqLen ;j++)
            addString(btoi(seq+i, j), j);
    addResults();
    qsort(results, nResults, sizeof(String), sSort);

    j=0;
    int currentFreq, isFirst;
    //print up to nFrequencies different frequencies
    for(i=0;i<nFrequencies && j < nResults;i++)
    {
        currentFreq=results[j].freq;
        fprintf(fout, "%d\n", currentFreq);
        for(isFirst=1, k=0;results[j].freq == currentFreq && j < nResults; j++, k++){
            if(!isFirst)
                fprintf(fout, " ");
            else
                isFirst = 0;
            fprintf(fout, "%s", results[j].s);
            if(k % 6 == 5){
                fprintf(fout, "\n");
                isFirst = 1;
            }
        }
        if(k % 6 != 0)
            fprintf(fout, "\n");
    }
	exit(0);
}
