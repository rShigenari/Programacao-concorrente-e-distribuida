/* Manna-Anueli mutual exclusion algorithm */
class MannaPnueli4 {
    /*Numero de processos ocorrendo na secao critica */
    static int num = 0;
    /*processo A que requer entrar na secao critica */
    static int reqa = 0;
    /* processo B que requer entrar na secao critica */
    static int reqb = 0;
    
    
    static class A extends Thread {
        public void run() {
            while (true) {
		if (reqb == -1)
		    reqa = -1;
		else
		    reqa = 1;
		while (reqb == reqa)
		    Thread.yield();
		num++;
		System.out.println("Thread A: " + num);
		reqa = 0;
            }
        }
    }

    static class B extends Thread {
        public void run() {
	    while (true) {
		if (reqa == -1)
		    reqb = 1;
		else
		    reqb = -1;
//		}
		while (reqa == -reqb)
		    Thread.yield();		
		num++;
        System.out.println("Thread B: " + num);
		reqb = 0;
            }
        }
    }
    
    public static void main(String[] args) {
        Thread A = new A();
        Thread B = new B();
	A.start();
	B.start();
    }
}
