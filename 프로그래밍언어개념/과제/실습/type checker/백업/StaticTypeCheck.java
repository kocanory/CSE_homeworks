// StaticTypeCheck.java

import java.util.*;

// Static type checking for Clite is defined by the functions 
// V and the auxiliary functions typing and typeOf.  These
// functions use the classes in the Abstract Syntax of Clite.

public class StaticTypeCheck {

    public static TypeMap typing(Declarations d) {
        TypeMap map = new TypeMap();
        for (Declaration di : d)
            map.put(di.v, di.t); // declarations에서 변수와 변수 타입을 hash map의 형태로 저장
        return map;
    }

    public static void check(boolean test, String msg) {
        if (test)
            return; // test가 true인 경우 함수 종료
        System.err.println(msg); // 오류 메세지를 출력
        System.exit(1); // 프로그램 종료
    }

    public static void V(Declarations d) {
        for (int i = 0; i < d.size() - 1; i++)
            for (int j = i + 1; j < d.size(); j++) {
                Declaration di = d.get(i); // i번째 declaration의 정보를 가져옴
                Declaration dj = d.get(j); // i번쨰 이후의 declaration의 정보를 가져옴
                check(!(di.v.equals(dj.v)), "duplicate declaration: " + dj.v); // 중복되는 declaration이 있는지 체크하고, 중복될 경우 오류
                                                                               // 메세지 출력
            }
    }

    public static void V(Program p) {
        V(p.decpart); // declaration 부분이 올바른지 확인
        V(p.body, typing(p.decpart)); // body 부분과 type map을 비교하여 올바른지 확인
    }

    public static Type typeOf(Expression e, TypeMap tm) {
        if (e instanceof Value)
            return ((Value) e).type; // expression이 value일 경우 value의 type을 리턴
        if (e instanceof Variable) {
            Variable v = (Variable) e;
            check(tm.containsKey(v), "undefined variable: " + v); // type map에 해당 variable이 존재하는지 확인하고, 만약 없으면 오류메세지 출력
            return (Type) tm.get(v); // type map에 해당 variable이 존재하면 variable의 type을 리턴
        }
        if (e instanceof Binary) {
            Binary b = (Binary) e; // 두 개의 operand의 type이 같음
            if (b.op.ArithmeticOp()) // operator가 arithmetic operator일 경우
                if (typeOf(b.term1, tm) == Type.FLOAT)
                    return (Type.FLOAT); // operand가 float일 경우 float 리턴
                else
                    return (Type.INT); // operand가 int일 경우 int 리턴
            if (b.op.RelationalOp() || b.op.BooleanOp()) // operator가 relational operator or boolean operator일 경우
                return (Type.BOOL); // bool 리턴
        }
        if (e instanceof Unary) {
            Unary u = (Unary) e;
            if (u.op.NotOp())
                return (Type.BOOL); // not operator일 경우 bool 리턴
            else if (u.op.NegateOp())
                return typeOf(u.term, tm); // negate operator일 경우 operand의 type 리턴(int or float)
            else if (u.op.intOp())
                return (Type.INT); // int 형변환 연산자일 경우 int 리턴
            else if (u.op.floatOp())
                return (Type.FLOAT); // float 형변환 연산자일 경우 float 리턴
            else if (u.op.charOp())
                return (Type.CHAR); // char 형변환 연산자일 경우 char 리턴
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void V(Expression e, TypeMap tm) {
        if (e instanceof Value)
            return; // expression이 value일 경우 함수 종료
        if (e instanceof Variable) { // expression이 variable일 경우
            Variable v = (Variable) e;
            check(tm.containsKey(v), "undeclared variable: " + v); // type map에 해당 variable이 있는지 확인하고, 만약 없으면 오류메세지 출력
            return; // 문제가 없다면 함수 종료
        }
        if (e instanceof Binary) {
            Binary b = (Binary) e;
            Type typ1 = typeOf(b.term1, tm); // term1 의 type 값 저장
            Type typ2 = typeOf(b.term2, tm); // term2 의 type 값 저장
            V(b.term1, tm); // term1 이 올바르게 정의되었는지 확인
            V(b.term2, tm); // term2 이 올바르게 정의되었는지 확인
            if (b.op.ArithmeticOp())
                check(typ1 == typ2 && (typ1 == Type.INT || typ1 == Type.FLOAT), "type error for " + b.op);
            // 두 operand의 type이 같고, 그 type이 int or float인지 확인하고, 만약 이를 만족하지 못하면 오류메세지 출력
            else if (b.op.RelationalOp())
                check(typ1 == typ2, "type error for " + b.op);
            // 두 operand의 type이 같은지 확인하고, 만약 이를 만족하지 못하면 오류메세지 출력
            else if (b.op.BooleanOp())
                check(typ1 == Type.BOOL && typ2 == Type.BOOL, b.op + ": non-bool operand");
            // 두 operand의 type이 bool인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            else
                throw new IllegalArgumentException("should never reach here");
            return;
        }
        if (e instanceof Unary) {
            Unary u = (Unary) e;
            Type typ = typeOf(u.term, tm); // term의 type 값 저장
            V(u.term, tm); // term이 올바르게 정의되었는지 확인
            if (u.op.NotOp())
                check(typ == Type.BOOL, "type error for " + u.op);
            // operand의 type이 bool인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            else if (u.op.NegateOp())
                check((typ == Type.INT || typ == Type.FLOAT), "type error for " + u.op);
            // operand의 type이 int or float인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            else if (u.op.floatOp())
                check(typ == Type.INT, "type error for " + u.op);
            // operand의 type이 int인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            else if (u.op.charOp())
                check(typ == Type.INT, "type error for " + u.op);
            // operand의 type이 int인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            else if (u.op.intOp())
                check((typ == Type.CHAR || typ == Type.FLOAT), "type error for " + u.op);
            // operand의 type이 char or float인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            else
                throw new IllegalArgumentException("should never reach here");
            return;
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void V(Statement s, TypeMap tm) {
        if (s == null)
            throw new IllegalArgumentException("AST error: null statement");
        if (s instanceof Skip)
            return; // skip인 경우 함수 종료
        if (s instanceof Assignment) {
            Assignment a = (Assignment) s;
            check(tm.containsKey(a.target), "undefined target in assignment: " + a.target); // target이 올바른지 확인하고, 이를
                                                                                            // 만족하지 못하면 오류메세지 출력
            V(a.source, tm); // source가 올바른지 확인
            Type ttype = (Type) tm.get(a.target); // target의 type값 저장
            Type srctype = typeOf(a.source, tm); // source의 type값 저장
            if (ttype != srctype) { // target과 source의 type이 다른 경우
                if (ttype == Type.FLOAT) // target의 type이 float인 경우
                    check(srctype == Type.INT, "mixed mode assignment to " + a.target); // source의 type이 int인지 확인하고, 이를
                                                                                        // 만족하지 못하면 오류메세지 출력
                else if (ttype == Type.INT) // target의 type이 int인 경우
                    check(srctype == Type.CHAR, "mixed mode assignment to " + a.target); // source의 type이 char인지 확인하고,
                                                                                         // 이를 만족하지 못하면 오류메세지 출력
                else
                    check(false, "mixed mode assignment to " + a.target); // 저 두 가지 경우 외에는 전부 오류메세지 출력
            }
            return;
        }

        if (s instanceof Conditional) {
            Conditional c = (Conditional) s;
            V(c.test, tm); // test가 올바른지 확인
            Type typ = typeOf(c.test, tm); // test의 type값 저장
            check(typ == Type.BOOL, "test is not boolean type"); // test의 type이 bool인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            V(c.thenbranch, tm); // thenbranch가 올바른지 확인
            V(c.elsebranch, tm); // elsebranch가 올바른지 확인
            return;
        }
        if (s instanceof Loop) {
            Loop l = (Loop) s;
            V(l.test, tm); // test가 올바른지 확인
            Type typ = typeOf(l.test, tm); // test의 type값 저장
            check(typ == Type.BOOL, "test is not boolean type"); // test의 type이 bool인지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            V(l.body, tm); // body가 올바른지 확인
            return;
        }
        if (s instanceof Block) {
            Block b = (Block) s;
            for (Statement state : b.members)
                V(state, tm); // block을 구성하고 있는 모든 statement에 대하여 올바른지 확인
            return;
        }
        throw new IllegalArgumentException("should never reach here");
    }

    public static void main(String args[]) {
        System.out.println("\nBegin Begin parsing... programs/" + args[0]);
        Parser parser = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
        prog.display(); // parser의 결과 화면 출력
        System.out.println("\nBegin type checking... programs/" + args[0]);
        System.out.println("Type map:");
        TypeMap map = typing(prog.decpart);
        map.display(); // declarations에서 정의된 <변수, 변수형> 정보를 출력
        V(prog); // 프로그램이 올바른지 확인
    } // main

} // class StaticTypeCheck
