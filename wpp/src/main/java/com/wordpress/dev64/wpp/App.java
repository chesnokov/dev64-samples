package com.wordpress.dev64.wpp;

import java.awt.*;
import java.awt.datatransfer.*;
import java.io.IOException;

public class App implements ClipboardOwner {
    @Override
    public void lostOwnership(Clipboard clipboard, Transferable contents) {}

    private String getClipboardContents() {
        String result = "";
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        Transferable contents = clipboard.getContents(null);

        if ( contents != null && contents.isDataFlavorSupported(DataFlavor.stringFlavor ) ) {
            try {
                result = (String) contents.getTransferData(DataFlavor.stringFlavor);
            } catch( Exception ex ) {
                /*
                   Ignore exceptions here
                   If exception will happen then you will see it visually
                   No logs required I believe
                */
            }
            
        }
        return result;
    }

    /**
     * Place a String on the clipboard, and make this class the
     * owner of the Clipboard's contents.
     */
    private void setClipboardContents( String aString ) {
        StringSelection stringSelection = new StringSelection( aString );
        Clipboard clipboard = Toolkit.getDefaultToolkit().getSystemClipboard();
        clipboard.setContents( stringSelection, this );
    }
    
    public static void main(String [] args) {
        App app = new App();
        String input =  app.getClipboardContents();
        String output = Preprocessor.preprocess(input);
        app.setClipboardContents(output);
    }
}
