public class Semantics {

    State M(Program p) {
        return M(p.body, initialState(p.decpart)); // initial state로 body의 meaning 파악
    }

    State initialState(Declarations d) {
        State state = new State();
        Value intUndef = new IntValue();
        for (Declaration decl : d)
            state.put(decl.v, Value.mkValue(decl.t)); // decpart에 정의된 변수를 state에 입력
        return state;
    }

    State M(Statement s, State state) {
        if (s instanceof Skip) // statement가 skip인 경우
            return M((Skip) s, state);
        if (s instanceof Assignment) // statement가 assignment인 경우
            return M((Assignment) s, state);
        if (s instanceof Conditional) // statement가 conditional인 경우
            return M((Conditional) s, state);
        if (s instanceof Loop) // statement가 loop인 경우
            return M((Loop) s, state);
        if (s instanceof Block) // statement가 block인 경우
            return M((Block) s, state);
        throw new IllegalArgumentException("should never reach here");
    }

    State M(Skip s, State state) {
        return state; // state가 변하지 않음
    }

    State M(Assignment a, State state) {
        return state.onion(a.target, M(a.source, state)); // 변경된 state를 업데이트
    }

    State M(Block b, State state) {
        for (Statement s : b.members)
            state = M(s, state); // block 안의 모든 statement에 대하여 meaning 파악
        return state;
    }

    State M(Conditional c, State state) {
        if (M(c.test, state).boolValue()) // test가 true일 경우
            return M(c.thenbranch, state); // thenbranch의 meaning 파악
        else // test가 false일 경우
            return M(c.elsebranch, state); // elsebranch의 meaning 파악
    }

    State M(Loop l, State state) {
        if (M(l.test, state).boolValue()) // test가 true일 경우
            return M(l, M(l.body, state)); // body의 meaning 파악
        else
            return state; // loop가 끝나면 바뀐 state를 리턴
    }

    Value applyBinary(Operator op, Value v1, Value v2) {
        StaticTypeCheck.check(!v1.isUndef() && !v2.isUndef(),
                "reference to undef value"); // 두 operand가 앞서 정의되어 있는지 확인하고, 그렇지 않으면 오류메세지 출력
        if (op.val.equals(Operator.INT_PLUS))
            return new IntValue(v1.intValue() + v2.intValue()); // 정수형 + 연산일 경우 + 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.INT_MINUS))
            return new IntValue(v1.intValue() - v2.intValue()); // 정수형 - 연산일 경우 - 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.INT_TIMES))
            return new IntValue(v1.intValue() * v2.intValue()); // 정수형 * 연산일 경우 * 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.INT_DIV))
            return new IntValue(v1.intValue() / v2.intValue()); // 정수형 / 연산일 경우 / 연산 후에 나온 값 리턴

        if (op.val.equals(Operator.INT_LT))
            return new BoolValue(v1.intValue() < v2.intValue()); // 정수형 < 연산일 경우 < 연산 후에 true, false 리턴
        if (op.val.equals(Operator.INT_LE))
            return new BoolValue(v1.intValue() <= v2.intValue()); // 정수형 <= 연산일 경우 <= 연산 후에 true, false 리턴
        if (op.val.equals(Operator.INT_EQ))
            return new BoolValue(v1.intValue() == v2.intValue()); // 정수형 == 연산일 경우 == 연산 후에 true, false 리턴
        if (op.val.equals(Operator.INT_LE))
            return new BoolValue(v1.intValue() != v2.intValue()); // 정수형 != 연산일 경우 != 연산 후에 true, false 리턴
        if (op.val.equals(Operator.INT_GT))
            return new BoolValue(v1.intValue() > v2.intValue()); // 정수형 > 연산일 경우 > 연산 후에 true, false 리턴
        if (op.val.equals(Operator.INT_GE))
            return new BoolValue(v1.intValue() >= v2.intValue()); // 정수형 >= 연산일 경우 >= 연산 후에 true, false 리턴

        if (op.val.equals(Operator.FLOAT_PLUS))
            return new FloatValue(v1.floatValue() + v2.floatValue()); // 실수형 + 연산일 경우 + 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.FLOAT_MINUS))
            return new FloatValue(v1.floatValue() - v2.floatValue()); // 실수형 - 연산일 경우 - 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.FLOAT_TIMES))
            return new FloatValue(v1.floatValue() * v2.floatValue()); // 실수형 * 연산일 경우 * 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.FLOAT_DIV))
            return new FloatValue(v1.floatValue() / v2.floatValue()); // 실수형 / 연산일 경우 / 연산 후에 나온 값 리턴

        if (op.val.equals(Operator.FLOAT_LT))
            return new BoolValue(v1.floatValue() < v2.floatValue()); // 실수형 < 연산일 경우 < 연산 후에 true, false 리턴
        if (op.val.equals(Operator.FLOAT_LE))
            return new BoolValue(v1.floatValue() <= v2.floatValue()); // 실수형 <= 연산일 경우 <= 연산 후에 true, false 리턴
        if (op.val.equals(Operator.FLOAT_EQ))
            return new BoolValue(v1.floatValue() == v2.floatValue()); // 실수형 == 연산일 경우 == 연산 후에 true, false 리턴
        if (op.val.equals(Operator.FLOAT_LE))
            return new BoolValue(v1.floatValue() != v2.floatValue()); // 실수형 != 연산일 경우 != 연산 후에 true, false 리턴
        if (op.val.equals(Operator.FLOAT_GT))
            return new BoolValue(v1.floatValue() > v2.floatValue()); // 실수형 > 연산일 경우 > 연산 후에 true, false 리턴
        if (op.val.equals(Operator.FLOAT_GE))
            return new BoolValue(v1.floatValue() >= v2.floatValue()); // 실수형 >= 연산일 경우 >= 연산 후에 true, false 리턴

        if (op.val.equals(Operator.CHAR_LT))
            return new BoolValue(v1.charValue() < v2.charValue()); // 문자형 < 연산일 경우 < 연산 후에 true, false 리턴
        if (op.val.equals(Operator.CHAR_LE))
            return new BoolValue(v1.charValue() <= v2.charValue()); // 문자형 <= 연산일 경우 <= 연산 후에 true, false 리턴
        if (op.val.equals(Operator.CHAR_EQ))
            return new BoolValue(v1.charValue() == v2.charValue()); // 문자형 == 연산일 경우 == 연산 후에 true, false 리턴
        if (op.val.equals(Operator.CHAR_LE))
            return new BoolValue(v1.charValue() != v2.charValue()); // 문자형 != 연산일 경우 != 연산 후에 true, false 리턴
        if (op.val.equals(Operator.CHAR_GT))
            return new BoolValue(v1.charValue() > v2.charValue()); // 문자형 > 연산일 경우 > 연산 후에 true, false 리턴
        if (op.val.equals(Operator.CHAR_GE))
            return new BoolValue(v1.charValue() >= v2.charValue()); // 문자형 >= 연산일 경우 >= 연산 후에 true, false 리턴

        if (op.val.equals(Operator.BOOL_EQ))
            return new BoolValue(v1.boolValue() == v2.boolValue()); // 두 논리값이 같은지 확인하고 true, false 리턴
        if (op.val.equals(Operator.BOOL_LE))
            return new BoolValue(v1.boolValue() != v2.boolValue()); // 두 논리값이 다른지 확인하고 true, false 리턴
        throw new IllegalArgumentException("should never reach here");
    }

    Value applyUnary(Operator op, Value v) {
        StaticTypeCheck.check(!v.isUndef(),
                "reference to undef value"); // operand가 정의되어 있는지 확인하고, 그렇지 않으면 오류메세지 출력
        if (op.val.equals(Operator.NOT))
            return new BoolValue(!v.boolValue()); // ! 연산일 경우, ! 연산 후 논리값 리턴
        else if (op.val.equals(Operator.INT_NEG))
            return new IntValue(-v.intValue()); // 정수형 - 연산일 경우, - 연산 후 정수값 리턴
        else if (op.val.equals(Operator.FLOAT_NEG))
            return new FloatValue(-v.floatValue()); // 실수형 - 연산일 경우, - 연산 후 실수값 리턴
        else if (op.val.equals(Operator.I2F))
            return new FloatValue((float) (v.intValue())); // int to float 연산일 경우, 형 변환 후 값 리턴
        else if (op.val.equals(Operator.F2I))
            return new IntValue((int) (v.floatValue())); // float to int 연산일 경우, 형 변환 후 값 리턴
        else if (op.val.equals(Operator.C2I))
            return new IntValue((int) (v.charValue())); // char to int 연산일 경우, 형 변환 후 값 리턴
        else if (op.val.equals(Operator.I2C))
            return new CharValue((char) (v.intValue())); // int to char 연산일 경우, 형 변환 후 값 리턴
        throw new IllegalArgumentException("should never reach here");
    }

    Value M(Expression e, State state) {
        if (e instanceof Value)
            return (Value) e; // value인 경우 value값 리턴
        if (e instanceof Variable)
            return (Value) (state.get(e)); // variable인 경우 variable에 저장되어 있는 값 리턴
        if (e instanceof Binary) {
            Binary b = (Binary) e;
            return applyBinary(b.op,
                    M(b.term1, state), M(b.term2, state)); // binary인 경우 두 operand의 meaning을 이용하여 연산
        }
        if (e instanceof Unary) {
            Unary u = (Unary) e;
            return applyUnary(u.op, M(u.term, state)); // unary인 경우 operand의 meaning을 이용하여 연산
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void main(String args[]) {
        Parser parser = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
        prog.display(); // parsing 후 program의 AST 출력
        System.out.println("\nBegin type checking...programs/" + args[0] + "\n");
        System.out.println("Type map:");
        TypeMap map = StaticTypeCheck.typing(prog.decpart);
        map.display(); // type map 출력
        StaticTypeCheck.V(prog); // type check 실행
        Program out = TypeTransformer.T(prog, map);
        System.out.println("Output AST");
        out.display(); // type transform 후 AST 출력
        Semantics semantics = new Semantics();
        State state = semantics.M(out); // program의 meaning 파악
        System.out.println("\nBegin interpreting...programs/" + args[0] + "\n");
        System.out.println("Final State");
        state.display(); // 최종 state 출력
    }
}
