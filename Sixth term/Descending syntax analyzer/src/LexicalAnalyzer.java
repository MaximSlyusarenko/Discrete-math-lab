import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

public class LexicalAnalyzer {

    private final InputStream is;
    private int curChar;
    private int prevChar;
    private int curPos;
    private Token curToken;

    public LexicalAnalyzer(InputStream is) throws ParseException {
        this.is = is;
        curPos = 0;
        nextChar();
    }

    private void nextChar() throws ParseException {
        curPos++;
        try {
            prevChar = curChar;
            curChar = is.read();
        } catch (IOException e) {
            throw new ParseException(e.getMessage(), curPos);
        }
    }

    public void nextToken() throws ParseException {
        while (Character.isWhitespace(curChar)) {
            nextChar();
        }
        if (curChar >= 'a' && curChar <= 'z') {
            nextChar();
            curToken = Token.VAR;
        } else {
            switch (curChar) {
                case '(':
                    nextChar();
                    curToken = Token.LPAREN;
                    break;
                case ')':
                    nextChar();
                    curToken = Token.RPAREN;
                    break;
                case '!':
                    nextChar();
                    curToken = Token.NOT;
                    break;
                case '&':
                    nextChar();
                    curToken = Token.AND;
                    break;
                case '^':
                    nextChar();
                    curToken = Token.XOR;
                    break;
                case '|':
                    nextChar();
                    curToken = Token.OR;
                    break;
                case '[':
                    nextChar();
                    curToken = Token.OPENSQUAREBRACKET;
                    break;
                case ']':
                    nextChar();
                    curToken = Token.CLOSESQUAREBRACKET;
                    break;
                case -1:
                    curToken = Token.END;
                    break;
                default:
                    throw new ParseException("Illegal character " + (char) curChar, curPos);
            }
        }
    }

    public Token curToken() {
        return curToken;
    }

    public int curPos() {
        return curPos;
    }

    public char prevChar() {
        return (char) prevChar;
    }

    public char curChar() {
        return (char) curChar;
    }
}
