/*
ID: afluria1
LANG: C
TASK: gift1
*/

#include <stdio.h>

int findpos(char names[][15], int numnames, char* name)
{
    int i, found=0;
    for(i=0;i<numnames;i++)
    {
        if(!strcmp(names[i], name))
        {
            found=1;
            break;
        }
    }
    if(found)
        return i;
    else 
        return -1;
}
    
int main()
{
    FILE* fin = fopen("gift1.in", "r");
    FILE *fout = fopen("gift1.out", "w");
    
    int i, j, balance[10], numrecip, amtgiven, numpeople;
    char namelist[10][15], givername[15], recipname[15];
    
    fscanf(fin, "%d", &numpeople);
    for(i=0;i<numpeople; i++)
        balance[i] = 0;
    
    for(i=0;i<numpeople;i++)
    {
        fscanf(fin, "%s", namelist[i]);
    }
    for(i=0;i<numpeople;i++)
    {
        fscanf(fin, "%s%d%d", givername, &amtgiven, &numrecip);
        if(numrecip != 0)
            balance[findpos(namelist, numpeople, givername)] -= (amtgiven/ numrecip)*numrecip;
        for(j=0;j<numrecip;j++)
        {
            fscanf(fin, "%s", recipname);
            int d;
            balance[findpos(namelist, numpeople, recipname)] += amtgiven/numrecip;
        }
    }
    for(i=0;i<numpeople;i++)
    {
        fprintf(fout, "%s %d\n", namelist[i], balance[i]);
    }
    exit(0);
}
