import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Map;
import java.util.Set;

/**
 * @author Maxim Slyusarenko
 * @since 28.05.16
 */
public class LexerWriter {

    private final LLChecker checker;

    public LexerWriter(LLChecker checker) {
        this.checker = checker;
    }

    public void generateLexer() {
        try (OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream("mygen" + File.separator + "Lexer.java"))) {
            writer.write("import java.util.List;\nimport java.util.ArrayList;\nimport java.io.IOException;\nimport java.io.InputStream;\nimport java.text.ParseException;\nimport java.util.Set;\nimport java.util.Map;\nimport java.util.HashSet;\nimport java.util.HashMap;\n\n/* This code is generated */\npublic class Lexer {\n");
            writer.write("    private final InputStream is;\n");
            //writer.write("    private int curChar;\n");
            //writer.write("    private int prevChar;\n");
            //writer.write("    private int nextChar;\n");
            writer.write("    private int curPos;\n");
            writer.write("    private String curString;\n");
            writer.write("    private int curIndex;\n");
            writer.write("    private Token curToken;\n");
            writer.write("    private String lastMatchedRegexText;\n\n");
            writer.write("    public Lexer(InputStream is) throws ParseException {\n        this.is = is;\n        curPos = 0;\n        curIndex = -1;\n        curString = \"\";\n        lastMatchedRegexText = \"\";\n        nextChar();\n    }\n\n");
            writer.write("    private void nextChar() throws ParseException {\n        curPos++;\n        if (curIndex != curString.length() - 1) {\n");
            writer.write("            curIndex++;\n        } else {\n            curIndex++;\n            try {\n                ");
            writer.write("int tmpI = is.read();\n                curString += (tmpI == -1 ? \"END\" : (char) tmpI);\n            } catch (IOException e) {\n                ");
            writer.write("throw new ParseException(e.getMessage(), curPos);\n            }\n        }\n    }\n\n");
            writer.write("    private void skipSymbols() throws ParseException {\n");
            writer.write("        String tmpString = \"\" + curString.charAt(curIndex);\n        ");
            writer.write("while (");
            Set<String> skipRules = checker.getSkipRules();
            int i = 0;
            for (String skipRule : skipRules) {
                writer.write("tmpString.matches(\"" + skipRule + "\")");
                if (i < skipRules.size() - 1) {
                    writer.write(" || ");
                }
                i++;
            }
            writer.write(") {\n            nextChar();\n            tmpString = \"\" + curString.charAt(curIndex);\n        }\n    }\n\n");
            writer.write("    public void nextToken() throws ParseException {\n        ");
            /*writer.write("String tmpString = \"\" + curString.charAt(curIndex);\n        ");
            writer.write("while (");
            Set<String> skipRules = checker.getSkipRules();
            int i = 0;
            for (String skipRule : skipRules) {
                writer.write("tmpString.matches(\"" + skipRule + "\")");
                if (i < skipRules.size() - 1) {
                    writer.write(" || ");
                }
                i++;
            }
            writer.write(") {\n            nextChar();\n            tmpString = \"\" + curString.charAt(curIndex);\n        }\n        ");*/
            writer.write("skipSymbols();\n        ");
            writer.write("String currentString = \"\" + curString.charAt(curIndex);\n        int startIndex = curIndex;\n        int matchLength = 0;\n");
            Map<String, String> tokens = checker.getTokens();
            i = 0;
            String tokenName = "TOKEN_" + i;
            String tokenValue = tokens.get(tokenName);
            if (tokenValue == null) {
                throw new IllegalArgumentException("No tokens in grammar");
            }
            Set<String> givenRegexps = checker.getGivenRegexps();
            writer.write("        String beforeLast = lastMatchedRegexText;\n");
            writer.write("        while (");
            if (tokenValue.startsWith("_regexp")) {
                writer.write("currentString.matches(\"" + tokenValue.substring(7) + "\")");
            } else {
                writer.write("\"" + tokenValue + "\".startsWith(currentString)");
            }
            for (int j = 1; j < tokens.size(); j++) {
                tokenValue = tokens.get("TOKEN_" + j);
                if (tokenValue.startsWith("_regexp")) {
                    writer.write(" || currentString.matches(\"" + tokenValue.substring(7) + "\")");
                } else {
                    writer.write(" || \"" + tokenValue + "\".startsWith(currentString)");
                }
            }
            writer.write(") {\n");
            tokenValue = tokens.get("TOKEN_0");
            writer.write("            if (");
            if (tokenValue.startsWith("_regexp")) {
                writer.write("currentString.matches(\"" + tokenValue.substring(7) + "\")");
            } else {
                writer.write("\"" + tokenValue + "\".equals(currentString)");
            }
            for (int j = 1; j < tokens.size(); j++) {
                tokenValue = tokens.get("TOKEN_" + j);
                if (tokenValue.startsWith("_regexp")) {
                    writer.write(" || currentString.matches(\"" + tokenValue.substring(7) + "\")");
                } else {
                    writer.write(" || \"" + tokenValue + "\".equals(currentString)");
                }
            }
            //writer.write(") {\n                matchLength += currentString.length() - matchLength;\n            }\n            nextChar();\n");
            writer.write(") {\n                matchLength += currentString.length() - matchLength;\n");
            for (String givenRegexp : givenRegexps) {
                writer.write("                if (currentString.matches(\"" + givenRegexp + "\")) {\n");
                writer.write("                    lastMatchedRegexText = currentString;\n");
                writer.write("                }\n");
            }
            writer.write("            }\n            nextChar();\n");
            // block
            writer.write("            skipSymbols();\n            currentString += curString.charAt(curIndex);\n        }\n");
            writer.write("        currentString = currentString.substring(0, matchLength);\n        curString = curString.substring(curIndex);\n");
            writer.write("        curIndex = 0;\n");
            i = 0;
            while (i < tokens.size()) {
                tokenName = "TOKEN_" + i;
                tokenValue = tokens.get(tokenName);
                if (tokenValue.startsWith("_regexp")) {
                    writer.write("        if (currentString.matches(\"" + tokenValue.substring(7) + "\")) {\n");
                    //writer.write("            lastMatchedRegexText = currentString;\n");
                    writer.write("            curToken = Token." + tokenName + ";\n            return;\n        }\n");
                } else {
                    writer.write("        if (currentString.equals(\"" + tokenValue + "\")) {\n");
                    //writer.write("            curToken = Token." + tokenName + ";\n            return;\n        }\n");
                    writer.write("            lastMatchedRegexText = beforeLast;\n            curToken = Token." + tokenName + ";\n            return;\n        }\n");
                }
                i++;
            }
            writer.write("        throw new ParseException(\"Illegal character \" + curString.charAt(curIndex), curPos);\n    }\n\n");
            writer.write("    public Token curToken() {\n        return curToken;\n    }\n\n");
            writer.write("    public int curPos() {\n        return curPos;\n    }\n\n");
            writer.write("    public char curChar() {\n        return curString.charAt(curIndex);\n    }\n\n");
            writer.write("    public String getLastMatchedRegexText() {\n        return lastMatchedRegexText;\n    }\n");
            writer.write("}");
        } catch (IOException e) {
            System.err.println("Something comes wrong with creating lexer file, message: " + e.getMessage());
        }
    }
}
