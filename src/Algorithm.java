import java.util.*;
import java.util.concurrent.atomic.AtomicInteger;

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
        HashSet<LR1Production> lr1Productions = new HashSet<>();
        Queue<LR1Production> queue = new LinkedList<>();
        lr1Productions.add(production);
        queue.add(production);
        while (!queue.isEmpty()) {
            LR1Production lr1Production = queue.poll();
            if(lr1Production.dotNextIsNonTerminal()){
                for(int i=1;i<=syntax.productions.size();i++){
                    if(syntax.productions.get(i-1).left.equals(lr1Production.getDotNext())){
                        int finalI = i;
                        lr1Production.ifIsNonTerminalThenGetFirst(syntax).forEach(terminal ->
                        {
                            LR1Production newOne = new LR1Production(syntax.productions.get(finalI - 1), finalI, terminal);
                            if(!lr1Productions.contains(newOne)){
                                lr1Productions.add(newOne);
                                queue.add(newOne);
                            }
                        });
                    }
                }
            }
        }
        return lr1Productions;
    }

    public static LR1Table generateLR1Table(Syntax syntax) {
        LR1Table table = new LR1Table(syntax);
        NonTerminal startSymbol = syntax.startSymbol;
        NonTerminal start = new NonTerminal(startSymbol.name + "#");
        Queue<LR1State> queue = new LinkedList<>();
        AtomicInteger stateIndex = new AtomicInteger();
        LR1State startState = new LR1State(stateIndex.get(),
                new HashSet<>(Set.of(
                        new LR1Production(
                                new Production(start,
                                        new ArrayList<>(List.of(startSymbol))),
                                0, Terminal.end))), syntax);
        table.states.add(startState);
        queue.add(startState);
        while (!queue.isEmpty()) {
            LR1State next = queue.poll();
            HashMap<Symbol, HashSet<LR1Production>> map = new HashMap<>();
            for (LR1Production production : next.postProductions){
                if(!production.isEnd()){
                    Symbol dotNext = production.getDotNext();
                    if(map.containsKey(dotNext)){
                        map.get(dotNext).add(production.toNext());
                    } else {
                        HashSet<LR1Production> productions = new HashSet<>();
                        productions.add(production.toNext());
                        map.put(dotNext, productions);
                    }
                }else{
                    table.table.putIfAbsent(production.lookAHead, new HashMap<>());
                    table.table.get(production.lookAHead).put(next.index, "r"+production.productionIndex);
                }
            }
            map.forEach((key, value) -> {
                LR1State toState = null;
                for (LR1State state : table.states) {
                    if(state.preProductions.equals(value)){
                        toState = state;
                        break;
                    }
                }
                if(toState == null){
                    stateIndex.getAndIncrement();
                    toState = new LR1State(stateIndex.get(), value, syntax);
                    table.states.add(toState);
                    queue.add(toState);
                }
                table.gotos.add(new LR1Goto(next, toState, key));
            });
        }
        table.gotos.forEach(edge -> {
            if(edge.symbol instanceof NonTerminal){
                table.table.putIfAbsent(edge.symbol, new HashMap<>());
                table.table.get(edge.symbol).put(edge.from.index, ""+edge.to.index);
            }else{
                table.table.putIfAbsent(edge.symbol, new HashMap<>());
                table.table.get(edge.symbol).put(edge.from.index, "s"+edge.to.index);
            }
        });
        return table;
    }

}
