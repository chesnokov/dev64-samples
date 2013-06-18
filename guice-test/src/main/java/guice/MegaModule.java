package guice;

import com.google.inject.AbstractModule;
import com.google.inject.Singleton;

/**
 */
public class MegaModule extends AbstractModule {
    @Override
    protected void configure() {
        bind(MyMegaInterface.class).to(MegaImplementation.class);
        bind(MyMegaInterface.class).annotatedWith(Puper.class).to(SuperImplementation.class);
    }
}
