import java.util.concurrent.Semaphore;

public class CalcThE {
	public static double vet1[] = new double[RunThE.N];
	public static double vet2[] = new double[RunThE.N];
    public static void main(String args[]) {
        int max_th = 2, i;
        int ratio = (RunThE.N/max_th);
        Thread[] th;
        RunThE[] rh;
        rh = new RunThE[max_th];
        th = new Thread[max_th];
        Semaphore sem = new Semaphore(1, true);
        
        for(i = 0; i < RunThE.N; i++) {
        	vet1[i] = (double) (Math.random()*10);
        	vet2[i] = (double) (Math.random()*10);
        }
        
        
        long startTime = System.currentTimeMillis();
        
        for(i=0; i<max_th; i++) {
            int end =  ((i!=(max_th-1)) ? ((ratio*(i+1))-1) : RunThE.N-1);
            rh[i] = new RunThE(ratio*i, end, sem);
            th[i] = new Thread(rh[i]);
            th[i].start();
        }

        try {
            for(i=0; i<max_th; i++) 
                th[i].join();            
        } catch (InterruptedException e)
        { System.out.println("Excecao"); }
        long calcTime = System.currentTimeMillis() - startTime;
        System.out.println("Resultado final=" + RunThE.somaTotal);
        System.out.println("Em " + calcTime + "ms.\n");
        
    }
}
