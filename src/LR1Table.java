import java.util.ArrayList;
import java.util.HashMap;

public class LR1Table {
    public HashMap<NonTerminal, HashMap<ArrayList<Terminal>, Production>> table;
    public Syntax syntax;

}
