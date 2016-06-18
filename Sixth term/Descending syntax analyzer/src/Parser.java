import java.io.InputStream;
import java.text.ParseException;

public class Parser {

    private LexicalAnalyzer lex;

    private Tree S() throws ParseException {
        switch (lex.curToken()) {
            case VAR:
                return new Tree("S", T(), SPrime());
            case LPAREN:
                return new Tree("S", T(), SPrime());
            case NOT:
                return new Tree("S", T(), SPrime());
            case OPENSQUAREBRACKET:
                return new Tree("S", T(), SPrime());
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    private Tree T() throws ParseException {
        switch (lex.curToken()) {
            case VAR:
                return new Tree("T", F(), TPrime());
            case LPAREN:
                return new Tree("T", F(), TPrime());
            case NOT:
                return new Tree("T", F(), TPrime());
            case OPENSQUAREBRACKET:
                return new Tree("T", F(), TPrime());
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    private Tree SPrime() throws ParseException {
        switch (lex.curToken()) {
            case OR:
                lex.nextToken();
                return new Tree("S'", new Tree("|"), T(), SPrime());
            case RPAREN:
            case END:
                return new Tree("S'");
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    private Tree F() throws ParseException {
        switch (lex.curToken()) {
            case VAR:
                return new Tree("F", P(), FPrime());
            case LPAREN:
                return new Tree("F", P(), FPrime());
            case NOT:
                return new Tree("F", P(), FPrime());
            case OPENSQUAREBRACKET:
                return new Tree("F", P(), FPrime());
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    private Tree TPrime() throws ParseException {
        switch (lex.curToken()) {
            case XOR:
                lex.nextToken();
                return new Tree("T'", new Tree("^"), F(), TPrime());
            case OR:
            case RPAREN:
            case END:
                return new Tree("T'");
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    private Tree P() throws ParseException {
        switch (lex.curToken()) {
            case VAR:
                char curChar = lex.prevChar();
                lex.nextToken();
                return new Tree("P", new Tree("" + curChar));
            case NOT:
                lex.nextToken();
                return new Tree("P", new Tree("!"), P());
            case LPAREN:
                lex.nextToken();
                Tree between = S();
                if (lex.curToken() != Token.RPAREN) {
                    throw new ParseException(") expected at position", lex.curPos());
                }
                lex.nextToken();
                return new Tree("P", new Tree("("), between, new Tree(")"));
            case OPENSQUAREBRACKET:
                lex.nextToken();
                between = Q();
                if (lex.curToken() != Token.CLOSESQUAREBRACKET) {
                    throw new ParseException("] expected at position", lex.curPos());
                }
                lex.nextToken();
                return new Tree("P", new Tree("["), between, new Tree("]"));
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    private Tree Q() throws ParseException {
        switch (lex.curToken()) {
            case LPAREN:
                lex.nextToken();
                Tree between = S();
                if (lex.curToken() != Token.RPAREN) {
                    throw new ParseException(") expected at position", lex.curPos());
                }
                lex.nextToken();
                return new Tree("Q", new Tree("("), between, new Tree(")"));
            case OPENSQUAREBRACKET:
                lex.nextToken();
                between = Q();
                if (lex.curToken() != Token.CLOSESQUAREBRACKET) {
                    throw new ParseException("] expected at position", lex.curPos());
                }
                lex.nextToken();
                return new Tree("Q", new Tree("["), between, new Tree("]"));
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    private Tree FPrime() throws ParseException {
        switch (lex.curToken()) {
            case AND:
                lex.nextToken();
                return new Tree("F'", new Tree("&"), P(), FPrime());
            case XOR:
            case OR:
            case RPAREN:
            case END:
                return new Tree("F'");
            default:
                throw new ParseException("Unexpected symbol " + lex.prevChar() + " in position " + (lex.curPos() - 1), lex.curPos());
        }
    }

    public Tree parse(InputStream is) throws ParseException {
        lex = new LexicalAnalyzer(is);
        lex.nextToken();
        return S();
    }
}
