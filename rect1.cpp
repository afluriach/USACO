#include <cstdlib>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <list>


class line
{
public:
    //start and end are inclusive, meaning if
    //b directly follows a, a.end+1 = b.start
    int start, end, color;
    //for the first line of a row, prev = NULL
    //for the last line of a row, next = NULL
    line *next;
    line(int start, int end, int color)
    {
        this->start = start;
        this->end = end;
        this->color = color;
    }

     void insert(line ** head)
    {
        //insert this into the list pointed to by *head

        this->next = (*head);
        *head = this;
    }
    void print()
    {
        printf("start: %d, end: %d, color: %d\n", this->start, this->end, this->color);
    }
    void printrow()
    {
        for(line * crnt = this; crnt != NULL; crnt=crnt->next)
            crnt->print();
    }


    //given the head line of a row and a newline to add
    //add newline to the row, splitting and overwriting
    //existing parts of the line that occupy the
    //same area
    static void addline(line** head, line* newline)
    {
        for(line* l=*head, *prev = NULL; l != NULL; prev = l, l= l->next)
        {
            //skip all lines thatwill not overlap
            if (l->end < newline->start) continue;
            if (l->start > newline-> end) continue;

            line *front=NULL, *back=NULL;

            if(newline->start > l->start)
            {
                //there will be a piece of the old line in front of the
                //new one

                front = new line(l->start, newline->start -1, l->color);
                printf("new line created in front\n");
                front->print();
            }

            if(newline->end < l->end)
            {
                //there will be a piece of the old line behind the
                //new one

                back = new line(newline->end +1, l->end, l->color);
                printf("new line created in back\n");
                back->print();
            }


            //add front if it is not null
            //add back if it is not null

            if(front != NULL)
            front->insert(head);

            if (back != NULL)
            back->insert(head);

            printf("row after insertions:\n");

            (*head)->printrow();


            //delete

            if(l != *head)
            {
                assert(prev != NULL);
                //it shouldn't, if L is not the head
                prev->next = l->next;
            }
            else
                *head=l->next;

            delete l;

            printf("row after deleting L:\n");

            (*head)->printrow();




        }

        newline->insert(head);

        printf("row after inserting newline L:\n");

        (*head)->printrow();
    }
};

class row
{
public:
    std::list <line> lineList;

    void addline(int start, int end, int color)
    {

    }

} row;

//stores the whole thing
class surface
{
    int height, width;
    row ** rows;
    surface(height, width)
    {
        this->height = height;
        this->width = width;
        rows = new *row[height];
    }

    void addrect(llx, lly, urx, ury)
    {
        for(int lineNum = lly; lineNum <= ury; lineNum++)
        {
            rows[lineNum]->addline(llx, urx, color);
        }
    }
}

int main()
{
    FILE *fin, *fout;

    int width, height, nRects;

    fin = fopen("rect1.in", "r");
    fout = fopen("rect1.out", "w");
    assert(fin != NULL);
    assert (fout != NULL);

    line *lines[10000];

    int colorCount[2501];

    for(int i=0;i<=2500;i++) colorCount[i]=0;

    for(int i=0;i<10000;i++) lines[i] = NULL;

    fscanf(fin, "%d%d%d", &width, &height, &nRects);

    for(int i=0; i<nRects; i++)
    {
        int llx, lly, urx, ury, color;

        fscanf(fin, "%d%d%d%d%d", &llx, &lly, &urx, &ury, &color);


    }

    for(int i=0; i <= height; i++)
    {
        printf("row %d\n", i);
        for(line * crnt = lines[i]; crnt != NULL; crnt=crnt->next)
        {
            crnt->print();
            colorCount[crnt->color] += crnt->end - crnt->start+1;
        }
    }

    for(int i=0;i<2500; i++)
    {
        if(colorCount[i] != 0)
            fprintf(fout, "%d %d\n", i, colorCount[i]);
    }

}
