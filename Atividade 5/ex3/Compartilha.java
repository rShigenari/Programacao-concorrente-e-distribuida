import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;

class Compartilha {
	public synchronized void Mostra(String texto){ 
		System.out.print(texto);
		try {
			if (texto.compareTo("A")==0) 
				wait(); 
			if (texto.compareTo("C")==0) 
				wait(); 
			if ((texto.compareTo("E")==0)||(texto.compareTo("R")==0))
				notify();
			if (texto.compareTo("O")==0) 
				wait();
			
		} 
		catch ( InterruptedException ie) { 
			System.err.println( ie.toString());
		}
	}
}
