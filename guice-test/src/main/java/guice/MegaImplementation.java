package guice;

/**
 */
public class MegaImplementation implements MyMegaInterface {

    public MegaImplementation() {
        System.out.println("Megaimplementation constructor");
    }

    @Override
    public void run() {
        System.out.println("Mega implementation run");
    }
}
