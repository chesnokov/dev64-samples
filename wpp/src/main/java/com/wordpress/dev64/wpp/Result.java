package com.wordpress.dev64.wpp;

public class Result {
    public boolean result;  // true if tag matches
    public char ch;         // next character (if result is true)
    
    public static final Result FALSE_RESULT=new Result();

    Result() { result = false; ch = ' '; }
    Result(boolean result, char ch)
    {
        this.result = result;
        this.ch = ch;
    }
}
