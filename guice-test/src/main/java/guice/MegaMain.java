package guice;

import com.google.inject.Guice;
import com.google.inject.Inject;
import com.google.inject.Injector;

/**
 */
public class MegaMain {
    private final MyMegaInterface mega;

    private final MyMegaInterface puper;

    @Inject
    public MegaMain(MyMegaInterface mega, @Puper MyMegaInterface puper) {
        this.mega = mega;
        this.puper = puper;
        System.out.println("MegaMain instance constructor");
    }

    public static void main(String [] args) {
        Injector injector = Guice.createInjector(new MegaModule());

        for(int i=0; i<10; i++) {
            MegaMain main = injector.getInstance(MegaMain.class);
            main.mega.run();
            main.puper.run();
        }
    }
}
