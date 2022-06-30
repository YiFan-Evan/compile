import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class LR1Table {
    public HashMap<Symbol, HashMap<Integer, String>> table;
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
                return print_table_json();
            case "text":
                return print_table_text();
            case "csv":
                return print_table_csv();
            case "tree":
                return print_table_tree();
        }
        return null;
    }

    public String print_table_json(){
        StringBuilder sb = new StringBuilder();
        sb.append("{");
        for (Symbol symbol : table.keySet()) {
            sb.append("\"" + symbol.toString() + "\": {");
            HashMap<Integer, String> map = table.get(symbol);
            for (Integer key : map.keySet()) {
                sb.append("\"" + key + "\": \"" + map.get(key) + "\", ");
            }
            sb.append("}, ");
        }
        sb.append("}");
        return sb.toString();
    }

    public String print_table_text(){
        StringBuilder sb = new StringBuilder();
        for (Symbol symbol : table.keySet()) {
            sb.append(symbol.toString() + ":\n");
            HashMap<Integer, String> map = table.get(symbol);
            for (Integer key : map.keySet()) {
                sb.append("\t" + "[" + symbol + "," + key + "] = " + map.get(key) + "\n");
            }
        }
        return sb.toString();
    }

    public String print_table_csv(){
        StringBuilder sb = new StringBuilder();
        for (Symbol symbol : table.keySet()) {
            HashMap<Integer, String> map = table.get(symbol);
            for (Integer key : map.keySet()) {
                sb.append(symbol.toString() + "," + key + "," + map.get(key) + "\n");
            }
        }
        return sb.toString();
    }

    public String print_table_tree(){
        StringBuilder sb = new StringBuilder();
        for (Symbol symbol : table.keySet()) {
            sb.append(symbol.toString() + ":\n");
            HashMap<Integer, String> map = table.get(symbol);
            for (Integer key : map.keySet()) {
                sb.append("\t" + "[" + symbol + "," + key + "] = " + map.get(key) + "\n");
            }
        }
        return sb.toString();
    }
}
