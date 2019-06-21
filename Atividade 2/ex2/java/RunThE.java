
class RunThE implements Runnable {/Users/rosangela/Documents/RunThE.java

    private int ini, fim;
    public double max;

   
    public RunThE(int ini, int fim) {
        super();       
        this.ini = ini;
        this.fim = fim;
    }
   
   
   
    public void run() {
	double result;
	max=0;
	for(int i = ini; i <= fim; i++){
		result = Math.log10( (double) CalcThE.vet[i] );
		if(result > max){
			max = result;	
		//	System.out.println("maximo " + max);
		}
	}	
    }


}
