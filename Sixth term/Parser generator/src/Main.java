import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

/**
 * @author Maxim Slyusarenko
 * @since 01.06.16
 */
public class Main {

    public static void main(String[] args) {
        if (args == null || args.length != 1 || args[0] == null) {
            System.err.println("Usage: Main fileName");
            return;
        }
        String fileName = args[0];
        /*try (InputStream is = new FileInputStream(fileName)) {
            Parser parser = new Parser();
            parser.parse(is);
        } catch (ParseException e) {
            System.err.println(e.getMessage());
        } catch (IOException e) {
            System.err.println("Something comes wrong, message: " + e.getMessage());
        }*/
    }
}
