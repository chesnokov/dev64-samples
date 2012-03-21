package com.wordpress.dev64.wpp;

import java.text.StringCharacterIterator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/*
    This enumerator class contains list of special characters (specified by first character)
    Second parameter is the regular expression that specify special cases for &: &amp; &lt; &gt;  &nbsp
    If preprocessor will find & symbol than it must be replaced to &amp;
    But if it is not a single & but one of specified XML named entities than no preprocessing should be
    done. In this case ttyProcess method must return false
 */
public enum SpecialSymbol {

    LT('<', null) {
        Result tryProcess(String testString, StringCharacterIterator it, StringBuilder output) {
            Result result = FALSE_RESULT;
            if(it.current() == '<') {
                for(WordPressTag tag: WordPressTag.values()) {
                    result=tag.tryProcessTag(testString, it, output);
                    if(result.result == true)
                        return result;
                }
                output.append("&lt;");
                it.next();
                result=new Result(true, it.current());
            }
            return result;
        }
    },
    AMP('&', "^(&gt;|&lt;|&nbsp|&amp;)") {
        Result tryProcess(String string, StringCharacterIterator it, StringBuilder output) {
            Result result = Result.FALSE_RESULT;
            if (it.current() == '&') {
                int index = it.getIndex();
                Matcher m = pattern.matcher(string.substring(it.getIndex()));
                if(!m.find()) {
                    //output.append(m.group(1));
                    //it.setIndex(index+m.group(1).length());
                    //result = new Result(true, it.current());
                //} else {
                    output.append("&amp;");
                    it.next();
                    result = new Result(true, it.current());
                }
            }
            return result;
        }
    },
    GT('>', null) {
        Result tryProcess(String testString, StringCharacterIterator it, StringBuilder output) {
            Result result = FALSE_RESULT;
            if (it.current() == '>') {
                output.append("&gt;");
                it.next();
                result = new Result(true, it.current());
            }
            return result;
        }
    },
    SQUARE_BRACKET('[', "(^\\[source[^\\]]*\\][^\\[]*\\[/sourcecode\\])") {
        Result tryProcess(String string, StringCharacterIterator it, StringBuilder output) {
            Result result = FALSE_RESULT;
            if (it.current() == '[') {
                int index = it.getIndex();

                Matcher m = pattern.matcher(string.substring(it.getIndex()));
                if(m.find()){
                    output.append(m.group(1));
                    it.setIndex(index+m.group(1).length());
                    result = new Result(true, it.current());
                }
                return result;
            }
            return result;
        }
    };

    private final static Result FALSE_RESULT = new Result();
    char ch;
    String regExp;
    Pattern pattern;

    SpecialSymbol(char ch, String regExp) {
        this.ch = ch;
        this.regExp = regExp;
        if(regExp != null) {
            pattern = Pattern.compile(this.regExp);
        }
    }
    
    Result tryProcess(String testString, StringCharacterIterator it, StringBuilder output) {
        return FALSE_RESULT;
    }
}
