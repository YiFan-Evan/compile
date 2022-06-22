public class Terminal extends Symbol{

    public static Terminal end = new Terminal("$");
    public static Terminal epsilon = new Terminal("epsilon");

    public boolean isEpsilon() {
        return this.name.equals("epsilon");
    }

    public boolean isEnd() {
        return this.name.equals("$");
    }

    public Terminal(String name) {
        assert name != null;
        assert name.length() > 0;
        assert !name.contains(" ");
        super.name = name;
    }


    @Override
    public boolean isTerminal() {
        return true;
    }

    @Override
    public boolean isNonTerminal() {
        return false;
    }
}
