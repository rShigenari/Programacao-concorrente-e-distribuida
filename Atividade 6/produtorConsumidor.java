// Java program to implement solution of producer
// consumer problem.
import java.util.LinkedList;
 

public class produtorConsumidor
{
    public static void main(String[] args)    throws InterruptedException
    {

        final PC pc = new PC();
 
        // cria TP
        Thread tp1 = new Thread(new Runnable()
        {
            public void run()
            {
                try
                {
                    pc.produce();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });
        // cria TP
        Thread tp2 = new Thread(new Runnable()
        {
            public void run()
            {
                try
                {
                    pc.produce();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });
 
        // cria TC
        Thread tc1 = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                try
                {
                    pc.consume();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });
	 Thread tc2 = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                try
                {
                    pc.consume();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });

        Thread tc3 = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                try
                {
                    pc.consume();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });
	 Thread tc4 = new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                try
                {
                    pc.consume();
                }
                catch(InterruptedException e)
                {
                    e.printStackTrace();
                }
            }
        });
 
        // inicia as threads
        tp1.start();
        tp2.start();
        tc1.start();
        tc2.start();
        tc3.start();
        tc4.start();
 
        // t1 termina antes de t2
        tp1.join();
        tp2.join();
        tc1.join();
        tc2.join();
        tc3.join();
        tc4.join();
    }
 
    // produtor adiciona na fila
    public static class PC
    {
        LinkedList<Integer> list = new LinkedList<>();

        public void produce() throws InterruptedException
        { int N = 100;
            int value = (int)(100000000*Math.random());
            while (true)
            {
                synchronized (this)
                {
                    while (list.size()==N)
                        wait();
 
                    System.out.println("Produtor adiciona: "
                                                  + value);

 		    value = (int)(100000000*Math.random());
                    
 			//insere na fila
                    list.add(value);

			//notifica o TC
                    notify();

                    Thread.sleep(1000);
	            if(list.size()==N)
			System.out.println(-1);//quando atinge N, imprime -1
                }
            }
        }
 
        // chama o TC
        public void consume() throws InterruptedException
        {
            while (true)
            {
                synchronized (this)
                {
                    while (list.size()==0)
                        wait();
 
                    //retira o primeiro da fila
                    int val = list.removeFirst();
		     
 
                    System.out.println("Consumidor retira:"
                                                    + val);
                    notify();

                    Thread.sleep(1000);
                }
            }
        }
    }
}
