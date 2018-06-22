
/*
ID: afluria1
LANG: JAVA
TASK: rect1
*/

package shaping.regions;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Collection;
import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Scanner;
import java.util.Set;
import java.util.TreeSet;

public class ShapingRegions
{

    public static void main(String[] args) throws FileNotFoundException
    {
        Scanner fin = new Scanner(new File("rect1.in"));
        
        
    }
}


class Rect
{
    int x, y, h, w;

    public Rect(int x, int y, int w, int h) {
        this.x = x;
        this.y = y;
        this.h = h;
        this.w = w;
    }    
    
    RectPair splitX(int xLine) throws Exception
    {
        if(xLine < this.x || xLine >= this.x + w)
            throw new Exception("line X="+xLine+" is not part of this rectangle");
        return new RectPair( new Rect(x,y,xLine-w, h), new Rect(xLine, y, x+w-xLine, h) );
    }
    
    RectPair splitY(int yLine) throws Exception
    {
        if(yLine < y || yLine >= y + h)
            throw new Exception("line Y="+yLine+" is not part of this rectangle");
        return new RectPair( new Rect(x, y, w, yLine-h), new Rect(x, yLine, w, y+h-yLine));
    }
    
}

class RectContainer
{
    LinkedList<Rect> list;
    TreeSet<Rect> treeByX;
    TreeSet<Rect> treeByY;
    
    public RectContainer()
    {
        list = new LinkedList<Rect>();
        treeByX = new TreeSet <Rect>(new RectComparator("x"));
        treeByY =  new TreeSet <Rect>(new RectComparator("y"));
    }
    public void addRect(Rect r)
    {
        list.add(r);
        treeByX.add(r);
        treeByY.add(r);
    }
    //find and remove all rectangles that are completely within a rectangular region
    public void removeInRange(Rect lo, Rect hi)
    {
        Collection<Rect> xList, yList, combined;
        
        //subset is based on the comparator, which is based on the start x, so
        //another dummy rectangle will need to be created.

        xList = treeByX.subSet(lo, hi);
        yList = treeByY.subSet(lo, hi);

        for(Rect r : xList)
        {
            if(r.x+r.w > hi.x)
                xList.remove(r);
        }
        for(Rect r : yList)
        {
            if(r.y + r.h > hi.y)
                yList.remove(r);
        }

        xList.retainAll(yList);
        combined=xList;
        
        list.removeAll(combined);
        xList.removeAll(combined);
        yList.removeAll(combined);

        
        
    }

    public void splitOverlappingX(int x, int ylo, int yhi)
    {
        Iterator<Rect> r = treeByX.iterator();
        Rect crnt = r.next();

           while(crnt.x + crnt.w < x)
               crnt = r.next();
    }

    public Set<Rect> getOverlapping(Rect region)
    {
        Iterator<Rect> r = treeByX.iterator();
        Set<Rect> overlapping = new TreeSet<Rect>();
        while(r.hasNext())
        {
            Rect crnt = r.next();

            //skip until you start finding overlapping
            if (crnt.x + crnt.w < region.x) continue;

            if (crnt.x  < region.x + region.w)
            {
                if(crnt.y + crnt.h > region.y || crnt.y < region.y + region.h)
                    overlapping.add(crnt);
            }
        }

        r = treeByY.iterator();
        while(r.hasNext())
        {
            Rect crnt = r.next();

            //skip until you start finding overlapping
            if (crnt.y + crnt.h < region.y) continue;

            if (crnt.y  < region.y + region.h)
            {
                if(crnt.x + crnt.w > region.x || crnt.x < region.x + region.w)
                    overlapping.add(crnt);
            }
        }
        return overlapping;
    }
}

class RectComparator implements Comparator<Rect>
{
    boolean compareX;

    public RectComparator(String s)
    {
        this.compareX = s.equals("x");
    }
    
    @Override
    public int compare(Rect r1, Rect r2)
    {
        Integer a, b;
        if(compareX)
        {
            a = r1.x;
            b = r2.x;
        }
        else
        {
            a = r1.y;
            b = r2.y;
        }
        return a.compareTo(b);
    }
}

class RectPair
{
    Rect a,b;
    public RectPair(Rect a, Rect b)
    {
        this.a = a;
        this.b = b;
    }
}