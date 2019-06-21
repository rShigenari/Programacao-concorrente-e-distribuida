
import java.util.*;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

public class RunThE implements Runnable{
    static final Lock locker = new ReentrantLock();
    static final Condition conditionVariable = locker.newCondition();
     static int numThreads, tCounter, contLimit;
     static int cont;
     int id;

	public RunThE(int id, int numThreads, int tCounter, int contLimit){
        	
            	RunThE.numThreads = numThreads;
            	RunThE.tCounter = tCounter;
            	RunThE.contLimit = contLimit;
            	RunThE.cont = 0;
		this.id = id;
	}
    public int getCounter(){
	return RunThE.cont;
    }
	public void run(){
        if(this.id==1){
            // watch_cont()            
            System.out.println("Inicia watch_cont(): Thread " + id);            
            RunThE.locker.lock();
            try {
                if(RunThE.cont<RunThE.contLimit){
                    System.out.println("watch_cont(): Thread " + id + " em espera");
                    RunThE.conditionVariable.await();
                    System.out.println("watch_cont(): Thread " + id + " sinal de condicao recebido");
                    RunThE.cont += 125;
                    System.out.println("watch_cont(): Thread " + id + " contador atual = " + RunThE.cont);
                }
                RunThE.locker.unlock();
            } catch (InterruptedException e){
                    System.err.println(e.toString());
            }            
        }
        else{
            // inc_cont()
            System.out.println("Inicia inc_cont(): Thread " + id);
            for(int i=0; i<tCounter; i++){
                locker.lock();
                RunThE.cont++;
                if(RunThE.cont==RunThE.contLimit){
                  System.out.println("inc_cont(): Thread " + id + "contador= " + RunThE.cont + " limite atingido");
                  RunThE.conditionVariable.signal();
                  System.out.println("inc_cont(): Thread " + id + " contador= " + RunThE.cont + " sinal enviado");
                }
                System.out.println("inc_cont(): Thread " + id  + " contador = " + RunThE.cont + ", debloqueando");
                locker.unlock();
                try {
                    Thread.sleep(500);
                } catch (InterruptedException e){
                    System.err.println(e.toString());
                }
            }
        }
	}
}

