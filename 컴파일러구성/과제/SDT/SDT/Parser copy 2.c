#define NO_KEYWORD 7
#define ID_LENGTH 12
#include "MiniC.tbl"
#include <stdio.h>
/* Mini C table for appendix A */
//#define  NO_RULES    97            /* number of rules */
//#define  GOAL_RULE  (NO_RULES+1)   /* accept rule */
//#define  NO_SYMBOLS  85            /* number of grammar symbols */
//#define  NO_STATES  153            /* number of states */
#define  PS_SIZE    100  

FILE * sourceFile;
FILE* astFile;

struct tokenType {
	int number;
	union {
		char id[ID_LENGTH];
		int num;
	} value;
};

typedef struct nodeType {
	struct tokenType token;            	// 토큰 종류
	enum { terminal, nonterm } noderep; // 노드의 종류
	struct nodeType* son;             	// 왼쪽 링크
	struct nodeType* brother;         	// 오른쪽 링크
	struct nodeType* father;		   	// 상위 링크
} Node;

int superLetter(char ch);
int superLetterOrDigit(char ch);
int getNumber(char firstCharacter);
int hexValue(char ch);
void lexicalError(int n);

void semantic(int);
void printToken(struct tokenType token); // -> MiniC Scanner
void dumpStack();
void errorRecovery();

Node* buildNode(struct tokenType token);
Node* buildTree(int nodeNumber, int rhsLength);
int meaningfulToken(struct tokenType token);
void printNode(Node* pt, int indent);
void printTree(Node* pt, int indent);

int errcnt = 0;
int sp;                               // stack pointer
int stateStack[PS_SIZE];              // state stack
int symbolStack[PS_SIZE];             // symbol stack
Node* valueStack[PS_SIZE];            // value stack

            /* size of parsing stack */

enum tsymbol { tnull=-1,
    tnot = 0,       tnotequ = 1,    	tremainder = 2, 	tremAssign = 3, 	tident = 4,     	tnumber = 5,
	/* 0         		 1       	     	2    		    	 3            		4          			5     */
	tand = 6,       tlparen = 7,    	trparen = 8,    	tmul = 9,  		    tmulAssign = 10, 	tplus = 11,
	/* 6          		 7      	    	8         			 9           		10     		    	11     */
    tinc = 12,      taddAssign = 13, 	tcomma = 14, 	    tminus = 15, 	    tdec = 16,	    	tsubAssign = 17,
	/* 12         		13          		14	 		       	15          		16         			17     */
	tdiv = 18,      tdivAssign = 19, 	tsemicolon = 21, 	tless = 22,      	tlesse = 23,     	tassign = 24,
	/* 18         		19          		21        			22           		23         			24     */
    tequal = 25,    tgreat = 26,     	tgreate = 27,    	tlbracket = 28,  	trbracket = 29,  	teof = 30,
	/* 25         		26          		27        			28           		29         			30     */
	//   ...........................................  word symbols  .......................................... //
	/* 33         		37          		39        			40           		41         			43     */
    tconst = 33,     telse = 37,      	tif = 39,        	tint = 40,       	treturn = 41,    	tvoid = 43,
	/* 44         		45          		46        			47                             */
    twhile = 44,     tlbrace = 45,    	tor = 46,        	trbrace = 47
};

char *tokenName[] = {
    "!",        "!=",      "%",       "%=",     "%ident",   "%number",
	/* 0          1           2         3          4          5        */
    "&&",       "(",       ")",       "*",      "*=",       "+",
	/* 6          7           8         9         10         11        */
    "++",       "+=",      ",",       "-",      "--",	    "-=",
	/* 12         13         14        15         16         17        */
    "/",        "/=",      	"",		  ";",       "<",       "<=",     
	/* 18         19         20        21         22         23        */
    "=",		"==",       ">",       ">=",      "[",      "]",       
	/* 24         25         26        27         28         29        */
	//   ...........    word symbols ................................. //
	/* 30         31         32        33         34         35        */
    "eof",        "",        "",     "const",    "	",     	 "",           
	/* 36         37         38        39         40         41        */
    ""  ,	  "else",        "",      "if",     "int",    "return",
	/* 42         43         44        45         46         47        */
    ""  ,     "void",   "while",   	  "{",       "||",       "}",       
};

char *keyword[NO_KEYWORD] = { 
    "const",  "else",    "if",    "int",    "return",  "void",    "while"
};

enum tsymbol tnum[NO_KEYWORD] = {
    tconst,    telse,     tif,     tint,     treturn,   tvoid,     twhile
};

enum nodeNumber {
	ERROR_NODE, // ERROR_NODE가 0번으로 지정되어야 함.
	ACTUAL_PARAM = 48, ADD = 50, ADD_ASSIGN = 51, ARRAY_VAR = 61, ASSIGN_OP = 51,
	CALL = 90, COMPOUND_ST = 52, CONST_NODE = 98, DCL = 57, DCL_ITEM = 73,
	DCL_LIST = 83, DCL_SPEC = 54, DIV = 81, DIV_ASSIGN = 51, EQ = 61,
	EXP_ST = 63, FORMAL_PARA = 66, FUNC_DEF = 68, FUNC_HEAD = 69,
	GE = 92, GT = 92, IDENT = 4, IF_ELSE_ST = 71, IF_ST = 71,
	INDEX = 90, INT_NODE = 99, LE = 92, LOGICAL_AND = 77, LOGICAL_NOT = 100,
	LOGICAL_OR = 78, LT = 92, MOD = 81, MOD_ASSIGN = 51, MUL = 81,
	MUL_ASSIGN = 51, NE = 61, NUMBER = 5, PARAM_DCL = 88, POST_DEC = 90,
	POST_INC = 90, PRE_DEC = 100, PRE_INC = 100, PROGRAM = 79, RETURN_ST = 93,
	SIMPLE_VAR = 61, STAT_LIST = 87, SUB = 50, SUB_ASSIGN = 51, UNARY_MINUS = 100,
	VOID_NODE = 99, WHILE_ST = 101
};

char* nodeName[] = {
	/* 0            1            2            3           4           */
	   "ERROR_NODE","PROGRAM",   0,           0,          0,
	/* 5            6            7            8           9           */
	   0,           "FUNC_DEF",  "FUNC_HEAD", "DCL_SPEC", 0,
	/* 10           11           12           13          14          */
	   0,           0,           0,           "CONST_NODE", "INT_NODE",
	/* 15           16           17           18          19          */
	   "VOID_NODE", 0,           "FORMAL_PARA", 0,          0,
	/* 20           21           22           23          24          */
	   0,           0,           "PARAM_DCL", "COMPOUND_ST","DCL_LIST",
	/* 25           26           27           28          29          */
	   "DCL_LIST",  0,           0,           "DCL",      0,
	/* 30           31           32           33          34          */
	   0,           "DCL_ITEM",  "DCL_ITEM",  "SIMPLE_VAR", "ARRAY_VAR",
	/* 35           36           37           38          39          */
	   0,           0,           "STAT_LIST",   0,          0,
	/* 40           41           42           43          44          */
	   0,           0,           0,           0,          0,
	/* 45           46           47           48          49          */
	   0,           0,      	 0,           0,          0,
	/* 50           51           52           53          54          */
	   0, 	 		"EXP_ST",    0,			  0,          0,
	/* 55           56           57           58          59          */
	   0,  			0,  		 0,  		  "IF_ST", 	  "IF_ELSE_ST",
	/* 60           61           62           63          64          */
	   "WHILE_ST",  0,           0,  		  0,          0,
	/* 65           66           67           68          69          */
	   0,           0,           "RETURN_ST", 0,          0,
	/* 70           71           72           73          74          */
	   "ASSIGN_OP", "ADD_ASSIGN","SUB_ASSIGN","MUL_ASSIGN","DIV_ASSIGN",
	/* 75           76           77           78          79          */
	   "MOD_ASSIGN",0,           "LOGICAL_OR",0,          "LOGICAL_AND",
	/* 80           81           82           83          84          */
	   0,           "EQ", 		 "NE", 		  0,    	  "GT",
	/* 85           86           87           88          89          */
	   "LT",        "GE",      	 "LE",        0,   		  "ADD",
	/* 90           91           92           93          94          */
	   "SUB",       0,           "MUL",		  "DIV",      "MOD",
	/* 95           96           97           98          99          */
	   0,           "UNARY_MINUS","LOGICAL_NOT", "PRE_INC", "PRE_DEC",
	/* 100          101          102          103         104         */
	   0,           "INDEX",     "CALL",     "POST_INC",  "POST_DEC",
	/* 105          106          107          						  */
	   0,			0,           "ACTUAL_PARAM"
};

int ruleName[] = {
	/* 0            1            2            3           4           */
	   0,           PROGRAM,     0,           0,          0,
	/* 5            6            7            8           9           */
	   0,           FUNC_DEF,    FUNC_HEAD,   DCL_SPEC,   0,
	/* 10           11           12           13          14          */
	   0,           0,           0,           CONST_NODE, INT_NODE,
	/* 15           16           17           18          19          */
	   VOID_NODE,   0,           FORMAL_PARA, 0,          0,
	/* 20           21           22           23          24          */
	   0,           0,           PARAM_DCL,   COMPOUND_ST,DCL_LIST,
	/* 25           26           27           28          29          */
	   DCL_LIST,    0,           0,           DCL,        0,
	/* 30           31           32           33          34          */
	   0,           DCL_ITEM,    DCL_ITEM,    SIMPLE_VAR, ARRAY_VAR,
	/* 35           36           37           38          39          */
	   0,           0,           STAT_LIST,   0,          0,
	/* 40           41           42           43          44          */
	   0,           0,           0,           0,          0,
	/* 45           46           47           48          49          */
	   0,           0,      	 0,           0,          0,
	/* 50           51           52           53          54          */
	   0, 	 		EXP_ST,    	 0,			  0,          0,
	/* 55           56           57           58          59          */
	   0,  			0,  		 0,  		  IF_ST, 	  IF_ELSE_ST,
	/* 60           61           62           63          64          */
	   WHILE_ST,  	0,           0,  		  0,          0,
	/* 65           66           67           68          69          */
	   0,           0,           RETURN_ST,   0,          0,
	/* 70           71           72           73          74          */
	   ASSIGN_OP,   ADD_ASSIGN,  SUB_ASSIGN,  MUL_ASSIGN, DIV_ASSIGN,
	/* 75           76           77           78          79          */
	   MOD_ASSIGN,  0,           LOGICAL_OR,  0,          LOGICAL_AND,
	/* 80           81           82           83          84          */
	   0,           EQ, 		 NE, 		  0,    	  GT,
	/* 85           86           87           88          89          */
	   LT,          GE,      	 LE,          0,   		  ADD,
	/* 90           91           92           93          94          */
	   SUB,         0,           MUL,		  DIV,        MOD,
	/* 95           96           97           98          99          */
	   0,           UNARY_MINUS, LOGICAL_NOT, PRE_INC,    PRE_DEC,
	/* 100          101          102          103         104         */
	   0,           INDEX,       CALL,        POST_INC,   POST_DEC,
	/* 105          106          107          						  */
	   0,			0,           ACTUAL_PARAM
};

struct tokenType scanner()
{
 struct tokenType token;
 int i, index;
 char ch, id[ID_LENGTH];
 
token.number = tnull;

do {
     while (isspace(ch = fgetc(sourceFile))) ;	// state 1: skip blanks
     if (superLetter(ch)) { // identifier or keyword
       i = 0;
       do {
            if (i < ID_LENGTH) id[i++] = ch;
            ch = fgetc(sourceFile);
       } while (superLetterOrDigit(ch));
	   if (i >= ID_LENGTH) lexicalError(1);
       id[i] = '\0';
       ungetc(ch, sourceFile);  //  retract
       // find the identifier in the keyword table
	   for (index=0; index < NO_KEYWORD; index++)
		   if (!strcmp(id, keyword[index])) break;
	   if (index < NO_KEYWORD)    // found, keyword exit
         token.number = tnum[index];
       else {                     // not found, identifier exit
			  token.number = tident;
			  strcpy(token.value.id, id);
       }
     }  // end of identifier or keyword
     else if (isdigit(ch)) {  // number
            token.number = tnumber;
            token.value.num = getNumber(ch);
          }
     else switch (ch) {  // special character
            case '/':
                      ch = fgetc(sourceFile);
                      if (ch == '*')			// text comment
						  do {
							  while (ch != '*') ch = fgetc(sourceFile);
							  ch = fgetc(sourceFile);
						  } while (ch != '/');
                      else if (ch == '/')		// line comment
						  while (fgetc(sourceFile) != '\n') ;
                      else if (ch == '=')  token.number = tdivAssign;
                      else { token.number = tdiv;
                             ungetc(ch, sourceFile); // retract
					  }
                      break;
            case '!':
                      ch = fgetc(sourceFile);
                      if (ch == '=')  token.number = tnotequ;
                        else { token.number = tnot;
                               ungetc(ch, sourceFile); // retract
                             }
                      break;
            case '%': 
                      ch = fgetc(sourceFile);
					  if (ch == '=') {
						  token.number = tremAssign;
					  }
					  else {
						  token.number = tremainder;
						  ungetc(ch, sourceFile);
					  }
					  break;
            case '&':
                      ch = fgetc(sourceFile);
                      if (ch == '&')  token.number = tand;
						else { lexicalError(2);
                               ungetc(ch, sourceFile);  // retract
                        }
                      break;
            case '*':
                      ch = fgetc(sourceFile);
                      if (ch == '=')  token.number = tmulAssign;
                        else { token.number = tmul;
                               ungetc(ch, sourceFile);  // retract
                             }
                      break;
            case '+':
                      ch = fgetc(sourceFile);
                      if (ch == '+')  token.number = tinc;
                        else if (ch == '=') token.number = taddAssign;
                           else { token.number = tplus;
                                  ungetc(ch, sourceFile);  // retract
                                }
                      break;
            case '-':
                      ch = fgetc(sourceFile);
                      if (ch == '-')  token.number = tdec;
                         else if (ch == '=') token.number = tsubAssign;
                              else { token.number = tminus;
                                     ungetc(ch, sourceFile);  // retract
							  }
                      break;
            case '<':
                      ch = fgetc(sourceFile);
                      if (ch == '=') token.number = tlesse;
                         else { token.number = tless;
                                ungetc(ch, sourceFile);  // retract
						 }
                      break;
            case '=':
                      ch = fgetc(sourceFile);
                      if (ch == '=')  token.number = tequal;
                        else { token.number = tassign;
                               ungetc(ch, sourceFile);  // retract
                             }
                      break;
            case '>':
                      ch = fgetc(sourceFile);
                      if (ch == '=') token.number = tgreate;
                        else { token.number = tgreat;
                               ungetc(ch, sourceFile);  // retract
                             }
                      break;
            case '|':
                      ch = fgetc(sourceFile);
                      if (ch == '|')  token.number = tor;
					  else { lexicalError(3);
                             ungetc(ch, sourceFile);  // retract
                           }
                      break;
            case '(': token.number = tlparen;         break;
            case ')': token.number = trparen;         break;
            case ',': token.number = tcomma;          break;
            case ';': token.number = tsemicolon;      break;
            case '[': token.number = tlbracket;       break;
            case ']': token.number = trbracket;       break;
            case '{': token.number = tlbrace;         break;
            case '}': token.number = trbrace;         break;
            case EOF: token.number = teof;            break;
			default:  {
						printf("Current character : %c", ch);
						lexicalError(4);
						break;
					  }

          } // switch end
   } while (token.number == tnull);
   return token;
} // end of scanner

void lexicalError(int n)
{
	printf(" *** Lexical Error : ");
	switch (n) {
		case 1: printf("an identifier length must be less than 12.\n");
				break;
		case 2: printf("next character must be &\n");
				break;
		case 3: printf("next character must be |\n");
				break;
		case 4: printf("invalid character\n");
				break;
	}
}

int superLetter(char ch)
{
	if (isalpha(ch) || ch == '_') return 1;
		else return 0;
}

int superLetterOrDigit(char ch)
{
	if (isalnum(ch) || ch == '_') return 1;
		else return 0;
}

int getNumber(char firstCharacter)
{
	int num = 0;
	int value;
	char ch;

	if (firstCharacter == '0') {
		ch = fgetc(sourceFile);
		if ((ch == 'X') || (ch == 'x'))	{		// hexa decimal
			while ((value=hexValue(ch=fgetc(sourceFile))) != -1)
				num = 16*num + value;
		}
		else if ((ch >= '0') && (ch <= '7'))	// octal
				do {
					num = 8*num + (int)(ch - '0');
					ch = fgetc(sourceFile);
				} while ((ch >= '0') && (ch <= '7'));
			 else num = 0;						// zero
	} else {									// decimal
			ch = firstCharacter;
			do {
				num = 10*num + (int)(ch - '0');
				ch = fgetc(sourceFile);
			} while (isdigit(ch));
	}
    ungetc(ch, sourceFile);  /*  retract  */
	return num;
}

int hexValue(char ch)
{
	switch (ch) {
		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':
			return (ch - '0');
		case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
			return (ch - 'A' + 10);
		case 'a': case 'b': case 'c': case 'd': case 'e': case 'f':
			return (ch - 'a' + 10);
		default: return -1;
	}
}

Node* buildNode(struct tokenType token)
{
	Node* ptr;
	ptr = (Node*)malloc(sizeof(Node));
	if (!ptr) {
		printf("malloc error in buildNode()\n");
		exit(1);
	}
	ptr->token = token;
	ptr->noderep = terminal;
	ptr->son = ptr->brother = NULL;
	return ptr;
}

Node* buildTree(int nodeNumber, int rhsLength)
{
	int i, j, start;
	Node* first, * ptr;

	i = sp - rhsLength + 1;
	/* step 1: find a first index with node in value stack */
	while (i <= sp && valueStack[i] == NULL) i++;
	if (!nodeNumber && i > sp) return NULL;
	start = i;
	/* step 2: linking brothers */
	while (i <= sp - 1) {
		j = i + 1;
		while (j <= sp && valueStack[j] == NULL) j++;
		if (j <= sp) {
			ptr = valueStack[i];
			while (ptr->brother) ptr = ptr->brother;
			ptr->brother = valueStack[j];
		}
		i = j;
	}
	first = (start > sp) ? NULL : valueStack[start];
	/* step 3: making subtree root and linking son */
	if (nodeNumber) {
		ptr = (Node*)malloc(sizeof(Node));
		if (!ptr) {
			printf("malloc error in buildTree()\n");
			exit(1);
		}
		ptr->token.number = nodeNumber;
		ptr->noderep = nonterm;
		ptr->son = first;
		ptr->brother = NULL;
		return ptr;
	}
	else return first;
}

void printNode(Node* pt, int indent)
{
	int i;

	for (i = 1; i <= indent; i++) fprintf(astFile, " ");
	if (pt->noderep == terminal) {
		if (pt->token.number == tident)
			fprintf(astFile, " Terminal: %s", pt->token.value.id);
		else if (pt->token.number == tnumber)
			fprintf(astFile, " Terminal: %d", pt->token.value.num);
	}
	else { // nonterminal node
		i = (int)(pt->token.number);
		fprintf(astFile, " Nonterminal: %s", nodeName[i]);
	}
	fprintf(astFile, "\n");
}

void printTree(Node* pt, int indent)
{
	Node* p = pt;
	while (p != NULL) {
		printNode(p, indent);
		if (p->noderep == nonterm) printTree(p->son, indent + 5);
		p = p->brother;
	}
}

Node* parser()
{
	extern int parsingTable[NO_STATES][NO_SYMBOLS + 1];
	extern int leftSymbol[NO_RULES + 1], rightLength[NO_RULES + 1];
	int entry, ruleNumber, lhs;
	int currentState;
	struct tokenType token;
	Node* ptr;

	sp = 0; stateStack[sp] = 0;  // initial state
	token = scanner();
	while (1) {
		currentState = stateStack[sp];
		entry = parsingTable[currentState][token.number];
		if (entry > 0)                          /* shift action */
		{
			sp++;
			if (sp > PS_SIZE) {
				printf("critical compiler error: parsing stack overflow");
				exit(1);
			}
			symbolStack[sp] = token.number;
			stateStack[sp] = entry;
			valueStack[sp] = meaningfulToken(token) ? buildNode(token) : NULL;
			token = scanner();
		}
		else if (entry < 0)                   /* reduce action */
		{
			ruleNumber = -entry;
			if (ruleNumber == GOAL_RULE) /* accept action */
			{
				//                      printf(" *** valid source ***\n");
				return valueStack[sp - 1];
			}
			//                 semantic(ruleNumber);
			ptr = buildTree(ruleName[ruleNumber], rightLength[ruleNumber]);
			printTree(ptr, 0);
			sp = sp - rightLength[ruleNumber];
			lhs = leftSymbol[ruleNumber];
			currentState = parsingTable[stateStack[sp]][lhs];
			sp++;
			symbolStack[sp] = lhs;
			stateStack[sp] = currentState;
			valueStack[sp] = ptr;
		}
		else                               /* error action */
		{
			printf(" === error in source ===\n");
			printf("Current Token : ");
			printToken(token);
			dumpStack();
			errorRecovery();
			token = scanner();
		}
	} /* while (1) */
} /* parser */

void semantic(int n)
{
	printf("%d ", n);
}

void dumpStack()
{
	int i, start;

	if (sp > 10) start = sp - 10;
	else start = 0;

	printf("\n *** dump state stack :");
	for (i = start; i <= sp; ++i)
		printf(" %d", stateStack[i]);

	printf("\n *** dump symbol stack :");
	for (i = start; i <= sp; ++i)
		printf(" %d", symbolStack[i]);
	printf("\n");
}

void printToken(struct tokenType token)
{
	if (token.number == tident)
		printf("%s", token.value.id);
	else if (token.number == tnumber)
		printf("%d", token.value.num);
	else
		printf("%s", tokenName[token.number]);

}

void errorRecovery()
{
	struct tokenType tok;
	int parenthesisCount, braceCount;
	int i;

	// step 1: skip to the semicolon
	parenthesisCount = braceCount = 0;
	while (1) {
		tok = scanner();
		if (tok.number == teof) exit(1);
		if (tok.number == tlparen) parenthesisCount++;
		else if (tok.number == trparen) parenthesisCount--;
		if (tok.number == tlbrace) braceCount++;
		else if (tok.number == trbrace) braceCount--;
		if ((tok.number == tsemicolon) && (parenthesisCount <= 0) && (braceCount <= 0))
			break;
	}

	// step 2: adjust state stack
	for (i = sp; i >= 0; i--) {
		// statement_list ->  statement_list .  statement
		if (stateStack[i] == 36) break;	 // second statement part

		// statement_list ->  .  statement
		// statement_list ->  .  statement_list statement
		if (stateStack[i] == 24) break;	 // first statement part

		// declaration_list ->  declaration_list .  declaration
		if (stateStack[i] == 25) break;  // second internal dcl

		// declaration_list ->  .  declaration
		// declaration_list ->  .  declaration_list declaration
		if (stateStack[i] == 17) break;  // internal declaration

		// external declaration
		// external_dcl ->  .  declaration
		if (stateStack[i] == 2) break;	// after first external dcl
		if (stateStack[i] == 0) break;	// first external declaration
	}
	sp = i;
}

int meaningfulToken(struct tokenType token)
{
	if ((token.number == tident) || (token.number == tnumber))
		return 1;
	else return 0;
}
int main(int argc, char* argv[])
{
    sourceFile = fopen(argv[1], "r");
	astFile = fopen(argv[2], "w");
	Node * ast = parser();
	printTree(ast, 5);
}