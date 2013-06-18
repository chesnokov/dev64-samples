package guice;

/**
 */
public class SuperImplementation implements MyMegaInterface{

    public SuperImplementation() {
        System.out.println("SuperImplemetation constructor");
    }

    @Override
    public void run() {
        System.out.println("Super");
    }
}
