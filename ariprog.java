/*
ID: afluria1
LANG: JAVA
TASK: test
*/
import java.io.*;
import java.util.*;

class test {
  public static void main (String [] args) throws IOException
  {
    
    Scanner fin = new Scanner(new File("ariprog.in"));
    PrintStream fout = new PrintStream(new File("ariprog.out"));

    int n = fin.nextInt();
    int m = fin.nextInt();
    int limit = m*m*2;

    boolean[] bi = new boolean[125001];

    for(int i=0; i<=m;i++)
    {
        for(int j = 0; j<= m; j++)
        {
            bi[i*i+j*j] = true;
        }
    }

    int[][] sequences = new int[10000][2];
    int sequencesFound = 0;

    //every possible sequence start
    for(int i=0; i < limit; i++)
    {
        //every possible difference
        for(int j = 1; j < limit; j++)
        {
           if(isBi(i, j, n, bi))
           {
               sequences[sequencesFound][0] = i;
               sequences[sequencesFound][1] = j;
           }
        }
    }


  }

  public static boolean isBi(int start, int diff, int count, boolean[] bi)
  {
      for(int i = start, j=0; j<count; j++, i += diff)
      {
          if(!bi[i])
              return false;
      }
      return true;
  }

    private test() {
        throw new Error();
    }
}
