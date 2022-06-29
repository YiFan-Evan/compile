import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class LR1Table {
    public HashMap<NonTerminal, HashMap<ArrayList<Terminal>, String>> table;
    public Syntax syntax;
    public HashSet<LR1State> states;
    public HashSet<LR1Goto> gotos;

    public LR1Table(Syntax syntax) {
        this.syntax = syntax;
        table = new HashMap<>();
        states = new HashSet<>();
        gotos = new HashSet<>();
    }

    @Override
    public String toString() {
        return "LR1Table{" +
                "table=" + table +
                ", syntax=" + syntax +
                ", states=" + states +
                ", gotos=" + gotos +
                '}';
    }

    public String print_table(String format) {
        switch (format) {
            case "json":
                return null;
            case "text":
                return null;
            case "csv":
                return null;
            case "tree":
                return null;
        }
        return null;
    }
}
