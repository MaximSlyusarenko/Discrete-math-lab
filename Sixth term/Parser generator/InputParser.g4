grammar InputParser;

@parser::header {
    import java.util.Map;
    import java.util.HashMap;
}

@parser::members {
    String currentRuleName;
    List<String> currentRule;
    List<String> currentRuleWithActions;
    Map<String, List<String>> currentRuleUntermNames;
    LLChecker checker = null;
    List<String> currentParameterTypes;
    List<String> currentParameterNames;
    boolean madeDirectory = false;
    int currentBlock;
}

s
    : 'grammar' NAME ';' parseRule {
        if (!checker.isLL()) {
            System.out.println("You grammar isn't LL(1)");
        } else {
            System.out.println("Grammar is LL");
            TokensEnumWriter enumGenerator = new TokensEnumWriter(checker.getTokens());
            enumGenerator.generateEnum();
            LexerWriter lexerWriter = new LexerWriter(checker);
            lexerWriter.generateLexer();
            ParserWriter parserWriter = new ParserWriter(checker);
            parserWriter.generateParser();
        }
    }
    ;

parseRule
    :
    | lexerRule
    | PARSER_RULE_NAME {
        currentRuleName = $PARSER_RULE_NAME.text;
        if (checker == null) {
            checker = new LLChecker($PARSER_RULE_NAME.text);
        }
        currentParameterTypes = new ArrayList<>();
        currentParameterNames = new ArrayList<>();
        currentBlock = 0;
    } parametersBlock {
        ClassWithFieldsWriter generator = new ClassWithFieldsWriter(currentParameterTypes, currentParameterNames, $PARSER_RULE_NAME.text, "parameters");
        if (!madeDirectory) {
            generator.makeDirectory();
            madeDirectory = true;
        }
        generator.generateClass();
        currentParameterTypes = new ArrayList<>();
        currentParameterNames = new ArrayList<>();
        currentBlock = 1;
    } returnsBlock {
        generator = new ClassWithFieldsWriter(currentParameterTypes, currentParameterNames, $PARSER_RULE_NAME.text, "returns");
        generator.generateClass();
        currentParameterTypes = new ArrayList<>();
        currentParameterNames = new ArrayList<>();
        currentBlock = 2;
    } localsBlock {
        generator = new ClassWithFieldsWriter(currentParameterTypes, currentParameterNames, $PARSER_RULE_NAME.text, "locals");
        generator.generateClass();
        currentParameterTypes = new ArrayList<>();
        currentParameterNames = new ArrayList<>();
        currentBlock = -1;
    } initBlock1 = initBlock {
        checker.addInitBlock($PARSER_RULE_NAME.text, $initBlock1.program);
    } rules ';' parseRule
    ;

ruleArguments
    : type1 = type NAME {
        currentParameterTypes.add($type1.resultType);
        currentParameterNames.add($NAME.text);
        if (currentBlock == 0) {
            checker.addParameterName(currentRuleName, $NAME.text);
        } else if (currentBlock == 1) {
            checker.addReturnName(currentRuleName, $NAME.text);
        } else if (currentBlock == 2) {
            checker.addLocalName(currentRuleName, $NAME.text);
        }
    } ',' ruleArguments
    | type1 = type NAME {
        currentParameterTypes.add($type1.resultType);
        currentParameterNames.add($NAME.text);
        if (currentBlock == 0) {
            checker.addParameterName(currentRuleName, $NAME.text);
        } else if (currentBlock == 1) {
            checker.addReturnName(currentRuleName, $NAME.text);
        } else if (currentBlock == 2) {
            checker.addLocalName(currentRuleName, $NAME.text);
        }
    } ')'
    ;

type returns [String resultType] // types which were in third lab
    : 'Set' '<' type1 = type '>' { $resultType = "Set<" + ($type1.resultType.equals("int") ? "Integer" : ($type1.resultType.equals("boolean") ? "Boolean" : $type1.resultType)) + ">"; }
    | 'int' { $resultType = "int"; }
    | 'String' { $resultType = "String"; }
    | 'List' '<' type1 = type '>' { $resultType = "List<" + ($type1.resultType.equals("int") ? "Integer" : ($type1.resultType.equals("boolean") ? "Boolean" : $type1.resultType))  + ">"; }
    | 'boolean' { $resultType = "boolean"; }
    ;

parametersBlock
    :
    | '(' ruleArguments
    ;

returnsBlock
    :
    | 'returns' '(' ruleArguments
    ;

localsBlock
    :
    | 'locals' '(' ruleArguments
    ;

initBlock returns [String program]
    :
    | '@init' PROGRAM_EXPR { $program = $PROGRAM_EXPR.text.substring(1, $PROGRAM_EXPR.text.length() - 1); }
    ;

rules
    :
    | ':' { currentRule = new ArrayList<>(); currentRuleWithActions = new ArrayList<>(); currentRuleUntermNames = new HashMap<>(); } rulePart { checker.addRule(currentRuleName, currentRule); checker.addRuleWithActions(currentRuleName, currentRuleWithActions, currentRuleUntermNames); } rules
    | '|' { currentRule = new ArrayList<>(); currentRuleWithActions = new ArrayList<>(); currentRuleUntermNames = new HashMap<>(); } rulePart { checker.addRule(currentRuleName, currentRule); checker.addRuleWithActions(currentRuleName, currentRuleWithActions, currentRuleUntermNames); } rules
    ;

rulePart
    :
    | PROGRAM_EXPR { currentRuleWithActions.add($PROGRAM_EXPR.text); } rulePart
    | EXPR_IN_QUOTES { currentRule.add($EXPR_IN_QUOTES.text.substring(1, $EXPR_IN_QUOTES.text.length() - 1)); currentRuleWithActions.add($EXPR_IN_QUOTES.text.substring(1, $EXPR_IN_QUOTES.text.length() - 1)); } rulePart
    | LEXER_RULE_NAME { currentRule.add($LEXER_RULE_NAME.text); currentRuleWithActions.add($LEXER_RULE_NAME.text); } rulePart
    | PARSER_RULE_NAME { currentRule.add($PARSER_RULE_NAME.text); currentRuleWithActions.add($PARSER_RULE_NAME.text); } rulePart
    | NAME '=' PARSER_RULE_NAME {
        currentRule.add($PARSER_RULE_NAME.text);
        currentRuleWithActions.add($PARSER_RULE_NAME.text);
        if (!currentRuleUntermNames.containsKey($PARSER_RULE_NAME.text)) {
            currentRuleUntermNames.put($PARSER_RULE_NAME.text, new ArrayList<>());
        }
        currentRuleUntermNames.get($PARSER_RULE_NAME.text).add($NAME.text);
    } rulePart
    | NAME '=' PARSER_RULE_NAME {
        currentRule.add($PARSER_RULE_NAME.text);
        //currentRuleWithActions.add($PARSER_RULE_NAME.text);
        if (!currentRuleUntermNames.containsKey($PARSER_RULE_NAME.text)) {
            currentRuleUntermNames.put($PARSER_RULE_NAME.text, new ArrayList<>());
        }
        currentRuleUntermNames.get($PARSER_RULE_NAME.text).add($NAME.text);
    } '(' callingRuleArguments1 = callingRuleArguments { currentRuleWithActions.add($PARSER_RULE_NAME.text + "(" + $callingRuleArguments1.result + ")"); } ')' rulePart
    ;

callingRuleArguments returns [String result]
    @init {
        $result = "";
    }
    : '$' NAME ',' callingRuleArguments1 = callingRuleArguments { $result = "$" + $NAME.text + "," + $callingRuleArguments1.result; }
    | '$' Name1 = NAME '.' Name2 = NAME ',' callingRuleArguments1 = callingRuleArguments { $result = "$" + $Name1.text + "." + $Name2.text + "," + $callingRuleArguments1.result; }
    | '$' NAME '+' NUMBER ',' callingRuleArguments1 = callingRuleArguments { $result = "$" + $NAME.text + "+" + $NUMBER.text + "," + $callingRuleArguments1.result; }
    | '$' NAME '+' NUMBER { $result = "$" + $NAME.text + "+" + $NUMBER.text; }
    | '$' Name1 = NAME '.' Name2 = NAME { $result = "$" + $Name1.text + "." + $Name2.text; }
    | '$' NAME { $result = "$" + $NAME.text; }
    ;

lexerRule
    :
    | LEXER_RULE_NAME ':' EXPR_IN_SQUARE_BRACKETS ';' { checker.addLexerRule($LEXER_RULE_NAME.text, $EXPR_IN_SQUARE_BRACKETS.text); } lexerRule
    | LEXER_RULE_NAME ':' EXPR_IN_SQUARE_BRACKETS '+' { checker.addLexerRule($LEXER_RULE_NAME.text, $EXPR_IN_SQUARE_BRACKETS.text + "+"); }';' lexerRule
    | LEXER_RULE_NAME ':' EXPR_IN_SQUARE_BRACKETS '*' { checker.addLexerRule($LEXER_RULE_NAME.text, $EXPR_IN_SQUARE_BRACKETS.text + "*"); }';' lexerRule
    | LEXER_RULE_NAME ':' EXPR_IN_SQUARE_BRACKETS '+?' { checker.addLexerRule($LEXER_RULE_NAME.text, $EXPR_IN_SQUARE_BRACKETS.text + "+?"); } ';' lexerRule
    | LEXER_RULE_NAME ':' EXPR_IN_SQUARE_BRACKETS '*?' { checker.addLexerRule($LEXER_RULE_NAME.text, $EXPR_IN_SQUARE_BRACKETS.text + "*?"); } ';' lexerRule
    | LEXER_RULE_NAME ':' EXPR_IN_SQUARE_BRACKETS '->' 'skip' { checker.addSkipRule($EXPR_IN_SQUARE_BRACKETS.text); } ';' lexerRule
    ;

NAME : ([a-zA-Z])([a-zA-Z0-9])* ;
PARSER_RULE_NAME : '!'([a-z])([a-zA-Z0-9])* ;
LEXER_RULE_NAME : '*'([A-Z])([a-zA-Z0-9])* ;
NUMBER : ([1-9])([0-9])* ;
EXPR_IN_QUOTES : '\'' (~('\''))+ '\'';
EXPR_IN_SQUARE_BRACKETS : '[' (~('['))+ ']' ;
PROGRAM_EXPR : '~' (~('~'))+ '~';
WS : [ \t \r \n]+ -> skip ;