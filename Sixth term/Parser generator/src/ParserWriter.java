import javafx.util.Pair;

import java.io.*;
import java.util.*;

/**
 * @author Maxim Slyusarenko
 * @since 29.05.16
 */
public class ParserWriter {

    private final LLChecker checker;

    public ParserWriter(LLChecker checker) {
        this.checker = checker;
    }

    public void generateParser() {
        try (OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream("mygen" + File.separator + "Parser.java"))) {
            writer.write("import javafx.util.Pair;\n\nimport java.util.List;\nimport java.util.ArrayList;\nimport java.io.*;\nimport java.text.ParseException;\nimport java.util.Set;\nimport java.util.Map;\nimport java.util.HashSet;\nimport java.util.HashMap;\n\n/* This code is generated */\npublic class Parser {\n");
            writer.write("    private Lexer lex;\n\n");
            Map<String, String> stringsToTokenNames = checker.getStringsToTokenNames();
            Map<String, List<Pair<List<String>, Map<String, List<String>>>>> rulesWithActions = checker.getRulesWithActions();
            Map<String, String> initBlocks = checker.getInitBlocks();
            for (Map.Entry<String, List<Pair<List<String>, Map<String, List<String>>>>> rulesWithActionsForUnterm : rulesWithActions.entrySet()) {
                String untermName = rulesWithActionsForUnterm.getKey().substring(1);
                String classUntermName = untermName.substring(0, 1).toUpperCase() + untermName.substring(1);
                writer.write("    private Pair<Tree, " + classUntermName + "ReturnsArguments> ");
                writer.write(untermName + "(" + classUntermName + "ParametersArguments params) throws ParseException {\n");
                writer.write("        " + classUntermName + "ReturnsArguments returns = new " + classUntermName + "ReturnsArguments();\n");
                writer.write("        " + classUntermName + "LocalsArguments locals = new " + classUntermName + "LocalsArguments();\n");
                writer.write("        Tree answerTree = new Tree(\"" + untermName + "\");\n");
                String initBlock = initBlocks.get("!" + untermName);
                if (initBlock != null) {
                    generateInitBlock(writer, initBlock, "!" + untermName);
                }
                writer.write("        switch (lex.curToken()) {\n");
                List<Pair<List<String>, Map<String, List<String>>>> rightParts = rulesWithActionsForUnterm.getValue();
                boolean wasEpsilonInFirst = false;
                String epsilonAction = "";
                for (Pair<List<String>, Map<String, List<String>>> rightPart : rightParts) {
                    List<String> rightPartList = rightPart.getKey();
                    List<String> listForGettingFirst = new ArrayList<>();
                    for (String item : rightPartList) {
                        String changedItem = item;
                        if (item.startsWith("!") && item.endsWith(")")) {
                            changedItem = changedItem.substring(0, changedItem.indexOf("("));
                            listForGettingFirst.add(changedItem);
                        } else {
                            listForGettingFirst.add(item);
                        }
                    }
                    Map<String, List<String>> rightPartUntermNames = rightPart.getValue();
                    Set<String> first = checker.getFirstRightPartOfRule(listForGettingFirst);
                    if (first.contains(LLChecker.EPSILON)) {
                        wasEpsilonInFirst = true;
                        if (listForGettingFirst.size() != 0) {
                            if (listForGettingFirst.get(0).startsWith("~") && listForGettingFirst.size() != 1) {
                                throw new IllegalArgumentException("It can be only one action after the EPSILON rule, but got: " + listForGettingFirst.size());
                            }
                        }
                        if (listForGettingFirst.size() == 1) {
                            epsilonAction = listForGettingFirst.get(0);
                        }
                        first.remove(LLChecker.EPSILON);
                    }
                    boolean needWriteTypes = true;
                    for (String tokenValue : first) {
                        writer.write("            case " + stringsToTokenNames.get(tokenValue) + ":\n");
                        Map<String, Integer> currentUntermNameNumber = new HashMap<>(); // Чтобы результат выполнения функции приписывать правильному ReturnsArguments
                        for (Map.Entry<String, List<String>> untermNames : rightPartUntermNames.entrySet()) {
                            String type = untermNames.getKey().substring(1).substring(0, 1).toUpperCase() + untermNames.getKey().substring(1).substring(1);
                            for (String name : untermNames.getValue()) {
                                if (needWriteTypes) {
                                    writer.write("                " + type + "ReturnsArguments " + name + ";\n");
                                }
                            }
                            currentUntermNameNumber.put(untermNames.getKey(), 0);
                        }
                        boolean firstTerm = true;
                        int skipTerms = 0;
                        int k = 0;
                        boolean nextTokenAfterActions = false;
                        for (String s : rightPartList) {
                            if (s.startsWith("!")) {
                                if (nextTokenAfterActions) {
                                    writer.write("\n                    lex.nextToken();\n                }\n");
                                    nextTokenAfterActions = false;
                                }
                                firstTerm = false;
                                String name = s.substring(1);
                                String type = name.substring(0, 1).toUpperCase() + name.substring(1) + "ReturnsArguments";
                                if (s.endsWith(")")) {
                                    name = name.substring(0, name.indexOf("("));
                                    type = name.substring(0, 1).toUpperCase() + name.substring(1) + "ReturnsArguments";
                                    boolean isName;
                                    String variableName = "";
                                    String nameWithoutArguments = s.substring(0, s.indexOf("("));
                                    if (currentUntermNameNumber.containsKey(nameWithoutArguments)) {
                                        int index = currentUntermNameNumber.get(nameWithoutArguments);
                                        variableName = rightPartUntermNames.get(nameWithoutArguments).get(index);
                                        currentUntermNameNumber.put(nameWithoutArguments, index + 1);
                                        if (needWriteTypes) {
                                            writer.write("                Pair<Tree, " + type + "> " + variableName + "TreeAndResult = ");
                                        } else {
                                            writer.write("                " + variableName + "TreeAndResult = ");
                                        }
                                        writer.write(name + "(new " + name.substring(0, 1).toUpperCase() + name.substring(1) + "ParametersArguments(");
                                        isName = true;
                                    } else {
                                        writer.write("                answerTree.addChildren(" + name + "(new " + name.substring(0, 1).toUpperCase() + name.substring(1));
                                        writer.write("ParametersArguments(");
                                        isName = false;
                                    }
                                    String argumentsString = s.substring(s.indexOf("(") + 1, s.indexOf(")"));
                                    StringBuilder stringWithoutWhitespaces = new StringBuilder();
                                    for (int i = 0; i < argumentsString.length(); i++) {
                                        if (!Character.isWhitespace(argumentsString.charAt(i))) {
                                            stringWithoutWhitespaces.append(argumentsString.charAt(i));
                                        }
                                    }
                                    String[] arguments = stringWithoutWhitespaces.toString().split(",");
                                    int i = 0;
                                    for (String argument : arguments) {
                                        if (argument.startsWith("$")) {
                                            Pair<String, Integer> currentVariableAndPos = getCurrentVariable(argument, 1, true);
                                            String currentVariable = currentVariableAndPos.getKey();
                                            if (currentVariable.contains(".")) {
                                                String[] classAndName = currentVariable.split("\\.");
                                                if (classAndName.length != 2) {
                                                    throw new IllegalArgumentException("If \".\" contains in variable, it must has only class and name");
                                                }
                                                String clazz = classAndName[0];
                                                String nameInClass = classAndName[1];
                                                writer.write(clazz + ".get" + nameInClass.substring(0, 1).toUpperCase() + nameInClass.substring(1) + "()");
                                            } else {
                                                Set<String> parametersNames = checker.getParametersNamesForUnterm().get("!" + untermName);
                                                Set<String> localsNames = checker.getLocalsNamesForUnterm().get("!" + untermName);
                                                Set<String> retursNames = checker.getReturnsNamesForUnterm().get("!" + untermName);
                                                if (parametersNames != null && parametersNames.contains(currentVariable)) {
                                                    writer.write("params.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                                                } else if (retursNames != null && retursNames.contains(currentVariable)) {
                                                    writer.write("returns.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                                                } else if (localsNames != null && localsNames.contains(currentVariable)) {
                                                    writer.write("locals.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                                                } else {
                                                    throw new IllegalArgumentException("Unknown variable name " + currentVariable + " in arguments block for unterm " + untermName);
                                                }
                                            }
                                        } else {
                                            writer.write(argument);
                                        }
                                        if (i == arguments.length - 1) {
                                            if (isName) {
                                                writer.write("));\n");
                                                writer.write("                answerTree.addChildren(" + variableName + "TreeAndResult.getKey());\n");
                                                writer.write("                " + variableName + " = " + variableName + "TreeAndResult.getValue();\n");
                                            } else {
                                                writer.write(")).getKey());\n");
                                            }
                                        } else {
                                            writer.write(", ");
                                        }
                                        i++;
                                    }
                                } else {
                                    if (currentUntermNameNumber.containsKey(s)) {
                                        int index = currentUntermNameNumber.get(s);
                                        String variableName = rightPartUntermNames.get(s).get(index);
                                        currentUntermNameNumber.put(s, index + 1);
                                        if (needWriteTypes) {
                                            writer.write("                Pair<Tree, " + type + "> " + variableName + "TreeAndResult = ");
                                        } else {
                                            writer.write("                " + variableName + "TreeAndResult = ");
                                        }
                                        writer.write(name + "(new " + name.substring(0, 1).toUpperCase() + name.substring(1) + "ParametersArguments());\n");
                                        writer.write("                answerTree.addChildren(" + variableName + "TreeAndResult.getKey());\n");
                                        writer.write("                " + variableName + " = " + variableName + "TreeAndResult.getValue();\n");
                                    } else {
                                        writer.write("                answerTree.addChildren(" + name + "(new " + name.substring(0, 1).toUpperCase() + name.substring(1));
                                        writer.write("ParametersArguments()).getKey());\n");
                                    }
                                }
                            } else if (s.startsWith("~")) {
                                writeBeforeSymbol(writer, s.substring(1), "!" + untermName, '~', false, needWriteTypes);
                            } else {
                                if (nextTokenAfterActions) {
                                    writer.write("\n                    lex.nextToken();\n                }\n");
                                    nextTokenAfterActions = false;
                                }
                                if (skipTerms > 0) {
                                    skipTerms--;
                                    k++;
                                    continue;
                                }
                                boolean regexpNow = false;
                                if (s.startsWith("*")) {
                                    s = checker.getGivenRegexpsMap().get(s);
                                    regexpNow = true;
                                }
                                String firstS = s;
                                if (firstTerm) {
                                    int t = k + 1;
                                    while (t < rightPartList.size() && !rightPartList.get(t).startsWith("!") && !rightPartList.get(t).startsWith("*")) {
                                        String tmp = rightPartList.get(t);
                                        if (tmp.startsWith("~")) {
                                            t++;
                                            continue;
                                        }
                                        if (regexpNow) {
                                            for (int j = 0; j < tmp.length(); j++) {
                                                firstS += "[" + tmp.charAt(j) + "]";
                                            }
                                        } else {
                                            firstS += tmp;
                                        }
                                        t++;
                                        skipTerms++;
                                    }
                                    firstTerm = false;
                                }
                                writer.write("                if (lex.curToken() != Token." + stringsToTokenNames.get(firstS) + ") {\n");
                                writer.write("                    throw new ParseException(\"Unexpected token on position \", lex.curPos());\n");
                                //writer.write("                } else {\n                    lex.nextToken();\n                    answerTree.addChildren(new Tree(\"" + firstS + "\"));\n");
                                if (regexpNow) {
                                    writer.write("                } else {\n                    answerTree.addChildren(new Tree(lex.getLastMatchedRegexText()));\n");
                                } else {
                                    writer.write("                } else {\n                    answerTree.addChildren(new Tree(\"" + firstS + "\"));\n");
                                }
                                nextTokenAfterActions = true;
                                //writer.write("                }\n");
                            }
                            k++;
                        }
                        if (nextTokenAfterActions) {
                            writer.write("\n                    lex.nextToken();\n                }\n");
                            nextTokenAfterActions = false;
                        }
                        writer.write("\n                return new Pair<>(answerTree, returns);\n");
                        needWriteTypes = false;
                    }
                }
                if (wasEpsilonInFirst) {
                    Set<String> follow = checker.getFollow().get("!" + untermName);
                    for (String tokenValue : follow) {
                        writer.write("            case " + stringsToTokenNames.get(tokenValue) + ":\n");
                        if (!epsilonAction.equals("")) {
                            writeBeforeSymbol(writer, epsilonAction.substring(1), "!" + untermName, '~', false, true);
                        }
                        writer.write("                return new Pair<>(new Tree(\"" + untermName + "\"), returns);\n");
                    }
                }
                writer.write("            default:\n                throw new ParseException(\"Unexpected symbol \" + lex.curChar() + \" in position \" + (lex.curPos() - 1), lex.curPos());\n");
                writer.write("        }\n    }\n\n");
            }
            writer.write("    public Tree parse(InputStream is) throws ParseException {\n        ");
            writer.write("lex = new Lexer(is);\n        lex.nextToken();\n        ");
            String startState = checker.getStart();
            startState = startState.substring(1);
            writer.write("return " + startState + "(new " + startState.substring(0, 1).toUpperCase() + startState.substring(1) + "ParametersArguments()).getKey();\n    }\n");
            writer.write("}");
        } catch (IOException e) {
            System.err.println("Something comes wrong with creating parser file, message: " + e.getMessage());
        }
    }

    private int writeBeforeSymbol(Writer writer, String source, String untermName, char stopSymbol, boolean writeStopSymbol, boolean needWriteTypes) throws IOException {
        Set<String> parametersNames = checker.getParametersNamesForUnterm().get(untermName);
        Set<String> localsNames = checker.getLocalsNamesForUnterm().get(untermName);
        Set<String> retursNames = checker.getReturnsNamesForUnterm().get(untermName);
        for (int i = 0; i < source.length(); ) {
            if (i + 7 < source.length() && source.substring(i, i + 6).equals("String")) {
                if (needWriteTypes) {
                    writer.write("String");
                }
                i += 6;
            } else if (i + 13 < source.length() && source.substring(i, i + 12).equals("List<String>")) {
                if (needWriteTypes) {
                    writer.write("List<String>");
                }
                i += 12;
            } else if (i + 12 < source.length() && source.substring(i, i + 11).equals("Set<String>")) {
                if (needWriteTypes) {
                    writer.write("Set<String>");
                }
                i += 11;
            } if (i + 1 < source.length() && source.charAt(i) == '$' && source.charAt(i + 1) == '*') {
                i += 2;
                String value = "";
                while (i < source.length() && ((source.charAt(i) >= 'A' && source.charAt(i) <= 'Z') || (source.charAt(i) >= 'a' && source.charAt(i) <= 'z') || source.charAt(i) == '.')) {
                    value += source.charAt(i);
                    i++;
                }
                String[] valueParts = value.split("\\.");
                if (valueParts.length != 2 || !valueParts[1].equals("text")) {
                    throw new IllegalArgumentException("Expected with regexps: $*NAME.text");
                }
                writer.write("lex.getLastMatchedRegexText()");
            } else if (source.charAt(i) == '$') {
                i++;
                Pair<String, Integer> currentVarAndPos = getCurrentVariable(source, i, true);
                i = currentVarAndPos.getValue();
                String currentVariable = currentVarAndPos.getKey();
                if (i < source.length() && source.charAt(i) == '=') {
                    i++;
                    while (i < source.length() && Character.isWhitespace(source.charAt(i))) {
                        i++;
                    }
                    if (currentVariable.contains(".")) {
                        String[] classAndName = currentVariable.split("\\.");
                        if (classAndName.length != 2) {
                            throw new IllegalArgumentException("If \".\" contains in variable, it must has only class and name");
                        }
                        String clazz = classAndName[0];
                        String nameInClass = classAndName[1];
                        writer.write(clazz + ".set" + nameInClass.substring(0, 1).toUpperCase() + nameInClass.substring(1) + "(");
                    } else {
                        if (parametersNames != null && parametersNames.contains(currentVariable)) {
                            writer.write("params.set" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "(");
                        } else if (retursNames != null && retursNames.contains(currentVariable)) {
                            writer.write("returns.set" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "(");
                        } else if (localsNames != null && localsNames.contains(currentVariable)) {
                            writer.write("locals.set" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "(");
                        } else {
                            throw new IllegalArgumentException("Unknown variable name " + currentVariable + " in action block for unterm " + untermName);
                        }
                    }
                    boolean inQuotes = false;
                    int balance = 0;
                    while (i < source.length() && ((source.charAt(i) != ';' && source.charAt(i) != ')') || (source.charAt(i) == ')' && balance != 0) || inQuotes)) {
                        if (source.charAt(i) == '$') {
                            i++;
                            if (i < source.length() && source.charAt(i) == '*') {
                                i++;
                                String value = "";
                                while (i < source.length() && ((source.charAt(i) >= 'A' && source.charAt(i) <= 'Z') || (source.charAt(i) >= 'a' && source.charAt(i) <= 'z') || source.charAt(i) == '.')) {
                                    value += source.charAt(i);
                                    i++;
                                }
                                String[] valueParts = value.split("\\.");
                                if (valueParts.length != 2 || !valueParts[1].equals("text")) {
                                    throw new IllegalArgumentException("Expected with regexps: $*NAME.text");
                                }
                                writer.write("lex.getLastMatchedRegexText()");
                            } else {
                                Pair<String, Integer> valueAndPos = getCurrentVariable(source, i, true);
                                String value = valueAndPos.getKey();
                                i = valueAndPos.getValue();
                                if (value.contains(".")) {
                                    String[] classAndNameOfValue = value.split("\\.");
                                    if (classAndNameOfValue.length != 2) {
                                        throw new IllegalArgumentException("If \".\" contains in variable, it must has only class and name");
                                    }
                                    String clazzOfValue = classAndNameOfValue[0];
                                    String nameInClassOfValue = classAndNameOfValue[1];
                                    writer.write(clazzOfValue + ".get" + nameInClassOfValue.substring(0, 1).toUpperCase() + nameInClassOfValue.substring(1) + "()");
                                } else {
                                    if (parametersNames != null && parametersNames.contains(value)) {
                                        writer.write("params.get" + value.substring(0, 1).toUpperCase() + value.substring(1) + "()");
                                    } else if (retursNames != null && retursNames.contains(value)) {
                                        writer.write("returns.get" + value.substring(0, 1).toUpperCase() + value.substring(1) + "()");
                                    } else if (localsNames != null && localsNames.contains(value)) {
                                        writer.write("locals.get" + value.substring(0, 1).toUpperCase() + value.substring(1) + "()");
                                    } else {
                                        throw new IllegalArgumentException("Unknown variable name " + value + " in action block for unterm " + untermName);
                                    }
                                }
                            }
                        } else {
                            if (source.charAt(i) == '\"') {
                                inQuotes = !inQuotes;
                            }
                            if (source.charAt(i) == '(' && !inQuotes) {
                                balance++;
                            }
                            if (source.charAt(i) == ')' && !inQuotes) {
                                balance--;
                            }
                            writer.write(source.charAt(i));
                            i++;
                        }
                    }
                    if (source.charAt(i) == ';') {
                        writer.write(");\n");
                    } else if (source.charAt(i) == ')') {
                        writer.write("))");
                    }
                } else {
                    if (currentVariable.contains(".")) {
                        String[] classAndName = currentVariable.split("\\.");
                        if (classAndName.length != 2) {
                            throw new IllegalArgumentException("If \".\" contains in variable, it must has only class and name");
                        }
                        String clazz = classAndName[0];
                        String nameInClass = classAndName[1];
                        writer.write(clazz + ".get" + nameInClass.substring(0, 1).toUpperCase() + nameInClass.substring(1) + "()");
                    } else {
                        if (parametersNames != null && parametersNames.contains(currentVariable)) {
                            writer.write("params.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                        } else if (retursNames != null && retursNames.contains(currentVariable)) {
                            writer.write("returns.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                        } else if (localsNames != null && localsNames.contains(currentVariable)) {
                            writer.write("locals.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                        } else {
                            throw new IllegalArgumentException("Unknown variable name " + currentVariable + " in action block for unterm " + untermName);
                        }
                    }
                }
            } else if (source.charAt(i) == stopSymbol) {
                if (writeStopSymbol) {
                    writer.write(stopSymbol + "\n");
                }
                return (i + 1);
            } else {
                writer.write(source.charAt(i));
                i++;
            }
        }
        return source.length();
    }

    private Pair<String, Integer> getCurrentVariable(String block, int i, boolean pointAndDigitsIsInName) {
        String currentVariable = "";
        while (i < block.length() && ((block.charAt(i) >= 'a' && block.charAt(i) <= 'z') || (block.charAt(i) >= 'A' && block.charAt(i) <= 'Z') || (pointAndDigitsIsInName && (block.charAt(i) == '.') || (block.charAt(i) >= '0' && block.charAt(i) <= '9')))) {
            currentVariable += block.charAt(i);
            i++;
        }
        while (i < block.length() && Character.isWhitespace(block.charAt(i))) {
            i++;
        }
        return new Pair<>(currentVariable, i);
    }

    private void generateInitBlock(Writer writer, String initBlock, String untermName) throws IOException {
        Set<String> parametersNames = checker.getParametersNamesForUnterm().get(untermName);
        Set<String> localsNames = checker.getLocalsNamesForUnterm().get(untermName);
        Set<String> retursNames = checker.getReturnsNamesForUnterm().get(untermName);
        for (int i = 0; i < initBlock.length(); i++) {
            if (initBlock.charAt(i) == '$') {
                i++;
                Pair<String, Integer> curVarAndPos = getCurrentVariable(initBlock, i, false);
                String currentVariable = curVarAndPos.getKey();
                i = curVarAndPos.getValue();
                if (i < initBlock.length() && initBlock.charAt(i) == '=') {
                    i++; // skip '='
                    while (i < initBlock.length() && Character.isWhitespace(initBlock.charAt(i))) {
                        i++;
                    }
                    String value = "";
                    while (i < initBlock.length() && initBlock.charAt(i) != ';') {
                        if (initBlock.charAt(i) == '$') {
                            i++;
                            curVarAndPos = getCurrentVariable(initBlock, i, false);
                            if (parametersNames != null && parametersNames.contains(curVarAndPos.getKey())) {
                                value += "params.get" + curVarAndPos.getKey().substring(0, 1).toUpperCase() + curVarAndPos.getKey().substring(1) + "()";
                            } else if (retursNames != null && retursNames.contains(curVarAndPos.getKey())) {
                                value += "returns.get" +curVarAndPos.getKey().substring(0, 1).toUpperCase() + curVarAndPos.getKey().substring(1) + "()";
                            } else if (localsNames != null && localsNames.contains(curVarAndPos.getKey())) {
                                value += "locals.get" + curVarAndPos.getKey().substring(0, 1).toUpperCase() + curVarAndPos.getKey().substring(1) + "()";
                            } else {
                                throw new IllegalArgumentException("Unknown variable name " + currentVariable + " in init block for unterm " + untermName);
                            }
                            i = curVarAndPos.getValue();
                            continue;
                        }
                        value += initBlock.charAt(i);
                        i++;
                    }
                    i++;
                    if (parametersNames != null && parametersNames.contains(currentVariable)) {
                        writer.write("params.set" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "(" + value + ");\n");
                    } else if (retursNames != null && retursNames.contains(currentVariable)) {
                        writer.write("returns.set" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "(" + value + ");\n");
                    } else if (localsNames != null && localsNames.contains(currentVariable)) {
                        writer.write("locals.set" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "(" + value + ");\n");
                    } else {
                        throw new IllegalArgumentException("Unknown variable name " + currentVariable + " in init block for unterm " + untermName);
                    }
                } else {
                    if (parametersNames != null && parametersNames.contains(currentVariable)) {
                        writer.write("params.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                    } else if (retursNames != null && retursNames.contains(currentVariable)) {
                        writer.write("returns.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                    } else if (localsNames != null && localsNames.contains(currentVariable)) {
                        writer.write("locals.get" + currentVariable.substring(0, 1).toUpperCase() + currentVariable.substring(1) + "()");
                    } else {
                        throw new IllegalArgumentException("Unknown variable name " + currentVariable + " in init block for unterm " + untermName);
                    }
                    i--;
                }
            } else {
                writer.write(initBlock.charAt(i));
            }
        }
        writer.write("\n");
    }
}
