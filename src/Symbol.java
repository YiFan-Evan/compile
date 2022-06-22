import java.util.Objects;

public abstract class Symbol {

    public String name;

    public String toString() {
        return name;
    }

    public abstract boolean isTerminal();

    public abstract boolean isNonTerminal();

    public abstract boolean isEpsilon();

    public abstract boolean isEnd();


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Symbol symbol = (Symbol) o;
        return Objects.equals(name, symbol.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }
}
