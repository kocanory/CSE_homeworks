import java.util.ArrayList;
import java.util.Stack;

public class Semantics {

    Stack<Function> callStack;

    State M(Program p) {
        Variable main = new Variable("main");
        ArrayList<Value> params = new ArrayList<Value>();
        callStack = new Stack<Function>();
        return M(p.functions, main, initialState(p.globals), params); // initial state과 parameters로 function과 main의
                                                                      // meaning 파악
    }

    State M(Functions fs, Variable call, State globals, ArrayList<Value> params) {
        for (int i = 0; i < fs.members.size(); i++) {
            if (fs.members.get(i).name.toString().equals(call.toString())) {// functions에서 call function을 찾은 경우
                State locals = new State();
                Function f = new Function(fs.members.get(i).name, fs.members.get(i).type, fs.members.get(i).params,
                        fs.members.get(i).locals, fs.members.get(i).body);
                callStack.push(f); // function을 stack에 push
                for (int j = 0; j < f.params.size(); j++)
                    locals.put(f.params.get(j).v, params.get(j));// parameter 저장
                locals.putAll(initialState(f.locals));// local variable 저장
                if (call.toString().equals("main")) { // call 된 함수가 main 함수인 경우
                    System.out.println("Entering " + call.toString() + " :");
                    System.out.println("  Globals and top frame:\n  ----------");
                    globals.display(); // global variable 출력
                    locals.display();// local variable 출력
                    System.out.println("  ----------");
                } else { // call된 함수가 외부에 선언된 함수인 경우
                    System.out.println("Calling " + call.toString() + " :");
                    System.out.println("  Globals and top frame:\n  ----------");
                    globals.display();// global variable 출력
                    locals.display();// local variable 출력
                    System.out.println("  <" + f.name + ", " + f.val + ">");// function name, value 출력
                    System.out.println("  ----------");
                }
                M(fs, f.body, globals, locals); // function body의 meaning check
                if (call.toString().equals("main")) { // call 된 함수가 main 함수인 경우
                    System.out.println("Leaving " + call.toString() + " :");
                    System.out.println("  Globals and top frame:\n  ----------");
                    globals.display();// global variable 출력
                    locals.display();// local variable 출력
                    System.out.println("  ----------");
                } else { // call된 함수가 외부에 선언된 함수인 경우
                    System.out.println("Returning " + call.toString() + " :");
                    System.out.println("  Globals and top frame:\n  ----------");
                    globals.display();// global variable 출력
                    locals.display();// local variable 출력
                    System.out.println("  <" + f.name + ", " + f.val + ">");// function name, value 출력
                    System.out.println("  ----------");
                }
                callStack.pop();
                break;
            }
        }
        return globals;
    }

    State initialState(Declarations d) {
        State state = new State();
        Value intUndef = new IntValue();
        for (Declaration decl : d)
            state.put(decl.v, Value.mkValue(decl.t)); // decpart에 정의된 변수를 state에 입력
        return state;
    }

    State M(Functions fs, Statement s, State globals, State locals) {
        if (s instanceof Skip) // statement가 skip인 경우
            return M(fs, (Skip) s, globals, locals);
        if (s instanceof Assignment) // statement가 assignment인 경우
            return M(fs, (Assignment) s, globals, locals);
        if (s instanceof Conditional) // statement가 conditional인 경우
            return M(fs, (Conditional) s, globals, locals);
        if (s instanceof Loop) // statement가 loop인 경우
            return M(fs, (Loop) s, globals, locals);
        if (s instanceof Block) // statement가 block인 경우
            return M(fs, (Block) s, globals, locals);
        if (s instanceof Call) {// statement가 Call인 경우
            ArrayList<Value> params = new ArrayList<Value>();
            for (int i = 0; i < ((Call) s).params.size(); i++)
                params.add(M(fs, ((Call) s).params.get(i), globals, locals));
            return M(fs, ((Call) s).name, globals, params);
        }
        if (s instanceof Return)// statement가 Return인 경우
            return M(fs, (Return) s, globals, locals);
        throw new IllegalArgumentException("should never reach here");
    }

    State M(Functions fs, Skip s, State globals, State locals) {
        return locals; // local variable의 state가 변하지 않음
    }

    State M(Functions fs, Assignment a, State globals, State locals) {
        if (locals.containsKey(a.target))
            return locals.onion(a.target, M(fs, a.source, globals, locals)); // 변경된 local variable state를 업데이트
        else
            return globals.onion(a.target, M(fs, a.source, globals, locals)); // 변경된 global variable state를 업데이트
    }

    State M(Functions fs, Block b, State globals, State locals) {
        State state = new State();
        for (Statement s : b.members)
            state = M(fs, s, globals, locals); // block 안의 모든 statement에 대하여 meaning 파악
        return state;
    }

    State M(Functions fs, Conditional c, State globals, State locals) {
        if (M(fs, c.test, globals, locals).boolValue()) // test가 true일 경우
            return M(fs, c.thenbranch, globals, locals); // thenbranch의 meaning 파악
        else // test가 false일 경우
            return M(fs, c.elsebranch, globals, locals); // elsebranch의 meaning 파악
    }

    State M(Functions fs, Loop l, State globals, State locals) {
        if (M(fs, l.test, globals, locals).boolValue()) // test가 true일 경우
            return M(fs, l, M(fs, l.body, globals, locals), locals); // body의 meaning 파악
        else
            return locals; // loop가 끝나면 바뀐 state를 리턴
    }

    State M(Functions fs, Return r, State globals, State locals) {
        callStack.get(callStack.size() - 1).val = M(fs, r.result, globals, locals); // call stack 최상단의 값을 변경
        return locals;
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
        if (op.val.equals(Operator.AND))
            return new BoolValue(v1.boolValue() && v2.boolValue());// 두 논리값에 and 연산을 취한뒤 true, false 리턴
        if (op.val.equals(Operator.OR))
            return new BoolValue(v1.boolValue() || v2.boolValue());// 두 논리값에 or 연산을 취한뒤 true, false 리턴

        if (op.val.equals(Operator.PLUS))
            return new IntValue(v1.intValue() + v2.intValue());// + 연산일 경우 정수형 + 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.MINUS))
            return new IntValue(v1.intValue() - v2.intValue());// - 연산일 경우 정수형 - 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.TIMES))
            return new IntValue(v1.intValue() * v2.intValue());// * 연산일 경우 정수형 * 연산 후에 나온 값 리턴
        if (op.val.equals(Operator.DIV))
            return new IntValue(v1.intValue() / v2.intValue());// / 연산일 경우 정수형 / 연산 후에 나온 값 리턴

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

    Value M(Functions fs, Expression e, State globals, State locals) {
        if (e instanceof Value)
            return (Value) e; // value인 경우 value값 리턴
        if (e instanceof Variable) {
            if (locals.containsKey(e))
                return (Value) (locals.get(e)); // local variable에 저장되어 있는 값 리턴
            else
                return (Value) (globals.get(e));// global variable에 저장되어 있는 값 리턴
        }
        if (e instanceof Binary) {
            Binary b = (Binary) e;
            return applyBinary(b.op,
                    M(fs, b.term1, globals, locals), M(fs, b.term2, globals, locals)); // binary인 경우 두 operand의 meaning을
                                                                                       // 이용하여 연산
        }
        if (e instanceof Unary) {
            Unary u = (Unary) e;
            return applyUnary(u.op, M(fs, u.term, globals, locals)); // unary인 경우 operand의 meaning을 이용하여 연산
        }
        if (e instanceof Call) {
            for (int i = 0; i < fs.members.size(); i++) {
                if (fs.members.get(i).name.equals(((Call) e).name)) {
                    ArrayList<Value> params = new ArrayList<Value>();
                    for (int j = 0; j < fs.members.get(i).params.size(); j++)
                        params.add(M(fs, ((Call) e).params.get(j), globals, locals));
                    return M2(fs, fs.members.get(i).name, globals, params);
                }
            }
        }
        throw new IllegalArgumentException("should never reach here");
    }

    Value M2(Functions fs, Variable call, State globals, ArrayList<Value> params) {
        Value result = null;
        for (int i = 0; i < fs.members.size(); i++) {
            if (fs.members.get(i).name.toString().equals(call.toString())) {// functions에서 call function을 찾은 경우
                State locals = new State();
                Function f = new Function(fs.members.get(i).name, fs.members.get(i).type, fs.members.get(i).params,
                        fs.members.get(i).locals, fs.members.get(i).body);
                callStack.push(f); // function을 stack에 push
                for (int j = 0; j < f.params.size(); j++)
                    locals.put(f.params.get(j).v, params.get(j));// parameter 저장
                locals.putAll(initialState(f.locals));// local variable 저장

                System.out.println("Calling " + call.toString() + " :");
                System.out.println("  Globals and top frame:\n  ----------");
                globals.display();// global variable 출력
                locals.display();// local variable 출력
                System.out.println("  <" + f.name + ", " + f.val + ">");// function name, value 출력
                System.out.println("  ----------");

                M(fs, f.body, globals, locals); // function body의 meaning check
                result = f.val;
                System.out.println("Returning " + call.toString() + " :");
                System.out.println("  Globals and top frame:\n  ----------");
                globals.display();// global variable 출력
                locals.display();// local variable 출력
                System.out.println("  <" + f.name + ", " + f.val + ">");// function name, value 출력
                System.out.println("  ----------");
                callStack.pop();
                break;
            }
        }
        return result;
    }

    public static void main(String args[]) {
        System.out.println("\nBegin parsing...programs/" + args[0] + "\n");
        Parser parser = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
        prog.display(); // parsing 후 program의 AST 출력
        System.out.println("\nBegin type checking...programs/" + args[0] + "\n");
        System.out.print("Globals = ");
        TypeMap map = StaticTypeCheck.typing(prog.globals);
        map.display(); // type map 출력
        StaticTypeCheck.V(prog); // type check 실행
        Program out = TypeTransformer.T(prog, map); // type 형변환 실행
        System.out.println("\nBegin interpreting...programs/" + args[0] + "\n");
        Semantics semantics = new Semantics();
        State state = semantics.M(out); // program의 meaning 파악
        System.out.println("\nFinal State");
        System.out.println("  Globals and top frame:\n  ----------");
        state.display(); // 최종 state 출력
        System.out.println("  ----------");
    }
}
