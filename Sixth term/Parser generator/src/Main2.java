import javax.swing.*;
import java.awt.*;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.text.ParseException;

/**
 * @author Maxim Slyusarenko
 * @since 02.06.16
 */
public class Main2 {

    public static void main(String[] args) {
        if (args == null || args.length != 1 || args[0] == null) {
            System.err.println("Usage: Main fileName");
            return;
        }
        String fileName = args[0];
        try (InputStream is = new FileInputStream(fileName)) {
            Parser parser = new Parser();
            JFrame frame = new JFrame();
            frame.setSize(2000, 2000);
            DrawPanel drawPanel = new DrawPanel(parser.parse(is));
            //drawPanel.setMinimumSize(new Dimension(300, 300));
            drawPanel.setPreferredSize(new Dimension(1500, 1500));
            JScrollPane scrollPane = new JScrollPane(drawPanel, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
            //scrollPane.setMinimumSize(new Dimension(300, 300));
            scrollPane.setPreferredSize(new Dimension(1500, 1500));
            frame.add(scrollPane);
            frame.setVisible(true);
            frame.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
        } catch (FileNotFoundException e) {
            System.err.println("Can't find file " + fileName);
        } catch (IOException ignored) {
        } catch (ParseException e) {
            System.err.println(e.getMessage());
        }
    }
}
