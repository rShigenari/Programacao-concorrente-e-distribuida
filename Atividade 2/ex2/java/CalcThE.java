import java.util.Scanner;

public class CalcThE {


	final static int MaxThreads = 8;
	static int[] vet;

	
    public static void main(String args[]) {
        
	long N;

	Scanner entrada = new Scanner(System.in);
	N = entrada.nextInt();

	

	vet = new int[(int) N];



	for (int i = 0; i < N; i++) { 
		vet[i] = (int) (Math.random() * 100);
	}



	double max_total=0;

	int i;
        Thread[] th;
        RunThE[] rh;

        rh = new RunThE[MaxThreads];
        th = new Thread[MaxThreads];
        
        int ratio = ( ((int) N) /MaxThreads);

        
        long startTime = System.currentTimeMillis();

        for(i=0; i<MaxThreads; i++) {
	    int N2 = (int) N;
            int end =  ((i!=(MaxThreads-1)) ? ((ratio*(i+1))-1) : N2-1);
            rh[i] = new RunThE(ratio*i, end);
            th[i] = new Thread(rh[i]);
            th[i].start();
        }

        try {
            for(i=0; i<MaxThreads; i++) {
                th[i].join();
		if(rh[i].max> max_total)
			max_total = rh[i].max;
            }
        } catch (InterruptedException e)
        { System.out.println("Exception”); }

        long calcTime = System.currentTimeMillis() - startTime;
	System.out.println(max_total);
        
        System.out.println(calcTime);
        
    }
}
