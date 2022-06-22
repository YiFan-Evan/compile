import java.util.ArrayList;
import java.util.HashMap;

public class LL1Table {
    public HashMap<NonTerminal, HashMap<ArrayList<Terminal>, Production>> table;
    public Syntax syntax;

    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (NonTerminal nonTerminal : table.keySet()) {
            sb.append(nonTerminal.toString() + ":\n");
            for (ArrayList<Terminal> key : table.get(nonTerminal).keySet()) {
                sb.append("\t" + key.toString() + " -> " + table.get(nonTerminal).get(key).toString() + "\n");
            }
        }
        return sb.toString();
    }
}
