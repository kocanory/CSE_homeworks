public class TypeTransformer {

    public static Program T(Program p, TypeMap tm) {
        Functions functions = (Functions) T(p.functions, tm);
        return new Program(p.globals, functions);
    }

    public static Functions T(Functions fs, TypeMap gloabals) {
        Functions out = new Functions();
        for (int i = 0; i < fs.members.size(); i++) {
            TypeMap tm = new TypeMap();
            tm.putAll(gloabals); // Type map에 global variable 저장
            tm.putAll(StaticTypeCheck.typing(fs.members.get(i).params));// Type map에 parameter 저장
            tm.putAll(StaticTypeCheck.typing(fs.members.get(i).locals));// Type map에 local variable 저장
            for (int j = 0; j < fs.members.size(); j++) {
                tm.put(fs.members.get(j).name, fs.members.get(j).type);// Type map에 function name, type 저장
            }
            Function f = new Function(fs.members.get(i).name, fs.members.get(i).type, fs.members.get(i).params,
                    fs.members.get(i).locals, (Block) T(fs.members.get(i).body, tm));
            out.members.add(f); // functions에 function 추가
        }
        return out;
    }

    public static Expression T(Expression e, TypeMap tm) {
        if (e instanceof Value)
            return e; // expression이 value일 경우 expression e 리턴
        if (e instanceof Variable)
            return e; // expression이 variable일 경우 expression e 리턴
        if (e instanceof Binary) {
            Binary b = (Binary) e;
            Type typ1 = StaticTypeCheck.typeOf(b.term1, tm); // term1의 type 값 저장
            Type typ2 = StaticTypeCheck.typeOf(b.term2, tm); // term2의 type 값 저장
            Expression t1 = T(b.term1, tm);
            Expression t2 = T(b.term2, tm);
            if (typ1 == Type.INT)
                return new Binary(b.op.intMap(b.op.val), t1, t2); // term1의 type이 int일 경우, intmap을 이용하여 생성한 binary 리턴
            else if (typ1 == Type.FLOAT)
                return new Binary(b.op.floatMap(b.op.val), t1, t2); // term1의 type이 float 경우, floatmap을 이용하여 생성한 binary
                                                                    // 리턴
            else if (typ1 == Type.CHAR)
                return new Binary(b.op.charMap(b.op.val), t1, t2); // term1의 type이 char일 경우, charmap을 이용하여 생성한 binary 리턴
            else if (typ1 == Type.BOOL)
                return new Binary(b.op.boolMap(b.op.val), t1, t2); // term1의 type이 bool일 경우, bollmap을 이용하여 생성한 binary 리턴
            throw new IllegalArgumentException("should never reach here");
        }
        if (e instanceof Unary) {
            Unary u = (Unary) e;
            Type typ = StaticTypeCheck.typeOf(u.term, tm); // term의 type 값 저장
            Expression t = T(u.term, tm);
            if (typ == Type.INT)
                return new Unary(u.op.intMap(u.op.val), t); // term의 type이 int일 경우, intmap을 이용하여 생성한 unary 리턴
            else if (typ == Type.FLOAT)
                return new Unary(u.op.floatMap(u.op.val), t); // term의 type이 float일 경우, floatmap을 이용하여 생성한 unary 리턴
            else if (typ == Type.CHAR)
                return new Unary(u.op.charMap(u.op.val), t); // term의 type이 char일 경우, charmap을 이용하여 생성한 unary 리턴
            else if (typ == Type.BOOL)
                return new Unary(u.op.boolMap(u.op.val), t); // term의 type이 bool일 경우, boolmap을 이용하여 생성한 unary 리턴
            throw new IllegalArgumentException("should never reach here");
        }
        if (e instanceof Call)
            return e; // expression이 Call Expression일 경우 expression e 리턴
        throw new IllegalArgumentException("should never reach here");
    }

    public static Statement T(Statement s, TypeMap tm) {
        if (s instanceof Skip)
            return s; // skip일 경우 statement s 리턴
        if (s instanceof Assignment) {
            Assignment a = (Assignment) s;
            Variable target = a.target;
            Expression src = T(a.source, tm); // source transform
            Type ttype = (Type) tm.get(a.target); // target의 type 저장
            Type srctype = StaticTypeCheck.typeOf(a.source, tm); // source의 type 저장
            if (ttype == Type.FLOAT) { // target type = float
                if (srctype == Type.INT) { // source의 type이 int인 경우
                    src = new Unary(new Operator(Operator.I2F), src); // int to float
                    srctype = Type.FLOAT; // source type = float
                }
            } else if (ttype == Type.INT) { // target type = int
                if (srctype == Type.CHAR) { // source의 type이 char인 경우
                    src = new Unary(new Operator(Operator.C2I), src); // char to int
                    srctype = Type.INT; // source type = int
                }
            }
            StaticTypeCheck.check(ttype == srctype, "bug in assignment to " + target);
            // target 과 source의 type이 같은지 확인하고, 이를 만족하지 못하면 오류메세지 출력
            return new Assignment(target, src); // assignment 리턴
        }
        if (s instanceof Conditional) {
            Conditional c = (Conditional) s;
            Expression test = T(c.test, tm); // test transform
            Statement tbr = T(c.thenbranch, tm); // thenbranch transform
            Statement ebr = T(c.elsebranch, tm); // elsebranch transform
            return new Conditional(test, tbr, ebr); // conditional 리턴
        }
        if (s instanceof Loop) {
            Loop l = (Loop) s;
            Expression test = T(l.test, tm); // test transform
            Statement body = T(l.body, tm); // body transform
            return new Loop(test, body); // loop 리턴
        }
        if (s instanceof Block) {
            Block b = (Block) s;
            Block out = new Block();
            for (Statement stmt : b.members)
                out.members.add(T(stmt, tm)); // 모든 statement에 대해 type transform 한 후 block에 추가
            return out;
        }
        if (s instanceof Call)
            return s; // statement 그대로 리턴
        if (s instanceof Return)
            return (Return) s;// Return Statement로 형변환하여 리턴
        throw new IllegalArgumentException("should never reach here");
    }

    public static void main(String args[]) {
        System.out.println("\nBegin Begin parsing... programs/" + args[0]);
        Parser parser = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
        prog.display(); // parser의 결과 화면 출력
        System.out.println("\nBegin type checking... programs/" + args[0]);
        System.out.println("Globals:");
        TypeMap map = StaticTypeCheck.typing(prog.globals);
        map.display(); // declarations에서 정의된 <변수, 변수형> 정보를 출력
        StaticTypeCheck.V(prog); // 프로그램이 올바른지 확인
        Program out = T(prog, map);
        System.out.println("Transformed Abstract Syntax Tree\n");
        out.display(); // type transformed된 AST 결과 화면 출력
    } // main

} // class TypeTransformer
