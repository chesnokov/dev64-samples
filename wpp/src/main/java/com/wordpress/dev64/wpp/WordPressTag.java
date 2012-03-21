package com.wordpress.dev64.wpp;

import java.text.StringCharacterIterator;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public enum WordPressTag {
    STRONG("(^<strong>)"),
    STRONG_END("(^<\\/strong>)"),
    UL("(^<ul[^>]*>)"),
    UL_END("(^</ul>)"),
    LI("(^<li[^>]*>)"),
    LI_END("(^</li>)"),
    HREF("(^<a href[^>]*>)"),
    HREF_END("(^</a>)"),
    IMG("(^<img[^>]*>)"),
    IMG_END("(^</img>)"),
    TABLE("(^<table[^>]*>)"),
    TABLE_END("(^</table>)"),
    TR("(^<tr[^>]*>)"),
    TR_END("(^</tr>)"),
    TD("(^<td[^>]*>)"),
    TD_END("(^</td>)");

    String regExp;
    Pattern pattern;

    WordPressTag(String regExp) {
        this.regExp = regExp;
        this.pattern = Pattern.compile(this.regExp);
    }
    
    String getRegExp() {
        return this.regExp;
    }
    
    int getLen() {
        return this.regExp.length();
    }
    
    Result tryProcessTag(String string, StringCharacterIterator it, StringBuilder output) {
        Result result = Result.FALSE_RESULT;
        int index = it.getIndex();
        
        Matcher m = pattern.matcher(string.substring(it.getIndex()));
        if(m.find())
        {
            output.append(m.group(1));
            it.setIndex(index+m.group(1).length());
            result = new Result(true, it.current());
        }
        return result;
    }
}
