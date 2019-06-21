class Manna_Pnueli_2Threads {

    static int counter = 0;

    static int request = 0;

    static int respond = 0;
    
    
    static class client extends Thread {
        public void run() {
            for(; ;) {
		//regiao nao critica
		while (respond != Thread.currentThread().getId()){
		    Thread.yield();
		    request=(int) Thread.currentThread().getId();
		}
		
		//regiao critica
		counter++;
		System.out.println("ID="+ Thread.currentThread().getId() + " counter=" + counter);
		respond = 0;
            }
        }
    }

    static class server extends Thread {
        public void run() {
	    for (; ;) {

		while(respond!=0){}
		request=0;

		while(request==0){}
		
		respond=request;

            }
        }
    }
    
    public static void main(String[] args) {
        Thread clientA = new client();
        Thread clientB = new client();
        Thread s = new server();

	clientA.start();
	clientB.start();	
	s.start();
    }
}
