import java.util.concurrent.Semaphore;


class RunThE implements Runnable {
    final static int N = 100000;
    static double somaTotal = 0;
   
    private int inic, fim;
    private Semaphore semaforo;
    public double somaLocal;
   
   
    public RunThE(int inic, int fim, Semaphore semaforo) {
        super();       
        this.inic = inic;
        this.fim = fim;
        this.semaforo = semaforo;
    }
   
   
    public void run() {
        double soma = 0;
        for(int k=inic; k<fim; k++)
            soma += CalcThE.vet1[k] * CalcThE.vet2[k];
        
        try {
			semaforo.acquire();
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        somaTotal += soma;
        semaforo.release();
    }
}
