/*
ID: afluria1
LANG: C
TASK: friday
*/

#include <stdio.h>
#define ISLEAP(y) ((y%4 == 0) && (y%100 != 0) || (y%400 == 0))

int main()
{
    FILE* fin = fopen("friday.in", "r");
    FILE* fout = fopen("friday.out", "w");
    
    int year, day, month, endyear, i, j, k, daycount[7], dotw=2;
    fscanf(fin, "%d", &endyear);
    endyear += 1900-1;
    
    for(i=0;i<7;i++)
        daycount[i] = 0;
    
    for(i=1900; i<=endyear;i++)
    {
        for(j=1;j<=12;j++)
        {
            for(k=1;k<=31;k++)
            {
                if(j==2)
                {
                    if(k>29 || (k> 28 && !ISLEAP(i)))
                        break;
                }
                if(k > 30 && (j==9 || j==4 || j==6 || j==11))
                {
                    break;
                }
                if(k > 31)
                {
                    break;
                }
                if(k==13)
                {
                    daycount[dotw]++;
                }
                dotw = (dotw+1) % 7;
            }
        } 
    }
    
    for(i=0;i<6;i++)
        fprintf(fout, "%d ", daycount[i]);
    fprintf(fout, "%d\n", daycount[6]);
    exit(0);    
}
