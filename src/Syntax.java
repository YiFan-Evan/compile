import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.concurrent.atomic.AtomicBoolean;

public class Syntax {
    public ArrayList<Production> productions;
    public HashSet<NonTerminal> nonTerminals;
    public HashSet<Terminal> terminals;
    public NonTerminal startSymbol;

    public Syntax(ArrayList<Production> productions){
        init();
        makeSyntax(productions);
    }

    private void init(){
        nonTerminals = new HashSet<>();
        terminals = new HashSet<>();
        productions = new ArrayList<>();
    }

    private void makeSyntax(ArrayList<Production> productions){
        startSymbol = productions.get(0).left;
        productions.forEach(production -> nonTerminals.add(production.left));
        productions.forEach(production ->{
            Production new_production = new Production(production.left);
            production.right.forEach(symbol ->{
                if(nonTerminals.contains(new NonTerminal(symbol.toString()))){
                    new_production.addRight(new NonTerminal(symbol.toString()));
                }else{
                    Terminal terminal = new Terminal(symbol.toString());
                    new_production.addRight(terminal);
                    terminals.add(terminal);
                }
            });
            this.productions.add(new_production);
        });
    }

    public Syntax(String syntax) {
        init();
        ArrayList<Production> productions = new ArrayList<>();
        for (String pro : syntax.split("\n")) {
            Production production = new Production(pro);
            productions.add(production);
        }
        makeSyntax(productions);
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();
        for (Production production : productions) {
            sb.append(production.toString() + "\n");
        }
        return sb.toString().trim();
    }

    public LL1Table generateLL1Table() {

        return null;
    }

    public LR1Table generateLR1Table() {

        return null;
    }

}
