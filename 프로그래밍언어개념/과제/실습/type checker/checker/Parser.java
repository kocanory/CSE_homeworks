import java.util.*;

public class Parser {
    // Recursive descent parser that inputs a C++Lite program and
    // generates its abstract syntax. Each method corresponds to
    // a concrete syntax grammar rule, which appears as a comment
    // at the beginning of the method.

    Token token; // current token from the input stream
    Lexer lexer;

    public Parser(Lexer ts) { // Open the C++Lite source program
        lexer = ts; // as a token stream, and
        token = lexer.next(); // retrieve its first Token
    }

    private String match(TokenType t) {
        String value = token.value();
        if (token.type().equals(t))
            token = lexer.next(); // if tokentype equals t, save next token
        else
            error(t);
        return value; // return token
    }

    private void error(TokenType tok) {
        System.err.println("Syntax error: expecting: " + tok + "; saw: " + token);
        System.exit(1); // send error message and shut down program
    }

    private void error(String tok) {
        System.err.println("Syntax error: expecting: " + tok + "; saw: " + token);
        System.exit(1); // send error message and shut down program
    }

    public Program program() {
        // Program --> void main ( ) '{' Declarations Statements '}'
        TokenType[] header = { TokenType.Int, TokenType.Main, TokenType.LeftParen, TokenType.RightParen };
        for (int i = 0; i < header.length; i++) // bypass "int main ( )"
            match(header[i]);
        match(TokenType.LeftBrace); // check leftbrace
        Declarations decs = declarations(); // Declarations decpart
        Block b = progstatements();// Block body
        match(TokenType.RightBrace); // check rightbrace
        return new Program(decs, b); // return Program
    }

    private Declarations declarations() {
        // Declarations --> { Declaration }
        Declarations ds = new Declarations();
        while (isType()) {
            declaration(ds); // save declarations
        }
        return ds;
    }

    private void declaration(Declarations ds) {
        // Declaration --> Type Identifier { , Identifier } ;
        Variable v;
        Declaration d;
        Type t = type();
        v = new Variable(match(TokenType.Identifier)); // check and save variable
        d = new Declaration(v, t); // make declaration
        ds.add(d); // save to declarations
        while (token.type().equals(TokenType.Comma)) {
            token = lexer.next();
            v = new Variable(match(TokenType.Identifier));
            d = new Declaration(v, t);
            ds.add(d); // if additional declaration exists, save to declarations
        }
        match(TokenType.Semicolon); // check statement terminator
    }

    private Type type() {
        // Type --> int | bool | float | char
        Type t = null;
        if (token.type().equals(TokenType.Int)) {
            t = Type.INT;
        } else if (token.type().equals(TokenType.Float)) {
            t = Type.FLOAT;
        } else if (token.type().equals(TokenType.Char)) {
            t = Type.CHAR;
        } else if (token.type().equals(TokenType.Bool)) {
            t = Type.BOOL;
        } else {
            error("Error in Type construction");
        }
        token = lexer.next();
        return t;
    }

    private Statement statement() {
        // Statement --> ; | Block | Assignment | IfStatement | WhileStatement
        Statement s = null;
        if (token.type().equals(TokenType.Semicolon)) {
            match(TokenType.Semicolon);
            s = new Skip();
        } else if (token.type().equals(TokenType.LeftBrace))
            s = statements();
        else if (token.type().equals(TokenType.If))
            s = ifStatement();
        else if (token.type().equals(TokenType.While))
            s = whileStatement();
        else if (token.type().equals(TokenType.Identifier))
            s = assignment();
        else
            error("Error in Statement construction");

        return s;
    }

    private Block statements() {
        // Block --> '{' Statements '}'
        Block b = new Block();
        Statement s;
        match(TokenType.LeftBrace); // check '{'
        while (isStatement()) {
            s = statement();
            b.members.add(s); // save to block
        }
        match(TokenType.RightBrace); // check '}'
        return b; // return block
    }

    private Block progstatements() // program --> Declarations decpart | 'Statements' body
    {
        Block b = new Block();
        Statement s;
        while (isStatement()) {
            s = statement();
            b.members.add(s); // save to block
        }
        return b; // return block
    }

    private Assignment assignment() {
        // Assignment --> Identifier = Expression ;
        Expression source;
        Variable target;

        target = new Variable(match(TokenType.Identifier)); // check and save identifier
        match(TokenType.Assign); // check '='
        source = expression(); // save source
        match(TokenType.Semicolon); // check statement terminator
        return new Assignment(target, source); // return assignment
    }

    private Conditional ifStatement() {
        // IfStatement --> if ( Expression ) Statement [ else Statement ]
        Conditional con;
        Statement s;
        Expression test;

        match(TokenType.If); // check 'if'
        match(TokenType.LeftParen); // check '('
        test = expression(); // save test
        match(TokenType.RightParen); // check ')'
        s = statement(); // save statement
        if (token.type().equals(TokenType.Else)) {
            Statement elsestate = statement();
            con = new Conditional(test, s, elsestate);
        } // if 'else' exists, save else statement
        else {
            con = new Conditional(test, s);
        }
        return con; // return conditional
    }

    private Loop whileStatement() {
        // WhileStatement --> while ( Expression ) Statement
        Expression test;
        Statement body;

        match(TokenType.While); // check 'while'
        match(TokenType.LeftParen); // check '('
        test = expression(); // save test
        match(TokenType.RightParen); // check ')'
        body = statement(); // save body
        return new Loop(test, body); // return loop
    }

    private Expression expression() {
        // Expression --> Conjunction { || Conjunction }
        Expression e = conjunction();
        while (token.type().equals(TokenType.Or)) { // check '||'
            Operator op = new Operator(match(token.type()));
            Expression term2 = conjunction();
            e = new Binary(op, e, term2);
        }
        return e;
    }

    private Expression conjunction() {
        // Conjunction --> Equality { && Equality }
        Expression e = equality();
        while (token.type().equals(TokenType.And)) { // check '&&'
            Operator op = new Operator(match(token.type()));
            Expression term2 = equality();
            e = new Binary(op, e, term2);
        }
        return e;
    }

    private Expression equality() {
        // Equality --> Relation [ EquOp Relation ]
        Expression e = relation();
        if (isEqualityOp()) {
            Operator op = new Operator(match(token.type())); // check '==' '!='
            Expression term2 = relation();
            e = new Binary(op, e, term2);
        }
        return e;
    }

    private Expression relation() {
        // Relation --> Addition [RelOp Addition]
        Expression e = addition();
        if (isRelationalOp()) {
            Operator op = new Operator(match(token.type())); // check '<' '<=' '>' '>='
            Expression term2 = addition();
            e = new Binary(op, e, term2);
        }
        return e;
    }

    private Expression addition() {
        // Addition --> Term { AddOp Term }
        Expression e = term();
        while (isAddOp()) {
            Operator op = new Operator(match(token.type())); // check '+' '-'
            Expression term2 = term();
            e = new Binary(op, e, term2);
        }
        return e;
    }

    private Expression term() {
        // Term --> Factor { MultiplyOp Factor }
        Expression e = factor();
        while (isMultiplyOp()) {
            Operator op = new Operator(match(token.type())); // check '*' '/'
            Expression term2 = factor();
            e = new Binary(op, e, term2);
        }
        return e;
    }

    private Expression factor() {
        // Factor --> [ UnaryOp ] Primary
        if (isUnaryOp()) {
            Operator op = new Operator(match(token.type())); // check '-' '!'
            Expression term = primary();
            return new Unary(op, term);
        } else
            return primary();
    }

    private Expression primary() {
        // Primary --> Identifier | Literal | ( Expression )
        // | Type ( Expression )
        Expression e = null;
        if (token.type().equals(TokenType.Identifier)) { // check identifier
            e = new Variable(match(TokenType.Identifier));
        } else if (isLiteral()) { // check literal
            e = literal();
        } else if (token.type().equals(TokenType.LeftParen)) { // check (expression)
            token = lexer.next();
            e = expression();
            match(TokenType.RightParen);
        } else if (isType()) { // check type(expression)
            Operator op = new Operator(match(token.type()));
            match(TokenType.LeftParen);
            Expression term = expression();
            match(TokenType.RightParen);
            e = new Unary(op, term);
        } else
            error("Identifier | Literal | ( | Type");
        return e;
    }

    private Value literal() {

        Value val = null;
        if (token.type().equals(TokenType.IntLiteral)) // check integer value
        {
            val = new IntValue(Integer.parseInt(token.value()));
            token = lexer.next();
        } else if (token.type().equals(TokenType.FloatLiteral)) // check float value
        {
            val = new FloatValue(Float.parseFloat(token.value()));
            token = lexer.next();
        } else if (token.type().equals(TokenType.CharLiteral)) // check character value
        {
            val = new CharValue(token.value().charAt(0));
            token = lexer.next();
        } else if (token.type().equals(TokenType.True)) // check boolean true value
        {
            val = new BoolValue(true);
            token = lexer.next();
        } else if (token.type().equals(TokenType.False)) // check boolean false value
        {
            val = new BoolValue(false);
            token = lexer.next();
        } else {
            error("Error in literal value construction");
        }
        return val;
    }

    private boolean isAddOp() { // check add operater
        return token.type().equals(TokenType.Plus) || token.type().equals(TokenType.Minus);
    }

    private boolean isMultiplyOp() { // check multi operater
        return token.type().equals(TokenType.Multiply) || token.type().equals(TokenType.Divide);
    }

    private boolean isUnaryOp() { // check unary operater
        return token.type().equals(TokenType.Not) || token.type().equals(TokenType.Minus);
    }

    private boolean isEqualityOp() { // check equal operater
        return token.type().equals(TokenType.Equals) || token.type().equals(TokenType.NotEqual);
    }

    private boolean isRelationalOp() { // check relation operater
        return token.type().equals(TokenType.Less) || token.type().equals(TokenType.LessEqual)
                || token.type().equals(TokenType.Greater) || token.type().equals(TokenType.GreaterEqual);
    }

    private boolean isType() { // check type operater
        return token.type().equals(TokenType.Int) || token.type().equals(TokenType.Bool)
                || token.type().equals(TokenType.Float) || token.type().equals(TokenType.Char);
    }

    private boolean isLiteral() { // check literal
        return token.type().equals(TokenType.IntLiteral) || isBooleanLiteral()
                || token.type().equals(TokenType.FloatLiteral) || token.type().equals(TokenType.CharLiteral);
    }

    private boolean isBooleanLiteral() { // check boolean literal
        return token.type().equals(TokenType.True) || token.type().equals(TokenType.False);
    }

    private boolean isStatement() // check statement
    {
        return token.type().equals(TokenType.Semicolon) || token.type().equals(TokenType.LeftBrace)
                || token.type().equals(TokenType.If) || token.type().equals(TokenType.While)
                || token.type().equals(TokenType.Identifier);
    }

    public static void main(String args[]) {
        Parser parser = new Parser(new Lexer(args[0]));
        System.out.println("Begin parsing... " + args[0] + '\n');
        Program prog = parser.program();
        prog.display(); // display abstract syntax tree
    } // main

} // Parser
