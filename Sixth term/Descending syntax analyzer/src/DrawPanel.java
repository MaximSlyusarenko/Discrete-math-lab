import javafx.util.Pair;

import javax.swing.*;
import java.awt.*;

public class DrawPanel extends JPanel {

    private Tree tree;
    private UITree uiTree;
    private final int radius = 10;

    private UITree dfs(Tree tree) {
        if (tree.getChildren() == null) {
            return new UITree(new Pair<>(0, 0));
        }
        if (tree.getChildren().size() == 1) {
            return new UITree(new Pair<>(1, 1), dfs(tree.getChildren().get(0)));
        } else if (tree.getChildren().size() == 2) {
            UITree left = dfs(tree.getChildren().get(0));
            UITree right = dfs(tree.getChildren().get(1));
            return new UITree(new Pair<>((left.getShift().getValue() + right.getShift().getKey()) / 2 + 1, (left.getShift().getValue() + right.getShift().getKey()) / 2 + 1), left, right);
        } else {
            UITree left = dfs(tree.getChildren().get(0));
            UITree center = dfs(tree.getChildren().get(1));
            UITree right = dfs(tree.getChildren().get(2));
            return new UITree(new Pair<>(left.getShift().getValue() + center.getShift().getKey(), center.getShift().getValue() + right.getShift().getKey()), left, center, right);
        }
    }

    public DrawPanel(Tree tree) {
        this.tree = tree;
    }

    private void drawTree(Tree tree, UITree uiTree, int x, int y, Graphics g) {
        int leftMultiplier = Math.max(uiTree.getShift().getKey(), 1);
        int rightMultiplier = Math.max(uiTree.getShift().getValue(), 1);
        g.drawString(tree.getNode(), x - radius / 2, y + radius / 2);
        if (tree.getChildren() == null) {
            if (tree.getNode().charAt(0) >= 'A' && tree.getNode().charAt(0) <= 'Z') {
                g.setColor(Color.GREEN);
            } else {
                g.setColor(Color.RED);
            }
            g.drawOval(x - radius, y - radius, 2 * radius, 2 * radius);
            g.setColor(Color.black);
            return;
        }
        g.drawOval(x - radius, y - radius, 2 * radius, 2 * radius);
        if (tree.getChildren().size() == 1) {
            g.drawLine(x, y + radius, x, y + 3 * radius);
            drawTree(tree.getChildren().get(0), uiTree.getChildren().get(0), x, y + 4 * radius, g);
        } else if (tree.getChildren().size() == 2) {
            g.drawLine(x, y + radius, x - 2 * leftMultiplier * radius, y + 3 * radius);
            drawTree(tree.getChildren().get(0), uiTree.getChildren().get(0), x - 2 * leftMultiplier * radius, y + 4 * radius, g);
            g.drawLine(x, y + radius, x + 2 * rightMultiplier * radius, y + 3 * radius);
            drawTree(tree.getChildren().get(1), uiTree.getChildren().get(1), x + 2 * rightMultiplier * radius, y + 4 * radius, g);
        } else if (tree.getChildren().size() == 3) {
            g.drawLine(x, y + radius, x - 2 * leftMultiplier * radius, y + 3 * radius);
            drawTree(tree.getChildren().get(0), uiTree.getChildren().get(0), x - 2 * leftMultiplier * radius, y + 4 * radius, g);
            g.drawLine(x, y + radius, x, y + 3 * radius);
            drawTree(tree.getChildren().get(1), uiTree.getChildren().get(1), x, y + 4 * radius, g);
            g.drawLine(x, y + radius, x + 2 * rightMultiplier * radius, y + 3 * radius);
            drawTree(tree.getChildren().get(2), uiTree.getChildren().get(2), x + 2 * rightMultiplier * radius, y + 4 * radius, g);
        }
    }

    @Override
    public void paintComponent(Graphics g) {
        uiTree = dfs(tree);
        drawTree(tree, uiTree, getWidth() / 2, 2 * radius, g);
    }
}
