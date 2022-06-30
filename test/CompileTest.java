import org.junit.Test;

public class CompileTest {
    public String input = "A -> t";

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

    @Test
    public void testFollow() {
        Syntax syntax = new Syntax(input);
        System.out.println(Algorithm.follow(syntax));
    }

    @Test
    public void testLL1Table() {
        Syntax syntax = new Syntax(input);
        System.out.println(Algorithm.generateLL1Table(syntax));
    }

    @Test
    public void testLR1Table() {
        Syntax syntax = new Syntax(input);
        System.out.println(Algorithm.generateLR1Table(syntax));
    }
}
