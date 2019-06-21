public class Monitor {
    public static void main (String args[]) {
	Compartilha comp=new Compartilha();
	initthread thread1,thread2,thread3,thread4,thread5;

	thread1 = new initthread("A",100,comp);
	thread2 = new initthread("C",200,comp);
	thread3 = new initthread("E",300,comp);
	thread4 = new initthread("R",300,comp);
	thread5 = new initthread("O",400,comp);

	thread1.start();
	thread2.start();
	thread3.start();
	thread4.start();
	thread5.start();

    }
}
