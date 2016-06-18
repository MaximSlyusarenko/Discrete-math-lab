grammar Variant7;

@parser::header {
    import java.util.Set;
    import java.util.HashSet;
    import java.io.*;
}

s locals[Set<String> declaredVariables, int tabs]
    @init {
        $declaredVariables = new HashSet<>();
        $tabs = 1;
    }
    : exprProgram1 = exprProgram[$declaredVariables, $tabs] {
        try (OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream("program.c"), "UTF-8")) {
            writer.write("#include <stdio.h>\n\nusing namespace std;\n\nint main() {\n" + $exprProgram1.program + "    return 0;\n}");
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
    ;

exprProgram[Set<String> declaredVariables, int tabs] returns [String program]
    @init {
        $program = "";
    }
    :
    | exprRead1 = exprRead[$declaredVariables, $tabs] { $program += $exprRead1.program; } exprProgram1 = exprProgram[$declaredVariables, $tabs] { $program += $exprProgram1.program; }
    | exprIf1 = exprIf[$tabs] exprProgram1 = exprProgram[$declaredVariables, $tabs] { $program += $exprIf1.program + $exprProgram1.program; }
    | exprWhile1 = exprWhile[$tabs] exprProgram1 = exprProgram[$declaredVariables, $tabs] { $program += $exprWhile1.program + $exprProgram1.program; }
    | exprFor1 = exprFor[$tabs] exprProgram1 = exprProgram[$declaredVariables, $tabs] { $program += $exprFor1.program + $exprProgram1.program; }
    | exprPrint1 = exprPrint[$tabs] exprProgram1 = exprProgram[$declaredVariables, $tabs] { $program += $exprPrint1.program + $exprProgram1.program; }
    | operationExpr1 = operationExpr ';' exprProgram1 = exprProgram[$declaredVariables, $tabs] {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += $operationExpr1.program + ";\n" + $exprProgram1.program; }
    ;

exprFor[int tabs] returns [String program] locals [Set<String> declaredVariables]
    @init {
        $declaredVariables = new HashSet<>();
        $program = "";
    }
    : 'for' '(' exprRead1 = exprRead[$declaredVariables, $tabs + 1] conditionPart1 = conditionPart ';' exprProgram1 = exprProgram[$declaredVariables, $tabs + 2] ')' '{' exprProgram2 = exprProgram[$declaredVariables, $tabs + 1] '}' {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "bool first = true;\n";
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "while (true) {\n";
        $program += $exprRead1.program;
        for (int i = 0; i < $tabs + 1; i++) {
            $program += "    ";
        }
        $program += "if (first) {\n";
        for (int i = 0; i < $tabs + 2; i++) {
            $program += "    ";
        }
        $program += "first = false;\n";
        for (int i = 0; i < $tabs + 1; i++) {
            $program += "    ";
        }
        $program += "} else {\n";
        $program += $exprProgram1.program;
        for (int i = 0; i < $tabs + 1; i++) {
            $program += "    ";
        }
        $program += "}\n";
        $program += $exprProgram2.program;
        for (int i = 0; i < $tabs + 1; i++) {
            $program += "    ";
        }
        $program += "if (";
        $program += $conditionPart1.program;
        $program += ") {\n";
        for (int i = 0; i < $tabs + 2; i++) {
            $program += "    ";
        }
        $program += "break;\n";
        for (int i = 0; i < $tabs + 1; i++) {
            $program += "    ";
        }
        $program += "}\n";
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "}\n";
    }
    ;

exprIf[int tabs] returns [String program] locals [Set<String> declaredVariables]
    @init {
        $declaredVariables = new HashSet<>();
        $program = "";
    }
    : 'if' '(' conditionPart1 = conditionPart ')' '{' exprProgram1 = exprProgram[$declaredVariables, $tabs + 1] '}' exprElse1 = exprElse[$tabs] {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "if (" + $conditionPart1.program + ") {\n" + $exprProgram1.program;
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "}\n";
        $program += $exprElse1.program;
    }
    ;

exprElse[int tabs] returns [String program] locals [Set<String> declaredVariables]
    @init {
            $declaredVariables = new HashSet<>();
            $program = "";
        }
        :
        | 'else' exprIf1 = exprIf[$tabs] { $program = "else\n" + $exprIf1.program; }
        | 'else' '{' exprProgram1 = exprProgram[$declaredVariables, $tabs + 1] '}' {
            $program = "else {\n" + $exprProgram1.program;
            for (int i = 0; i < $tabs; i++) {
                $program += "    ";
            }
            $program += "}";
        }
        ;

exprWhile[int tabs] returns [String program] locals [Set<String> declaredVariables]
    @init {
        $declaredVariables = new HashSet<>();
        $program = "";
    }
    : 'while' '(' conditionPart1 = conditionPart ')' '{' exprProgram1 = exprProgram[$declaredVariables, $tabs + 1] '}' {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "while (" + $conditionPart1.program + ") {\n" + $exprProgram1.program;
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "}\n";
    }
    ;

conditionPart returns [String program]
    : exprCompare1 = exprCompare { $program = $exprCompare1.program; }
    | '(' conditionPart1 = conditionPart ')' { $program = "(" + $conditionPart1.program + ")"; }
    | conditionPart1 = conditionPart '||' conditionPart2 = conditionPart { $program = $conditionPart1.program + " || " + $conditionPart2.program; }
    | conditionPart1 = conditionPart '&&' conditionPart2 = conditionPart { $program = $conditionPart1.program + " && " + $conditionPart2.program; }
    | conditionPart1 = conditionPart '^' conditionPart2 = conditionPart { $program = $conditionPart1.program + " ^ " + $conditionPart2.program; }
    | '!' conditionPart1 = conditionPart { $program = "! " + $conditionPart1.program; }
    ;

operationExpr returns [String program]
    : ID { $program = $ID.text; }
    | VAL { $program = $VAL.text; }
    | ID '++' { $program = $ID.text + "++"; }
    | ID '--' { $program = $ID.text + "--"; }
    | '++' ID { $program = "++" + $ID.text; }
    | '--' ID { $program = "--" + $ID.text; }
    | operationExpr1 = operationExpr '+' operationExpr2 = operationExpr { $program = $operationExpr1.program + " + " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '*' operationExpr2 = operationExpr { $program = $operationExpr1.program + " * " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '/' operationExpr2 = operationExpr { $program = $operationExpr1.program + " / " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '-' operationExpr2 = operationExpr { $program = $operationExpr1.program + " - " + $operationExpr2.program; }
    | '-' operationExpr1 = operationExpr { $program = "-" + $operationExpr1.program; }
    | '(' operationExpr1 = operationExpr ')' { $program = "(" + $operationExpr1.program + ")"; }
    ;

exprCompare returns [String program]
    : operationExpr1 = operationExpr '<' operationExpr2 = operationExpr { $program = $operationExpr1.program + " < " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '<=' operationExpr2 = operationExpr { $program = $operationExpr1.program + " <= " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '==' operationExpr2 = operationExpr { $program = $operationExpr1.program + " == " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '!=' operationExpr2 = operationExpr { $program = $operationExpr1.program + " != " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '>=' operationExpr2 = operationExpr { $program = $operationExpr1.program + " >= " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '>' operationExpr2 = operationExpr { $program = $operationExpr1.program + " > " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '<' operationExpr2 = operationExpr { $program = $operationExpr1.program + " < " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '<=' operationExpr2 = operationExpr { $program = $operationExpr1.program + " <= " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '==' operationExpr2 = operationExpr { $program = $operationExpr1.program + " == " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '!=' operationExpr2 = operationExpr { $program = $operationExpr1.program + " != " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '>=' operationExpr2 = operationExpr { $program = $operationExpr1.program + " >= " + $operationExpr2.program; }
    | operationExpr1 = operationExpr '>' operationExpr2 = operationExpr { $program = $operationExpr1.program + " > " + $operationExpr2.program; }
    | operationExpr1 = operationExpr { $program = $operationExpr1.program; }
    ;

exprPrint[int tabs] returns [String program]
    @init {
        $program = "";
    }
    : 'printInt' '(' operationExpr1 = operationExpr ')' ';' {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "printf(\"%d\", " + $operationExpr1.program + ");\n";
    }
    | 'printDouble' '(' operationExpr1 = operationExpr ')' ';' {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        $program += "printf(\"%f\", " + $operationExpr1.program + ");\n";
    }
    ;

exprRead[Set<String> declaredVariables, int tabs] returns [String program]
	: exprDeclaration1 = exprDeclaration[$declaredVariables, $tabs] {
	    $program = $exprDeclaration1.program;
	}
	;

exprDeclaration[Set<String> declaredVariables, int tabs] returns [String program]
    : exprType1 = exprType exprNamesEqualsValues1 = exprNamesEqualsValues[$exprType1.type, $declaredVariables, $tabs] ';' {
        $program = $exprNamesEqualsValues1.program;
    }
    ;

exprType returns [String type]
    : { $type = ""; } // eps
    | 'int' { $type = "int "; }
    | 'double' { $type = "real "; }
    ;

exprNamesEqualsValues[String type, Set<String> declaredVariables, int tabs] returns [String program, List<String> names, Set<String> changedNames]
    @init {
        $names = new ArrayList<>();
        $changedNames = new HashSet<>();
        $program = "";
    }
    : ID { $names.add($ID.text); } ',' exprON1 = exprON[$type, $names, $changedNames, $declaredVariables, $tabs] {
        $program += $exprON1.program;
    }
    | ID { $names.add($ID.text); } '=' exprValues1 = exprValues[$type, $names, $changedNames, $declaredVariables, $tabs] {
        for (String changedName: $exprValues1.declareTemp) {
            for (int i = 0; i < $tabs; i++) {
                $program += "    ";
            }
            if ($declaredVariables.contains(changedName + "1")) {
                $program += changedName + "1 = " + changedName + ";\n";
            } else {
                $declaredVariables.add(changedName + "1");
                $program += $type + changedName + "1 = " + changedName + ";\n";
            }
        }
        $program += $exprValues1.program;
    }
    ;

exprON[String type, List<String> names, Set<String> changedNames, Set<String> declaredVariables, int tabs] returns [String program] // other names
    @init {
        $program = "";
    }
    : ID {$names.add($ID.text); } ',' exprON1 = exprON[$type, $names, $changedNames, $declaredVariables, $tabs] {
        $program += $exprON1.program;
    }
    | ID {$names.add($ID.text); } '=' exprValues1 = exprValues[$type, $names, $changedNames, $declaredVariables, $tabs] {
        for (String changedName: $exprValues1.declareTemp) {
            for (int i = 0; i < $tabs; i++) {
                $program += "    ";
            }
            if ($declaredVariables.contains(changedName + "1")) {
                $program += changedName + "1 = " + changedName + ";\n";
            } else {
                $declaredVariables.add(changedName + "1");
                $program += $type + changedName + "1 = " + changedName + ";\n";
            }
        }
        $program += $exprValues1.program;
    }
    ;

exprValues[String type, List<String> names, Set<String> changedNames, Set<String> declaredVariables, int tabs] returns [String program, Set<String> declareTemp] locals [String name, boolean nameIsDeclared]
    @init {
        $name = $names.get(0);
        $names.remove(0);
        $program = "";
        $declareTemp = new HashSet<>();
    }
    : 'readInt()' ',' { $changedNames.add($name); if ($declaredVariables.contains($name)) { $nameIsDeclared = true;} else { $declaredVariables.add($name); $nameIsDeclared = false;} } exprValues1 = exprValues[$type, $names, $changedNames, $declaredVariables, $tabs] {
        $declareTemp.addAll($exprValues1.declareTemp);
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($nameIsDeclared) {
            $program += "scanf(\"%d\", &" + $name + ");\n";
        } else {
            $program += $type + $name + ";\n";
            for (int i = 0; i < $tabs; i++) {
                $program += "    ";
            }
            $program += "scanf(\"%d\", &" + $name + ");\n";
        }
        $program += $exprValues1.program;
    }
    | 'readDouble()' ',' { $changedNames.add($name); if ($declaredVariables.contains($name)) { $nameIsDeclared = true;} else { $declaredVariables.add($name); $nameIsDeclared = false;} } exprValues1 = exprValues[$type, $names, $changedNames, $declaredVariables, $tabs] {
        $declareTemp.addAll($exprValues1.declareTemp);
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($nameIsDeclared) {
            $program += "scanf(\"%f\", &" + $name + ");\n";
        } else {
            $program += $type + $name + ";\n";
            for (int i = 0; i < $tabs; i++) {
                $program += "    ";
            }
            $program += "scanf(\"%f\", &" + $name + ");\n";
        }
        $program += $exprValues1.program;
    }
    | VAL ',' { $changedNames.add($name); if ($declaredVariables.contains($name)) { $nameIsDeclared = true;} else { $declaredVariables.add($name); $nameIsDeclared = false;} } exprValues1 = exprValues[$type, $names, $changedNames, $declaredVariables, $tabs] {
        $declareTemp.addAll($exprValues1.declareTemp);
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($nameIsDeclared) {
            $program += $name + " = " + $VAL.text + ";\n";
        } else {
            $program += $type + $name + " = " + $VAL.text + ";\n";
        }
        $program += $exprValues1.program;
    }
    | ID ',' { $changedNames.add($name); if ($declaredVariables.contains($name)) { $nameIsDeclared = true;} else { $declaredVariables.add($name); $nameIsDeclared = false;} } exprValues1 = exprValues[$type, $names, $changedNames, $declaredVariables, $tabs] {
        $declareTemp.addAll($exprValues1.declareTemp);
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($changedNames.contains($ID.text)) {
            $declareTemp.add($ID.text);
            if ($nameIsDeclared) {
                $program += $name + " = " + $ID.text + "1;\n";
            } else {
                $program += $type + $name + " = " + $ID.text + "1;\n";
            }
        } else {
            if ($nameIsDeclared) {
                $program += $name + " = " + $ID.text + ";\n";
            } else {
                $program += $type + $name + " = " + $ID.text + ";\n";
            }
        }
        $program += $exprValues1.program;
    }
    | 'readInt()' {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($declaredVariables.contains($name)) {
            $program += $name + ";\nscanf(\"%d\", &" + $name + ");\n";
        } else {
            $declaredVariables.add($name);
            $program += $type + $name + ";\n";
            for (int i = 0; i < $tabs; i++) {
                $program += "    ";
            }
            $program += "scanf(\"%d\", &" + $name + ");\n";
        }
    }
    | 'readDouble()' {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($declaredVariables.contains($name)) {
            $program += $name + ";\nscanf(\"%f\", &" + $name + ");\n";
        } else {
            $declaredVariables.add($name);
            $program += $type + $name + ";\n";
            for (int i = 0; i < $tabs; i++) {
                $program += "    ";
            }
            $program += "scanf(\"%f\", &" + $name + ");\n";
        }
    }
    | VAL {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($declaredVariables.contains($name)) {
            $program += $name + " = " + $VAL.text + ";\n";
        } else {
            $declaredVariables.add($name);
            $program += $type + $name + " = " + $VAL.text + ";\n";
        }
    }
    | ID {
        for (int i = 0; i < $tabs; i++) {
            $program += "    ";
        }
        if ($changedNames.contains($ID.text)) {
            $declareTemp.add($ID.text);
            if ($declaredVariables.contains($name)) {
                $program += $name + " = " + $ID.text + "1;\n";
            } else {
                $declaredVariables.add($name);
                $program += $type + $name + " = " + $ID.text + "1;\n";
            }
        } else {
            if ($declaredVariables.contains($name)) {
                $program += $name + " = " + $ID.text + ";\n";
            } else {
                $declaredVariables.add($name);
                $program += $type + $name + " = " + $ID.text + ";\n";
            }
        }
    }
    ;

ID : [a-z]+ ;
VAL : [0-9]+ ;
WS : [ \t \r \n]+ -> skip ;