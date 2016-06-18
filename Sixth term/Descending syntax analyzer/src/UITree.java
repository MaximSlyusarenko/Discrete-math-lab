import javafx.util.Pair;

import java.util.Arrays;
import java.util.List;

public class UITree {

    private Pair<Integer, Integer> shift;
    private List<UITree> children;

    public UITree(Pair<Integer, Integer> shift, UITree... children) {
        this.shift = shift;
        this.children = Arrays.asList(children);
    }

    public UITree(Pair<Integer, Integer> shift) {
        this.shift = shift;
    }

    public Pair<Integer, Integer> getShift() {
        return shift;
    }

    public List<UITree> getChildren() {
        return children;
    }
}
