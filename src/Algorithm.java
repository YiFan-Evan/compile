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

//        (1) 若X ∈ Vt，则FIRST(X) = {X}。(即定义1)
//        (2）若X ∈ Vn，且有产生式X → a……， a ∈ Vt，则a ∈ FIRST(X) (非终结符，将首个终结符加入First集)
//        (3）若X ∈ VN，X → ε，则 ε ∈ FIRST(X) (直接推导)
//        (4）若X→Y1,Y2,……,Yn ∈ Vn，而有产生式X → Y1,Y2,……,Yn。当Y1,Y2,……,Y(i-1) 直接推出ε时，则FIRST(Y1) - ε, FIRST(Y2) - ε, …… , FIRST(Y(i-1) - ε) ,FIRST(Yi) 都包含在FIRST(X)中(无ε)
//        (5）当(4）中所有Yi 都推出 ε时，则最后的FIRST(X) = FIRST(Y1) ∪ FIRST(Y2) ∪ …… ∪ FIRST(Yn) ∪ {ε}
//        反复运用(2）-(5）步骤计算，直到每个符号的FIRST集合不再增大为止

        HashSet<Terminal> clone = (HashSet<Terminal>) terminals.clone();
        for (Production production : syntax.productions) {
            if (production.left.equals(nonTerminal)) {
                Symbol symbol = production.right.get(0);
                if (symbol instanceof Terminal) {
                    terminals.add((Terminal) symbol);
                } else {
                    if (terminals != clone) {
                        terminals.addAll(first(syntax, (NonTerminal) symbol, terminals));
                    }
                }
            }
        }
        return terminals;
    }

    public static HashMap<NonTerminal, ArrayList<Terminal>> follow(Syntax syntax) {

        return null;
    }

}
