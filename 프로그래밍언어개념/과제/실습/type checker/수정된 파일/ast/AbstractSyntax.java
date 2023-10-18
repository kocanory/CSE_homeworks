// Abstract syntax for the language C++Lite,
// exactly as it appears in Appendix B.

import java.util.*;

class Program {
    // Program = Declarations decpart ; Block body
    Declarations decpart;
    Block body;

    Program (Declarations d, Block b) {
        decpart = d;
        body = b;
    } //Program constructor
    public Declarations decs(){ return decpart; } //return decpart
    public Block bd(){ return body; } //return body
    
    void display() {
        System.out.println("Program (abstract syntax): ");
        decs().display(1); //show decpart;
        bd().display(1); //show body;
    }
}

class Declarations extends ArrayList<Declaration> {
    // Declarations = Declaration*
    // (a list of declarations d1, d2, ..., dn)
    public void display(int indent)
    {
        int index = 0, size = this.size();
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Declarations:");
        for(int i = 0; i < indent + 1; i++)
            System.out.print("  "); //represent precedence
        System.out.print("Declarations = ");

        for(Declaration d: this)
            {
                System.out.print("<" + d.v + ", " + d.t + ">");
                if(index < size - 1)
                {
                    System.out.print(", "); // show declations
                    index++;
                }
            }
        System.out.println("");
    }

}

class Declaration {
// Declaration = Variable v; Type t
    Variable v;
    Type t;

    Declaration (Variable var, Type type) {
        v = var; t = type;
    } // declaration constructor

}

class Type {
    // Type = int | bool | char | float 
    final static Type INT = new Type("int");
    final static Type BOOL = new Type("bool");
    final static Type CHAR = new Type("char");
    final static Type FLOAT = new Type("float");
    // final static Type UNDEFINED = new Type("undef");
    
    private String id;

    private Type (String t) { id = t; } //Type constructor

    public String toString ( ) { return id; } //return id
}

abstract class Statement {
    // Statement = Skip | Block | Assignment | Conditional | Loop
    public abstract void display(int indent); //function declaration

}

class Skip extends Statement {
    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Skip:");
    }
}

class Block extends Statement {
    // Block = Statement*
    //         (a Vector of members)
    ArrayList<Statement> members;
    Block()
    {
        members  = new ArrayList<Statement>(); //Block constructor
    }
    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Block:");
        for(Statement s : members)
            s.display(indent + 1); //show Block
    }

}

class Assignment extends Statement {
    // Assignment = Variable target; Expression source
    Variable target;
    Expression source;

    Assignment (Variable t, Expression e) {
        target = t;
        source = e;
    } //Assignment constructor

    public Variable target(){ return target; } //return target
    public Expression source(){ return source; } //return source

    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Assignment:");
        for(int i = 0; i < indent + 1; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Variable: " + target().toString()); //show variable
        source().display(indent + 1); //show source
    }
}

class Conditional extends Statement {
// Conditional = Expression test; Statement thenbranch, elsebranch
    Expression test;
    Statement thenbranch, elsebranch;
    // elsebranch == null means "if... then"
    
    Conditional (Expression t, Statement tp) {
        test = t; thenbranch = tp; elsebranch = new Skip( );
    } //Conditional constructor - not exist elsebranch
    
    Conditional (Expression t, Statement tp, Statement ep) {
        test = t; thenbranch = tp; elsebranch = ep;
    } //Conditional constructor - exist elsebranch
    public Expression test(){ return test; } //return test
    public Statement thenbranch(){ return thenbranch; } //return thenbranch
    public Statement elsebranch(){ return elsebranch; } //return elsebranch

    public void display(int indent)
    {
        for(int i = 0;i < indent;i++)
            System.out.print("  "); //represent precedence
        System.out.println("Conditional:");
        test().display(indent + 1); //show test
        thenbranch().display(indent + 1); //show thenbranch
        if(!(elsebranch instanceof Skip)){
            elsebranch().display(indent + 1); //if elsebranch exists, show elsebranch
        }
        
    }

}

class Loop extends Statement {
// Loop = Expression test; Statement body
    Expression test;
    Statement body;

    Loop (Expression t, Statement b) {
        test = t; body = b;
    } //Loop constructor
    
    public Expression test(){ return test; } //return test
    public Statement body(){ return body; } //return body;

    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Loop:");
        test().display(indent + 1); //show test
        body().display(indent + 1); //show body
    }
}

abstract class Expression {
    // Expression = Variable | Value | Binary | Unary
    public abstract void display(int indent); //function declaration
}

class Variable extends Expression {
    // Variable = String id
    private String id;

    Variable (String s) { id = s; } //Variable constructor

    public String toString( ) { return id; } //return id
    
    public boolean equals (Object obj) {
        String s = ((Variable) obj).id;
        return id.equals(s); // case-sensitive identifiers
    }
    
    public int hashCode ( ) { return id.hashCode( ); }
    public void display(int indent)
    {
        for(int i = 0;i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Variable: " + id); //show Variable
    }

}

abstract class Value extends Expression {
    // Value = IntValue | BoolValue |
    //         CharValue | FloatValue
    protected Type type;
    protected boolean undef = true;

    int intValue ( ) {
        assert false : "should never reach here";
        return 0;
    }
    
    boolean boolValue ( ) {
        assert false : "should never reach here";
        return false;
    }
    
    char charValue ( ) {
        assert false : "should never reach here";
        return ' ';
    }
    
    float floatValue ( ) {
        assert false : "should never reach here";
        return 0.0f;
    }

    boolean isUndef( ) { return undef; }

    Type type ( ) { return type; }

    static Value mkValue (Type type) {
        if (type == Type.INT) return new IntValue( );
        if (type == Type.BOOL) return new BoolValue( );
        if (type == Type.CHAR) return new CharValue( );
        if (type == Type.FLOAT) return new FloatValue( );
        throw new IllegalArgumentException("Illegal type in mkValue");
    } //make value
}

class IntValue extends Value {
    private int value = 0;

    IntValue ( ) { type = Type.INT; } //IntValue constructor - not exist value

    IntValue (int v) { this( ); value = v; undef = false; } //Intvalue constructor - exist value

    int intValue ( ) {
        assert !undef : "reference to undefined int value";
        return value; //return value
    }

    public String toString( ) {
        if (undef)  return "undef";
        return "" + value; //int to string
    }
    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("IntValue: " + value); //show IntValue
    }
}

class BoolValue extends Value {
    private boolean value = false;

    BoolValue ( ) { type = Type.BOOL; } //Boolvalue constructor - not exist value

    BoolValue (boolean v) { this( ); value = v; undef = false; } //BoolValue constructor - exist value

    boolean boolValue ( ) {
        assert !undef : "reference to undefined bool value";
        return value; //return value
    }

    int intValue ( ) {
        assert !undef : "reference to undefined bool value";
        return value ? 1 : 0; //return value(bool to int)
    }

    public String toString( ) {
        if (undef)  return "undef";
        return "" + value; //bool to string
    }
    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("BoolValue: " + value); //show BoolValue
    }
}

class CharValue extends Value {
    private char value = ' ';

    CharValue ( ) { type = Type.CHAR; } //CharValue constructor - not exist value

    CharValue (char v) { this( ); value = v; undef = false; } //CharValue constructor value

    char charValue ( ) {
        assert !undef : "reference to undefined char value";
        return value;
    } //return value

    public String toString( ) {
        if (undef)  return "undef";
        return "" + value;
    } //char to string
    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("CharValue: " + value); //show CharValue
    }
}

class FloatValue extends Value {
    private float value = 0;

    FloatValue ( ) { type = Type.FLOAT; } //FloatValue constructor - not exist value

    FloatValue (float v) { this( ); value = v; undef = false; }  //FloatValue constructor - exist value

    float floatValue ( ) {
        assert !undef : "reference to undefined float value";
        return value;
    } //return value;

    public String toString( ) {
        if (undef)  return "undef";
        return "" + value;
    }//float to string
    public void display(int indent)
    {
        for(int i = 0; i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("FloatValue: " + value); //show FloatValue
    }
}

class Binary extends Expression {
// Binary = Operator op; Expression term1, term2
    Operator op;
    Expression term1, term2;

    Binary (Operator o, Expression l, Expression r) {
        op = o; term1 = l; term2 = r;
    } // Binary constructor 
    public void display(int indent)
    {
        for(int i = 0;i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Binary: ");
        for(int i = 0;i < indent + 1; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Operator: " + op.val); //show opeartor
        term1.display(indent + 1); //show term1
        term2.display(indent + 1); //show term2
    }
}

class Unary extends Expression {
    // Unary = Operator op; Expression term
    Operator op;
    Expression term;

    Unary (Operator o, Expression e) {
        op = o; term = e;
    } // Unary constructor

    public void display(int indent)
    {
        for(int i = 0;i < indent; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Unary: ");
        for(int i = 0;i < indent + 1; i++)
            System.out.print("  "); //represent precedence
        System.out.println("Operator: " + op.val); //show operator
        term.display(indent + 1); //show term
    }
}

class Operator {
    // Operator = BooleanOp | RelationalOp | ArithmeticOp | UnaryOp
    // BooleanOp = && | ||
    final static String AND = "&&";
    final static String OR = "||";
    // RelationalOp = < | <= | == | != | >= | >
    final static String LT = "<";
    final static String LE = "<=";
    final static String EQ = "==";
    final static String NE = "!=";
    final static String GT = ">";
    final static String GE = ">=";
    // ArithmeticOp = + | - | * | /
    final static String PLUS = "+";
    final static String MINUS = "-";
    final static String TIMES = "*";
    final static String DIV = "/";
    // UnaryOp = !    
    final static String NOT = "!";
    final static String NEG = "-";
    // CastOp = int | float | char
    final static String INT = "int";
    final static String FLOAT = "float";
    final static String CHAR = "char";
    // Typed Operators
    // RelationalOp = < | <= | == | != | >= | >
    final static String INT_LT = "INT<";
    final static String INT_LE = "INT<=";
    final static String INT_EQ = "INT==";
    final static String INT_NE = "INT!=";
    final static String INT_GT = "INT>";
    final static String INT_GE = "INT>=";
    // ArithmeticOp = + | - | * | /
    final static String INT_PLUS = "INT+";
    final static String INT_MINUS = "INT-";
    final static String INT_TIMES = "INT*";
    final static String INT_DIV = "INT/";
    // UnaryOp = !    
    final static String INT_NEG = "-";
    // RelationalOp = < | <= | == | != | >= | >
    final static String FLOAT_LT = "FLOAT<";
    final static String FLOAT_LE = "FLOAT<=";
    final static String FLOAT_EQ = "FLOAT==";
    final static String FLOAT_NE = "FLOAT!=";
    final static String FLOAT_GT = "FLOAT>";
    final static String FLOAT_GE = "FLOAT>=";
    // ArithmeticOp = + | - | * | /
    final static String FLOAT_PLUS = "FLOAT+";
    final static String FLOAT_MINUS = "FLOAT-";
    final static String FLOAT_TIMES = "FLOAT*";
    final static String FLOAT_DIV = "FLOAT/";
    // UnaryOp = !    
    final static String FLOAT_NEG = "-";
    // RelationalOp = < | <= | == | != | >= | >
    final static String CHAR_LT = "CHAR<";
    final static String CHAR_LE = "CHAR<=";
    final static String CHAR_EQ = "CHAR==";
    final static String CHAR_NE = "CHAR!=";
    final static String CHAR_GT = "CHAR>";
    final static String CHAR_GE = "CHAR>=";
    // RelationalOp = < | <= | == | != | >= | >
    final static String BOOL_LT = "BOOL<";
    final static String BOOL_LE = "BOOL<=";
    final static String BOOL_EQ = "BOOL==";
    final static String BOOL_NE = "BOOL!=";
    final static String BOOL_GT = "BOOL>";
    final static String BOOL_GE = "BOOL>=";
    // Type specific cast
    final static String I2F = "I2F";
    final static String F2I = "F2I";
    final static String C2I = "C2I";
    final static String I2C = "I2C";
    
    String val;
    
    Operator (String s) { val = s; } //Operator constructor

    public String toString( ) { return val; } //return val
    public boolean equals(Object obj) { return val.equals(obj); } //check eqaulity val and obj
    
    boolean BooleanOp ( ) { return val.equals(AND) || val.equals(OR); }  //check operator && ||
    boolean RelationalOp ( ) {
        return val.equals(LT) || val.equals(LE) || val.equals(EQ) //check operator < <= =
            || val.equals(NE) || val.equals(GT) || val.equals(GE); //check operator != > >= 
    }
    boolean ArithmeticOp ( ) {
        return val.equals(PLUS) || val.equals(MINUS) //check operator + -
            || val.equals(TIMES) || val.equals(DIV); //check operator * /
    }
    boolean NotOp ( ) { return val.equals(NOT) ; } //check operator !
    boolean NegateOp ( ) { return val.equals(NEG) ; } //check operator -
    boolean intOp ( ) { return val.equals(INT); } //check type operator int
    boolean floatOp ( ) { return val.equals(FLOAT); } //check type operator float
    boolean charOp ( ) { return val.equals(CHAR); } //check type operator char

    final static String intMap[ ] [ ] = {
        {PLUS, INT_PLUS}, {MINUS, INT_MINUS},
        {TIMES, INT_TIMES}, {DIV, INT_DIV},
        {EQ, INT_EQ}, {NE, INT_NE}, {LT, INT_LT},
        {LE, INT_LE}, {GT, INT_GT}, {GE, INT_GE},
        {NEG, INT_NEG}, {FLOAT, I2F}, {CHAR, I2C}
    }; //int operation

    final static String floatMap[ ] [ ] = {
        {PLUS, FLOAT_PLUS}, {MINUS, FLOAT_MINUS},
        {TIMES, FLOAT_TIMES}, {DIV, FLOAT_DIV},
        {EQ, FLOAT_EQ}, {NE, FLOAT_NE}, {LT, FLOAT_LT},
        {LE, FLOAT_LE}, {GT, FLOAT_GT}, {GE, FLOAT_GE},
        {NEG, FLOAT_NEG}, {INT, F2I}
    }; //float operation

    final static String charMap[ ] [ ] = {
        {EQ, CHAR_EQ}, {NE, CHAR_NE}, {LT, CHAR_LT},
        {LE, CHAR_LE}, {GT, CHAR_GT}, {GE, CHAR_GE},
        {INT, C2I}
    }; //char operation

    final static String boolMap[ ] [ ] = {
        {EQ, BOOL_EQ}, {NE, BOOL_NE}, {LT, BOOL_LT},
        {LE, BOOL_LE}, {GT, BOOL_GT}, {GE, BOOL_GE},
    }; //bool operation

    final static private Operator map (String[][] tmap, String op) {
        for (int i = 0; i < tmap.length; i++)
            if (tmap[i][0].equals(op))
                return new Operator(tmap[i][1]);
        assert false : "should never reach here";
        return null;
    } //return proper operation

    final static public Operator intMap (String op) {
        return map (intMap, op);
    } //return int operation map

    final static public Operator floatMap (String op) {
        return map (floatMap, op);
    } //return float operation map

    final static public Operator charMap (String op) {
        return map (charMap, op);
    } //return char operation map

    final static public Operator boolMap (String op) {
        return map (boolMap, op);
    } //return bool operation map
}
