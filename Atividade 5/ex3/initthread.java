class initthread extends Thread {
    int t;
    Compartilha comp;
    public initthread (String nome, int tempo, Compartilha c) {
	super(nome);
	t=tempo; 
	comp=c;
    }
    public void run () {
	for (; ;) { 
	    try {
		Thread.sleep(t); 
	    } catch ( InterruptedException ie) {
		System.err.println( ie.toString());
	    }
	    comp.Mostra(getName());
	}
    }
}
