import org.junit.Test;

public class CompileTest {
    public String input = "E -> T E'\n" +
            "E' -> + T E'\n" +
            "E' -> epsilon\n" +
            "T -> F T'\n" +
            "T' -> * F T'\n" +
            "T' -> epsilon\n" +
            "F -> ( E )\n" +
            "F -> id";
    @Test
    public void testSyntax() {
        Syntax syntax = new Syntax(input);
        System.out.println(syntax);
    }

    @Test
    public void testStart() {
        Syntax syntax = new Syntax(input);
        System.out.println(syntax.startSymbol);
    }

    @Test
    public void testTerminal() {
        Syntax syntax = new Syntax(input);
        System.out.println(syntax.terminals);
    }

    @Test
    public void testNonTerminal() {
        Syntax syntax = new Syntax(input);
        System.out.println(syntax.nonTerminals);
    }

    @Test
    public void testFirst() {
        Syntax syntax = new Syntax(input);
        System.out.println(Algorithm.first(syntax));
    }
}
