package com.wordpress.dev64.wpp;

import java.text.CharacterIterator;
import java.text.StringCharacterIterator;

public class Preprocessor {

    /*
      This function iterates all characters in string
      For every character processSPecialSymbols is called.
      If character is processed then processSpecialSymbols will return true and
      value of next character for the loop.

      If character is not processed then it is ordinary character that should be
      added to as is to ouput string
     */
    static public String preprocess(String input) {
        StringCharacterIterator it = new StringCharacterIterator(input);
        final StringBuilder output = new StringBuilder();
        
        for(char c = it.first(); c!=CharacterIterator.DONE; ) {
            Result result=processSpecialSymbols(input, it, output); // try process special symbol
            if (result.result==true) { // character has been preprocessed
                c=result.ch;  // next character
                continue;
            }

            output.append(c); // add as is
            c=it.next();
        }
        
        return output.toString();
    }
    
    /*
       try to preprocess special symbols (actually full tag beginning special symbol)
       returns result with next character and updates iterator it (which is passed as second parameter).
       If symbol is not special then function will return false in the Result class and don't touch the
       iterator.
     */
    private static Result processSpecialSymbols(String testString, StringCharacterIterator it, StringBuilder output) {
        Result result = Result.FALSE_RESULT;
        for(SpecialSymbol s:SpecialSymbol.values()) {
            result=s.tryProcess(testString, it, output);
            if(result.result == true)
                break;
        }
        return result;
    }
}
