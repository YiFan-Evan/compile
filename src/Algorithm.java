import jdk.swing.interop.SwingInterOpUtils;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;

public class Algorithm {

    public static HashMap<NonTerminal, HashSet<Terminal>> first(Syntax syntax) {
        HashMap<NonTerminal, HashSet<Terminal>> first = new HashMap<>();
        for (NonTerminal nonTerminal : syntax.nonTerminals) {
            first.put(nonTerminal, first(syntax, nonTerminal, new HashSet<>()));
        }
        return first;
    }

    public static HashSet<Terminal> first(Syntax syntax, NonTerminal nonTerminal, HashSet<Terminal> terminals) {
        HashSet<Terminal> clone = (HashSet<Terminal>) terminals.clone();
        for (Production production : syntax.productions) {
            if (production.left.equals(nonTerminal)) {
                Symbol symbol = production.right.get(0);
                if (symbol instanceof Terminal) {
                    terminals.add((Terminal) symbol);
                } else {
                    terminals.addAll(first(syntax, (NonTerminal) symbol, terminals));
                }
            }
        }
        return terminals;
    }

    public static HashMap<NonTerminal, HashSet<Terminal>> follow(Syntax syntax) {
        HashMap<NonTerminal, HashSet<Terminal>> follow = new HashMap<>();
        for (NonTerminal nonTerminal : syntax.nonTerminals) {
            follow.put(nonTerminal, follow(syntax, nonTerminal, new HashSet<>(), new HashSet<>()));
        }
        return follow;
    }

    public static HashSet<Terminal> follow(Syntax syntax, NonTerminal nonTerminal, HashSet<Terminal> terminals, HashSet<NonTerminal> recursion) {
        HashSet<Terminal> clone = (HashSet<Terminal>) terminals.clone();
        if (nonTerminal.equals(syntax.startSymbol)) {
            terminals.add(Terminal.end);
        }
        for (Production production : syntax.productions) {
            for (int i = 0; i < production.right.size(); i++) {
                Symbol symbol = production.right.get(i);
                if (symbol.name.equals(nonTerminal.name)) {
                    if (i + 1 < production.right.size()) {
                        Symbol nextSymbol = production.right.get(i + 1);
                        if (nextSymbol instanceof NonTerminal) {
                            terminals.addAll(first(syntax, (NonTerminal) nextSymbol, new HashSet<>()));
                            if(terminals.contains(Terminal.epsilon)){
                                terminals.remove(Terminal.epsilon);
                                recursion.add((NonTerminal) nextSymbol);
                                terminals.addAll(follow(syntax, (NonTerminal) nextSymbol, new HashSet<>(), recursion));
                            }
                        } else {
                            terminals.add((Terminal) nextSymbol);
                        }
                    } else {
                        if (production.left != nonTerminal && !recursion.contains(production.left)) {
                            recursion.add(production.left);
                            terminals.addAll(follow(syntax, production.left, terminals, recursion));
                        }
                    }
                }
            }
        }
        return terminals;
    }

    public static LL1Table generateLL1Table(Syntax syntax) {
        LL1Table table = new LL1Table(syntax);
        for (Production production : syntax.productions) {
            Symbol symbol = production.right.get(0);
            if (symbol instanceof NonTerminal) {
                table.add(production.left, first(syntax, (NonTerminal) symbol, new HashSet<>()), production);
            } else {
                if(symbol.equals(Terminal.epsilon)) {
                    table.add(production.left, follow(syntax, production.left, new HashSet<>(), new HashSet<>()), production);
                } else {
                    table.add(production.left, (Terminal) symbol, production);
                }
            }
        }
        return table;
    }

    public static HashSet<LR1Production> calClosure(Syntax syntax, LR1Production production) {
        return null;
    }

    public static LR1Table generateLR1Table(Syntax syntax) {
        
        return null;
    }

}
