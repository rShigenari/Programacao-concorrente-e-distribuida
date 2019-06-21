import java.util.Random;

class ProdThread extends Thread { 
	ProdEscalar parent = 0;
     ProdThread(ProdEscalar parent) { 
        this.parent = parent; 
    } 
}

class ProdEscalar { 
    ProdEscalar() { 					
       for (int i = 0; i < 100000; i++){
 	 vet1[i] = Math.random();  
 	 vet2[i] = Math.random(); 
	 }
					
       for (int i = 0; i < 100000; i++) 
            new ProdThread(this).start(); 	
				
}					
   int n = 100000, index = 0, sum = 0,  numThreads = 4, aux = 0; 				
   double[] vet1 = new double[n]; 
    double[] vet2 = new double[n];					
synchronized int getNextIndex() { 
    return index < n ? index++ : -1; 					
}						
synchronized void AdicionaPartes(double somaParcial) { 
    sum += somaParcial; 
    if (++aux == numThreads) 					
	System.out.println(sum);	
}

public void run() { 
        int i; 
	ProdEscalar parent = 0;
	double sum = 0; 
	for (i = 0; i< 100000; i++) 
 		   sum += parent.vet1[i] * parent.vet2[i]; 
	parent.AdicionaPartes(sum); 
}}
	


