import java.util.Objects;

public class LR1Goto {

    public LR1State from;
    public LR1State to;
    public Symbol symbol;

    public LR1Goto(LR1State from, LR1State to, Symbol symbol) {
        this.from = from;
        this.to = to;
        this.symbol = symbol;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        LR1Goto lr1Goto = (LR1Goto) o;
        return from.equals(lr1Goto.from) && symbol.equals(lr1Goto.symbol);
    }

    @Override
    public int hashCode() {
        return Objects.hash(from, symbol);
    }

    @Override
    public String toString() {
        return "LR1Goto{" +
                "from=" + from +
                ", to=" + to +
                ", symbol=" + symbol +
                '}';
    }
}
