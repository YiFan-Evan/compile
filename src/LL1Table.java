import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class LL1Table {
    public HashMap<NonTerminal, HashMap<Terminal, Production>> table;
    public Syntax syntax;

    public LL1Table(Syntax syntax) {
        table = new HashMap<>();
        syntax.nonTerminals.forEach(nonTerminal -> {
            table.put(nonTerminal, new HashMap<>());
        });
        this.syntax = syntax;
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        for (NonTerminal nonTerminal : syntax.nonTerminals) {
            sb.append(nonTerminal.name + ":\n");
            for (Terminal terminal : syntax.terminals) {
                Production production = table.get(nonTerminal).get(terminal);
                if (production != null) {
                    sb.append("\t" + "[" + nonTerminal + "," + terminal.name + "] = {" + production + "}\n");
                }
            }
        }
        return sb.toString();
    }

    public void add(NonTerminal nonTerminal, Terminal terminal, Production production) {
        assert production.left.equals(nonTerminal);
        HashMap<Terminal, Production> map = table.get(nonTerminal);
        assert !map.containsKey(terminal);
        map.put(terminal, production);
    }

    public void add(NonTerminal nonTerminal, HashSet<Terminal> key, Production production) {
        for (Terminal terminal : key) {
            add(nonTerminal, terminal, production);
        }
    }

}
