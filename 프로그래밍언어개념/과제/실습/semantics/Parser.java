import java.util.*;

public class Parser {
    // Recursive descent parser that inputs a C++Lite program and 
    // generates its abstract syntax.  Each method corresponds to
    // a concrete syntax grammar rule, which appears as a comment
    // at the beginning of the method.
  
    Token token;          // current token from the input stream
    Lexer lexer;
  
    public Parser(Lexer ts) { // Open the C++Lite source program
        lexer = ts;                          // as a token stream, and
        token = lexer.next();            // retrieve its first Token
    }
  
    private String match (TokenType t) {
        String value = token.value();
        if (token.type().equals(t))
            token = lexer.next();
        else
            error(t);
        return value;
    }
  
    private void error(TokenType tok) {
        System.err.println("Syntax error: expecting: " + tok 
                           + "; saw: " + token);
        System.exit(1);
    }

    private void error(String tok) {
        System.err.println("Syntax error: expecting: " + tok 
                           + "; saw: " + token);
        System.exit(1);
    }
  
    public Program program() {
        // Program --> void main ( ) '{' Declarations Statements '}'
        TokenType[ ] header = {TokenType.Int, TokenType.Main,
                          TokenType.LeftParen, TokenType.RightParen};
        for (int i=0; i<header.length; i++)   // bypass "int main ( )"
            match(header[i]);
        match(TokenType.LeftBrace);
        Program p = new Program(declarations(), main_statements());
        return p;
    }

    private Declarations declarations () {
        // Declarations --> { Declaration }
        Declarations decls = new Declarations();
        while(true)
        {
            if(isType())
                declaration(decls);
            else
                break;
        }
        return decls;
    }
  
    private void declaration (Declarations ds) {
        // Declaration  --> Type Identifier { , Identifier } ;
        Type t = type();
        Declaration decl;
        Variable v = null;

        if (token.type().equals(TokenType.Identifier)) {
            v = new Variable(match(TokenType.Identifier));
        }
        decl = new Declaration(v, t);
        ds.add(decl);

        while(true)
        {
            if(token.type().equals(TokenType.Comma))
            {
                token = lexer.next();
                if(token.type().equals(TokenType.Identifier)) {
                    v = new Variable(match(TokenType.Identifier));
                }
                decl = new Declaration(v, t);
                ds.add(decl);
            }
            else if(token.type().equals(TokenType.Semicolon))
            {
                token = lexer.next();
                break;
            }
            else
                break;
        }
    }
  
    private Type type () {
        // Type  -->  int | bool | float | char 
        Type t = null;

        if(isType())
        {
            if(token.type().equals(TokenType.Int))
                t = Type.INT;
            else if(token.type().equals(TokenType.Bool))
                t = Type.BOOL;
            else if(token.type().equals(TokenType.Float))
                t = Type.FLOAT;
            else if(token.type().equals(TokenType.Char))
                t = Type.CHAR;
           token = lexer.next();
        }

        return t;
    }
  
    private Block statements () {
        // Block --> '{' Statements '}'
        Block b = new Block();
        if(token.type().equals(TokenType.LeftBrace))
        {
            token = lexer.next();
            while(true)
            {
                if(token.type().equals(TokenType.RightBrace))
                {
                    token = lexer.next();
                    break;
                }
                b.members.add(statement());
            }
        }
        return b;
    }

    private Block main_statements () {
        // Block --> '{' Statements '}'
        Block b = new Block();
        while(true)
        {
            if(token.type().equals(TokenType.RightBrace))
                break;
            b.members.add(statement());
        }
        return b;
    }
  
    private Statement statement() {
        // Statement --> ; | Block | Assignment | IfStatement | WhileStatement
        Statement s = new Skip();
        if (token.type().equals(TokenType.Semicolon))
        {
            s = new Skip();
            token = lexer.next();
        }
        else if (token.type().equals(TokenType.LeftBrace))
            s = statements();
        else if (token.type().equals(TokenType.Identifier))
            s = assignment();
        else if (token.type().equals(TokenType.If))
            s = ifStatement();
        else if (token.type().equals(TokenType.While))
            s = whileStatement();
        return s;
    }
  
    private Assignment assignment () {
        // Assignment --> Identifier = Expression ;
        Variable v = null;
        Expression e = null;
        if (token.type().equals(TokenType.Identifier)) {
            v = new Variable(match(TokenType.Identifier));
            if (token.type().equals(TokenType.Assign))
            {
                token = lexer.next();
                e = expression();
                if(token.type().equals(TokenType.Semicolon))
                {
                    token = lexer.next();
                }
            }
        }
        return new Assignment(v, e);
    }
  
    private Conditional ifStatement () {
        // IfStatement --> if ( Expression ) Statement [ else Statement ]
        Expression e = null;
        Statement s = null;
        Statement s2 = new Skip();

        if(token.type().equals(TokenType.If))
        {
            token = lexer.next();
            if(token.type().equals(TokenType.LeftParen))
            {
                token = lexer.next();
                e = expression();
                if(token.type().equals(TokenType.RightParen))
                {
                    token = lexer.next();
                    s = statement();
                    if(token.type().equals(TokenType.Else))
                    {
                        token = lexer.next();
                        s2 = statement();
                    }
                }
            }
        }
        return new Conditional(e,s,s2);
    }
  
    private Loop whileStatement () {
        // WhileStatement --> while ( Expression ) Statement
        Expression e = null;
        Statement s = new Skip();

        if(token.type().equals(TokenType.While))
        {
            token = lexer.next();
            if(token.type().equals(TokenType.LeftParen))
            {
                token = lexer.next();
                e = expression();
                if(token.type().equals(TokenType.RightParen))
                {
                    token = lexer.next();
                    s = statement();
                }
            }
        }
        return new Loop(e,s);
    }

    private Expression expression () {
        // Expression --> Conjunction { || Conjunction }
        Expression e = conjunction();
        while (isOrOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = conjunction();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression conjunction () {
        // Conjunction --> Equality { && Equality }
        Expression e = equality();
        while (isAndOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = equality();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression equality () {
        // Equality --> Relation [ EquOp Relation ]
        Expression e = relation();
        if (isEquOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = relation();
            e = new Binary(op, e, term2);
        }
        return e;
    }

    private Expression relation (){
        // Relation --> Addition [RelOp Addition] 
        Expression e = addition();
        if (isRelOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = addition();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression addition () {
        // Addition --> Term { AddOp Term }
        Expression e = term();
        while (isAddOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = term();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression term () {
        // Term --> Factor { MultiplyOp Factor }
        Expression e = factor();
        while (isMultiplyOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term2 = factor();
            e = new Binary(op, e, term2);
        }
        return e;
    }
  
    private Expression factor() {
        // Factor --> [ UnaryOp ] Primary 
        if (isUnaryOp()) {
            Operator op = new Operator(match(token.type()));
            Expression term = primary();
            return new Unary(op, term);
        }
        else return primary();
    }
  
    private Expression primary () {
        // Primary --> Identifier | Literal | ( Expression )
        //             | Type ( Expression )
        Expression e = null;
        if (token.type().equals(TokenType.Identifier)) {
            e = new Variable(match(TokenType.Identifier));
        } else if (isLiteral()) {
            e = literal();
        } else if (token.type().equals(TokenType.LeftParen)) {
            token = lexer.next();
            e = expression();       
            match(TokenType.RightParen);
        } else if (isType()) {
            Operator op = new Operator(match(token.type()));
            match(TokenType.LeftParen);
            Expression term = expression();
            match(TokenType.RightParen);
            e = new Unary(op, term);
        } else error("Identifier | Literal | ( | Type");
        return e;
    }

    private Value literal( ) {
        Value value = null;
        if (token.type().equals(TokenType.IntLiteral)) {
            value = new IntValue (Integer.parseInt(token.value()));
            token = lexer.next();
        }
        else if (token.type().equals(TokenType.FloatLiteral))  {
            value = new FloatValue(Float.parseFloat(token.value()));
            token = lexer.next();
        }
        else if (token.type().equals(TokenType.CharLiteral))  {
            value = new CharValue(token.value().charAt(0));
            token = lexer.next();
        }
        else if (token.type().equals(TokenType.True))  {
            value = new BoolValue(true);
            token = lexer.next();
        }
        else if (token.type().equals(TokenType.False))  {
            value = new BoolValue(false);
            token = lexer.next();
        }
        return value;
    }
  
    private boolean isOrOp( ) {
        return token.type().equals(TokenType.Or);
    }
  
    private boolean isAndOp( ) {
        return token.type().equals(TokenType.And);
    }

    private boolean isEquOp( ) {
        return token.type().equals(TokenType.Equals) ||
               token.type().equals(TokenType.NotEqual);
    }
  
    private boolean isRelOp( ) {
        return token.type().equals(TokenType.Less) ||
               token.type().equals(TokenType.LessEqual) ||
               token.type().equals(TokenType.Greater) ||
               token.type().equals(TokenType.GreaterEqual);
    }

    private boolean isAddOp( ) {
        return token.type().equals(TokenType.Plus) ||
               token.type().equals(TokenType.Minus);
    }
    
    private boolean isMultiplyOp( ) {
        return token.type().equals(TokenType.Multiply) ||
               token.type().equals(TokenType.Divide);
    }
    
    private boolean isUnaryOp( ) {
        return token.type().equals(TokenType.Not) ||
               token.type().equals(TokenType.Minus);
    }
    
    private boolean isEqualityOp( ) {
        return token.type().equals(TokenType.Equals) ||
            token.type().equals(TokenType.NotEqual);
    }
    
    private boolean isRelationalOp( ) {
        return token.type().equals(TokenType.Less) ||
               token.type().equals(TokenType.LessEqual) || 
               token.type().equals(TokenType.Greater) ||
               token.type().equals(TokenType.GreaterEqual);
    }
    
    private boolean isType( ) {
        return token.type().equals(TokenType.Int)
            || token.type().equals(TokenType.Bool) 
            || token.type().equals(TokenType.Float)
            || token.type().equals(TokenType.Char);
    }
    
    private boolean isLiteral( ) {
        return token.type().equals(TokenType.IntLiteral) ||
            isBooleanLiteral() ||
            token.type().equals(TokenType.FloatLiteral) ||
            token.type().equals(TokenType.CharLiteral);
    }
    
    private boolean isBooleanLiteral( ) {
        return token.type().equals(TokenType.True) ||
            token.type().equals(TokenType.False);
    }

    public static void main(String args[]) {
        Parser parser  = new Parser(new Lexer(args[0]));
        Program prog = parser.program();
        prog.display();           // display abstract syntax tree
    } //main

} // Parser
