public class NonTerminal extends Symbol{


    public NonTerminal(String name) {
        assert name != null;
        assert name.length() > 0;
        assert !name.contains(" ");
        super.name = name;
    }


    @Override
    public boolean isTerminal() {
        return false;
    }

    @Override
    public boolean isNonTerminal() {
        return true;
    }

    @Override
    public boolean isEpsilon() {
        return false;
    }

    @Override
    public boolean isEnd() {
        return false;
    }
}
