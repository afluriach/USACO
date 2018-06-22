/*
ID: afluria1
LANG: JAVA
TASK: fact4
*/
import java.io.*;
import java.util.*;
import java.math.*;


public class fact4
{
   public static void main(String [] args) throws IOException
   {
           PrintWriter fout = new PrintWriter(new FileWriter("fact4.out"));
        Scanner fin = new Scanner(new File("fact4.in"));
        int n = fin.nextInt();
        BigInteger b = BigInteger.ONE;
        BigInteger ib = BigInteger.ONE;
        for(int i=1; i <= n; i++, ib = ib.add(BigInteger.ONE)){
        	b = b.multiply(ib);
        	//System.out.println(ib + " " + b);
        }
        while( BigInteger.ZERO.equals(b.mod(BigInteger.TEN))){
        	b = b.divide(BigInteger.TEN);
        }
        long ans = b.mod(BigInteger.TEN).longValue();

        fout.println(ans);
        fout.close();
        //System.out.println(ans);
        System.exit(0);
   }

}
