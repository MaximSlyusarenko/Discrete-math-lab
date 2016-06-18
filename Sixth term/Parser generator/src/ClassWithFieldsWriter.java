import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.List;
import java.util.Objects;

/**
 * Generates class which contains rule arguments.
 * They could be output (written in return block), locals (written in locals block) and input (written in parameters block).
 * @author Maxim Slyusarenko
 * @since 25.05.16
 */
public class ClassWithFieldsWriter {

    private final List<String> types;
    private final List<String> names;
    private final String untermName;
    private final String variablesBlock;

    public ClassWithFieldsWriter(List<String> types, List<String> names, String untermName, String variablesBlock) {
        this.types = Objects.requireNonNull(types, "types mustn't be null");
        this.names = Objects.requireNonNull(names, "names mustn't be null");
        if (types.size() != names.size()) {
            throw new IllegalArgumentException("types.size = " + types.size()
                    + ", names.size = " + names.size() + ", expected: equal sizes");
        }
        this.untermName = Objects.requireNonNull(untermName, "untermName mustn't be null").substring(1);
        variablesBlock = Objects.requireNonNull(variablesBlock, "variablesBlock mustn't be null");
        this.variablesBlock = variablesBlock.substring(0, 1).toUpperCase() + variablesBlock.substring(1);
    }

    public void makeDirectory() {
        File file = new File(System.getProperty("user.dir") + File.separator + "mygen");
        if (!file.mkdirs()) {
            System.err.println("Can't make directory mygen/");
        }
    }

    public void generateClass() {
        try (OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream("mygen" + File.separator + untermName.substring(0, 1).toUpperCase() + untermName.substring(1) + variablesBlock + "Arguments.java"))) {
            writer.write("import java.util.List;\nimport java.util.ArrayList;\nimport java.util.Set;\nimport java.util.Map;\n\n/* This code is generated */\npublic class " + untermName.substring(0, 1).toUpperCase() + untermName.substring(1) + variablesBlock + "Arguments {\n\n");
            int i = 0;
            for (String type : types) {
                writer.write("    private " + type + " " + names.get(i) + ";\n");
                i++;
            }
            // Constructor from given types:
            if (types.size() != 0) {
                writer.write("\n");
                i = 0;
                writer.write("    public " + untermName.substring(0, 1).toUpperCase() + untermName.substring(1) + variablesBlock + "Arguments(");
                for (String type : types) {
                    writer.write(type + " " + names.get(i));
                    if (i == names.size() - 1) {
                        writer.write(") {\n");
                    } else {
                        writer.write(", ");
                    }
                    i++;
                }
                for (String name : names) {
                    writer.write("        this." + name + " = " + name + ";\n");
                }
                writer.write("    }\n\n");
            }
            // Empty constructor:
            writer.write("    public " + untermName.substring(0, 1).toUpperCase() + untermName.substring(1) + variablesBlock + "Arguments() {\n    }\n\n");
            i = 0;
            for (String type : types) {
                String name = names.get(i);
                writer.write("    public void set" + name.substring(0, 1).toUpperCase() + name.substring(1) +
                        "(" + type + " " + name + ") {\n        this." + name + " = " + name + ";\n    }\n\n"); // setter
                i++;
            }
            i = 0;
            for (String type : types) {
                String name = names.get(i);
                writer.write("    public " + type + " get" + name.substring(0, 1).toUpperCase() + name.substring(1) +
                        "() {\n        return " + name + ";\n    }\n\n"); // getter
                i++;
            }
            writer.write("}");
        } catch (IOException e) {
            System.err.println("Something comes wrong with creating file for " + untermName + " arguments, message: " + e.getMessage());
        }
    }
}
