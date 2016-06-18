import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.util.Map;

/**
 * Generates Enum for tokens
 * @author Maxim Slyusarenko
 * @since 27.05.16
 */
public class TokensEnumWriter {

    private final Map<String, String> tokens;

    public TokensEnumWriter(Map<String, String> tokens) {
        this.tokens = tokens;
    }

    public void generateEnum() {
        try (OutputStreamWriter writer = new OutputStreamWriter(new FileOutputStream("mygen" + File.separator + "Token.java"))) {
            writer.write("/* This code is generated */\npublic enum Token {\n");
            int i = 0;
            for (Map.Entry<String, String> token : tokens.entrySet()) {
                writer.write("    " + token.getKey());
                if (i != tokens.size() - 1) {
                    writer.write(",");
                }
                writer.write(" // \"" + token.getValue() + "\"\n");
                i++;
            }
            writer.write("}");
        } catch (IOException e) {
            System.err.println("Something comes wrong with creating file for tokens enum arguments, message: " + e.getMessage());
        }
    }
}