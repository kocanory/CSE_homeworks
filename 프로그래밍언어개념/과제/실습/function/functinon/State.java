import java.util.*;

public class State extends HashMap<Variable, Value> {
    // Defines the set of variables and their associated values
    // that are active during interpretation

    public State() {
    }

    public State(Variable key, Value val) {
        put(key, val); // 변수와 변수값을 state에 입력
    }

    public State onion(Variable key, Value val) {
        put(key, val); // 변수와 변경된 변수값을 state에 입력
        return this;
    }

    public State onion(State t) {
        for (Variable key : t.keySet())
            put(key, t.get(key)); // state에 있는 모든 변수에 대하여 변수와 변수값을 state에 입력
        return this;
    }

    void display() {
        Iterator<Variable> iterator = this.keySet().iterator();
        while (iterator.hasNext()) {
            Variable key = (Variable) iterator.next();
            System.out.println("  <" + key + ", " + this.get(key) + ">");
        }
    }
}
