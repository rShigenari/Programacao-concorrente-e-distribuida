
public class CalcThE{
	public static void main(String[] args){
	int max_th = 3;
        int cont = 10;
        int cont_limit= 12;
		Thread[] thread;
		RunThE[] rh;
		
		rh = new RunThE[max_th];
		thread = new Thread[max_th];		

		for(int i=0; i<max_th; i++){
			int id = i+1;
			rh[i] = new RunThE(id,max_th,cont,cont_limit);
			thread[i] = new Thread(rh[i]);
			thread[i].start();
		}
		
	try {
            for(int i=0; i<max_th; i++)
                thread[i].join();           
        } catch (InterruptedException e)
        { System.out.println("Excecao"); }

        System.out.println("Espera em " + max_th + " threadreads. Valor final do contador = " + rh[0].getCounter() + ". Finalizado");
	}
}

