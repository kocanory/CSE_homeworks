public class DynamicTyping extends Semantics {

    State M(Program p) {
        return M(p.body, new State());
    }

    Value applyBinary(Operator op, Value v1, Value v2) {
        StaticTypeCheck.check(v1.type() == v2.type(),
                "mismatched types"); // 두 operand의 type이 같은지 확인하고, 그렇지 않으면 오류메세지 출력
        if (op.ArithmeticOp()) { // Arithmetic op인 경우
            if (v1.type() == Type.INT) { // operand의 type이 int일때
                if (op.val.equals(Operator.PLUS))
                    return new IntValue(v1.intValue() + v2.intValue()); // + 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.MINUS))
                    return new IntValue(v1.intValue() - v2.intValue()); // - 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.TIMES))
                    return new IntValue(v1.intValue() * v2.intValue()); // * 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.DIV))
                    return new IntValue(v1.intValue() / v2.intValue()); // / 연산을 수행하고 값 리턴
            } else if (v1.type() == Type.FLOAT) { // operand의 type이 float일때
                if (op.val.equals(Operator.PLUS))
                    return new FloatValue(v1.floatValue() + v2.floatValue()); // + 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.MINUS))
                    return new FloatValue(v1.floatValue() - v2.floatValue()); // - 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.TIMES))
                    return new FloatValue(v1.floatValue() * v2.floatValue()); // * 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.DIV))
                    return new FloatValue(v1.floatValue() / v2.floatValue()); // / 연산을 수행하고 값 리턴
            }
        } else if (op.RelationalOp()) // Relational op인 경우
        {
            if (v1.type() == Type.INT) { // operand의 type이 int일때
                if (op.val.equals(Operator.LT))
                    return new BoolValue(v1.intValue() < v2.intValue()); // < 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.LE))
                    return new BoolValue(v1.intValue() <= v2.intValue()); // <= 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.EQ))
                    return new BoolValue(v1.intValue() == v2.intValue()); // == 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.NE))
                    return new BoolValue(v1.intValue() != v2.intValue()); // != 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.GT))
                    return new BoolValue(v1.intValue() > v2.intValue()); // > 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.GE))
                    return new BoolValue(v1.intValue() >= v2.intValue()); // >= 연산을 수행하고 값 리턴
            } else if (v1.type() == Type.FLOAT) { // operand의 type이 float일때
                if (op.val.equals(Operator.LT))
                    return new BoolValue(v1.floatValue() < v2.floatValue()); // < 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.LE))
                    return new BoolValue(v1.floatValue() <= v2.floatValue()); // <= 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.EQ))
                    return new BoolValue(v1.floatValue() == v2.floatValue()); // == 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.NE))
                    return new BoolValue(v1.floatValue() != v2.floatValue()); // != 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.GT))
                    return new BoolValue(v1.floatValue() > v2.floatValue()); // > 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.GE))
                    return new BoolValue(v1.floatValue() >= v2.floatValue()); // >= 연산을 수행하고 값 리턴
            }
        } else if (op.BooleanOp()) // Boolean op인 경우
        {
            if (v1.type() == Type.BOOL) // operand의 type이 bool일때
            {
                if (op.val.equals(Operator.AND))
                    return new BoolValue(v1.boolValue() && v2.boolValue()); // && 연산을 수행하고 값 리턴
                if (op.val.equals(Operator.OR))
                    return new BoolValue(v1.boolValue() || v2.boolValue()); // || 연산을 수행하고 값 리턴
            }
        }
        throw new IllegalArgumentException("should never reach here");
    }

    Value applyUnary(Operator op, Value v) {
        if (op.val.equals(Operator.NOT) && v.type == Type.BOOL)
            return new BoolValue(!v.boolValue()); // operand의 type이 bool이고 ! 연산일 경우, 연산 후 값 리턴
        else if (op.val.equals(Operator.NEG) && v.type == Type.INT)
            return new IntValue(-v.intValue()); // operand의 type이 int이고 - 연산일 경우, 연산 후 값 리턴
        else if (op.val.equals(Operator.NEG) && v.type == Type.FLOAT)
            return new FloatValue(-v.floatValue()); // operand의 type이 float이고 - 연산일 경우, 연산 후 값 리턴
        else if (op.val.equals(Operator.FLOAT) && v.type == Type.INT)
            return new FloatValue((float) (v.intValue())); // operand의 type이 int이고 int to float 연산일 경우, 형 변환 후 값 리턴
        else if (op.val.equals(Operator.INT) && v.type == Type.FLOAT)
            return new IntValue((int) (v.floatValue())); // operand의 type이 float이고 float to int 연산일 경우, 형 변환 후 값 리턴
        else if (op.val.equals(Operator.INT) && v.type == Type.CHAR)
            return new IntValue((int) (v.charValue())); // operand의 type이 char이고 char to int 연산일 경우, 형 변환 후 값 리턴
        else if (op.val.equals(Operator.CHAR) && v.type == Type.INT)
            return new CharValue((char) (v.intValue())); // operand의 type이 int이고 int to char 연산일 경우, 형 변환 후 값 리턴
        throw new IllegalArgumentException("should never reach here");
    }

    Value M(Expression e, State sigma) {
        if (e instanceof Value)
            return (Value) e; // value인 경우 value값 리턴
        if (e instanceof Variable) {
            StaticTypeCheck.check(sigma.containsKey(e),
                    "reference to undefined variable"); // state에 variable이 없는지 확인하고, 없으면 오류메세지 출력
            return (Value) (sigma.get(e)); // variable의 값 출력
        }
        if (e instanceof Binary) {
            Binary b = (Binary) e;
            return applyBinary(b.op,
                    M(b.term1, sigma), M(b.term2, sigma)); // binary인 경우 두 operand의 meaning을 이용해 연산
        }
        if (e instanceof Unary) {
            Unary u = (Unary) e;
            return applyUnary(u.op, M(u.term, sigma)); // unary인 경우 operand의 meaning을 이용해 연산
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void main(String args[]) {
        Parser parser = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
        prog.display(); // parsing 후 program의 AST 출력
        DynamicTyping dynamic = new DynamicTyping();
        State state = dynamic.M(prog); // meaning 파악
        System.out.println("Final State");
        state.display(); // 최종 state 출력
    }
}
