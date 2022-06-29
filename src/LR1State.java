import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Objects;
import java.util.logging.Handler;

public class LR1State {

    public int index;
    public HashSet<LR1Production> preProductions;
    public HashSet<LR1Production> postProductions;
    public Syntax syntax;

    public LR1State(int index, HashSet<LR1Production> preProductions, Syntax syntax) {
        this.index = index;
        this.preProductions = preProductions;
        this.syntax = syntax;
        calPostProductions();
    }

    public void calPostProductions(){
        postProductions = new HashSet<>();
        for (LR1Production preProduction : preProductions) {
            //!!!!!!!!!!!!!!!
            postProductions.addAll(Algorithm.calClosure(syntax, preProduction));
        }
        int count = postProductions.size();
        do{
            for (LR1Production postProduction : postProductions) {
                postProductions.addAll(Algorithm.calClosure(syntax, postProduction));
            }
        }
        while(count != postProductions.size());
    }

    public HashSet<LR1Production> go(Symbol symbol){
        HashSet<LR1Production> result = new HashSet<>();
        for (LR1Production postProduction : postProductions) {
            if(postProduction.getDotNext().equals(symbol)){
                result.add(postProduction.toNext());
            }
        }
        return result;
    }

    @Override
    public String toString() {
        return "LR1State{" +
                "index=" + index +
                ", preProductions=" + preProductions +
                ", postProductions=" + postProductions +
                '}';
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        LR1State lr1State = (LR1State) o;
        return preProductions.equals(lr1State.preProductions);
    }

    @Override
    public int hashCode() {
        return Objects.hash(preProductions);
    }
}
