import java.util.HashSet;
import java.util.List;
import java.util.Objects;

public class LR1Production {
    public Production production;
    public int dotPosition;
    public int productionIndex;
    public Terminal lookAHead;

    public LR1Production(Production production, int productionIndex, Terminal lookAHead) {
        this.production = production;
        this.productionIndex = productionIndex;
        this.lookAHead = lookAHead;
    }

    public LR1Production toNext(){
        LR1Production next = new LR1Production(this.production, this.productionIndex, this.lookAHead);
        next.dotPosition = this.dotPosition + 1;
        return next;
    }

    public boolean isEnd(){
        return production.right.size() == dotPosition;
    }

    public boolean dotNextIsTerminal(){
        if(isEnd()) return false;
        return production.right.get(dotPosition).isTerminal();
    }

    public boolean dotNextIsNonTerminal(){
        if(isEnd()) return false;
        return production.right.get(dotPosition).isNonTerminal();
    }

    public List<Symbol> ifIsNonTerminalThenGetRight(){
        assert dotNextIsNonTerminal();
        List<Symbol> symbols = production.right.subList(dotPosition, production.right.size());
        symbols.add(lookAHead);
        return symbols;
    }

    public HashSet<Terminal> ifIsNonTerminalThenGetFirst(Syntax syntax){
        assert dotNextIsNonTerminal();
        List<Symbol> symbols = ifIsNonTerminalThenGetRight();
        HashSet<Terminal> terminals = new HashSet<>();
        for (Symbol symbol : symbols) {
            if(symbol.isTerminal()){
                terminals.add((Terminal) symbol);
                break;
            }else{
                terminals.addAll(Algorithm.first(syntax, (NonTerminal) symbol, new HashSet<>()));
                if(terminals.contains(Terminal.epsilon)) {
                    terminals.remove(Terminal.epsilon);
                }else {
                    break;
                }
            }
        }
        return terminals;
    }

    @Override
    public String toString() {
        return "LR1Production{" +
                "production=" + production +
                ", dotPosition=" + dotPosition +
                ", productionIndex=" + productionIndex +
                ", lookAHead=" + lookAHead +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        LR1Production that = (LR1Production) o;
        return dotPosition == that.dotPosition && productionIndex == that.productionIndex && production.equals(that.production) && lookAHead.equals(that.lookAHead);
    }

    @Override
    public int hashCode() {
        return Objects.hash(production, dotPosition, productionIndex, lookAHead);
    }

    public Symbol getDotNext(){
        return production.right.get(dotPosition);
    }
}
