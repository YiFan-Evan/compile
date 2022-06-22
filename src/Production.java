import java.util.ArrayList;

public class Production {

    public NonTerminal left;
    public ArrayList<Symbol> right;

    public Production(NonTerminal left, ArrayList<Symbol> right) {
        this.left = left;
        this.right = right;
    }

    public Production(String production) {
        String[] parts = production.split("->");
        this.left = new NonTerminal(parts[0].trim());
        this.right = new ArrayList<Symbol>();
        for (String part : parts[1].split(" ")) {
            if(part.equals("")){
                continue;
            }
            if (part.equals(left.toString())) {
                this.right.add(new NonTerminal(part.trim()));
            }else{
                this.right.add(new Terminal(part.trim()));
            }
        }
    }

    public Production(NonTerminal left) {
        this.left = left;
        this.right = new ArrayList<Symbol>();
    }

    public void addRight(Symbol symbol) {
        this.right.add(symbol);
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(left.toString() + " -> ");
        for (Symbol symbol : right) {
            sb.append(symbol.toString() + " ");
        }
        return sb.toString().trim();
    }

}
