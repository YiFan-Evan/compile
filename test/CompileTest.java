import org.junit.Test;

public class CompileTest {
//    public String input = "E -> T E'\n" +
//            "E' -> + T E'\n" +
//            "E' -> epsilon\n" +
//            "T -> F T'\n" +
//            "T' -> * F T'\n" +
//            "T' -> epsilon\n" +
//            "F -> ( E )\n" +
//            "F -> id";

    public String input = "A -> C\n" +
            "B -> E\n" +
            "B -> F\n" +
            "B -> G\n" +
            "B -> C\n" +
            "C -> { D }\n" +
            "D -> B D\n" +
            "D -> epsilon\n" +
            "E -> if ( H ) then B else B\n" +
            "F -> while ( H ) B\n" +
            "G -> ID = J ;\n" +
            "H -> J I J\n" +
            "I -> <\n" +
            "I -> >\n" +
            "I -> <=\n" +
            "I -> >=\n" +
            "I -> ==\n" +
            "J -> L K\n" +
            "K -> + L K\n" +
            "K -> - L K\n" +
            "K -> epsilon\n" +
            "L -> N  M\n" +
            "M -> * N M\n" +
            "M -> / N M\n" +
            "M -> epsilon\n" +
            "N -> ID\n" +
            "N -> NUM\n" +
            "N -> ( J )";

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
}
