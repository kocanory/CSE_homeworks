#define NO_KEYWORD 7
#define ID_LENGTH 12
#include "MiniC.tbl"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
};	//변경된 부분 : MiniC.lst와 MiniC.tbl을 참고하여 각 token별로 shift & reduce 할 때 parsing table에서 token의 위치가 어디에 있는지 확인하고 이 index를 token number로 배정한다.

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
};	//변경된 부분 : token number로 각 토큰 이름에 접근하므로 token number에 해당하는 자리에 token name이 존재해야 한다. 따라서 token name 원소의 순서를 token number에 맞게 재배치.

char *keyword[NO_KEYWORD] = { 
    "const",  "else",    "if",    "int",    "return",  "void",    "while"
};

enum tsymbol tnum[NO_KEYWORD] = {
    tconst,    telse,     tif,     tint,     treturn,   tvoid,     twhile
};

enum nodeNumber {
	ERROR_NODE, // ERROR_NODE가 0번으로 지정되어야 함.
	ACTUAL_PARAM = 48, ADD, ADD_ASSIGN, ARRAY_VAR, ASSIGN_OP,
	CALL, COMPOUND_ST, CONST_NODE, DCL, DCL_ITEM,
	DCL_LIST, DCL_SPEC, DIV, DIV_ASSIGN, EQ,
	EXP_ST, FORMAL_PARA, FUNC_DEF, FUNC_HEAD,
	GE, GT, IDENT, IF_ELSE_ST, IF_ST,
	INDEX, INT_NODE, LE, LOGICAL_AND, LOGICAL_NOT,
	LOGICAL_OR, LT, MOD, MOD_ASSIGN, MUL,
	MUL_ASSIGN, NE, NUMBER, PARAM_DCL, POST_DEC,
	POST_INC, PRE_DEC, PRE_INC, PROGRAM, RETURN_ST,
	SIMPLE_VAR, STAT_LIST, SUB, SUB_ASSIGN, UNARY_MINUS,
	VOID_NODE, WHILE_ST
}; /*변경된 부분 : tree를 만들 때 노드마다 토큰 넘버로 노드 넘버를 저장하게 되는데, 만약 토큰 넘버와 중복되면 본래 정보와는 다른 노드가 나올 수 있음.
   				  그래서 ERROR_NODE를 제외하고 현재 최대 토큰 넘버인 47보다 큰 값을 노드 넘버로 배정한다.*/

char* nodeName[] = {
   "ERROR_NODE",
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      	 	0,          	0,          	0,
   0,           	0,      	 	0,           	0,          	0,
   0,           	0,      		"ACTUAL_PARAM", "ADD",    		"ADD_ASSIGN", 
   "ARRAY_VAR",  	"ASSIGN_OP", 	"CALL",   		"COMPOUND_ST", 	"CONST_NODE", 
   "DCL",        	"DCL_ITEM",  	"DCL_LIST", 	"DCL_SPEC",  	"DIV",          
   "DIV_ASSIGN", 	"EQ",   	   	"EXP_ST",   	"FORMAL_PARA",	"FUNC_DEF",    
   "FUNC_HEAD",		"GE",           "GT",          	"IDENT",        "IF_ELSE_ST", 
   "IF_ST",			"INDEX",        "INT_NODE",    	"LE",           "LOGICAL_AND", 
   "LOGICAL_NOT",	"LOGICAL_OR",   "LT",          	"MOD",          "MOD_ASSIGN",  
   "MUL",			"MUL_ASSIGN",   "NE",          	"NUMBER",       "PARAM_DCL",   
   "POST_DEC",		"POST_INC",     "PRE_DEC",     	"PRE_INC",      "PROGRAM",     
   "RETURN_ST",		"SIMPLE_VAR",   "STAT_LIST",   	"SUB",          "SUB_ASSIGN",  
   "UNARY_MINUS",	"VOID_NODE",    "WHILE_ST"
}; //변경된 부분 : 위의 노드 넘버를 인덱스로 사용하여 어떤 노드인지 파악하고, 별도의 파일에 출력해야 하므로 노드 넘버와 노드 이름의 순서는 같아야 함

int ruleName[] = {
	/* 0            1            2            3           4           */
	   0,           PROGRAM,     0,           0,          0,
	/* 5            6            7            8           9           */
	   0,           FUNC_DEF,    FUNC_HEAD,   DCL_SPEC,   0,
	/* 10           11           12           13          14          */
	   0,           IDENT,       0,           CONST_NODE, INT_NODE,
	/* 15           16           17           18          19          */
	   VOID_NODE,   0,           FORMAL_PARA, 0,          0,
	/* 20           21           22           23          24          */
	   0,           0,           PARAM_DCL,   COMPOUND_ST,DCL_LIST,
	/* 25           26           27           28          29          */
	   DCL_LIST,    0,           0,           DCL,        0,
	/* 30           31           32           33          34          */
	   NUMBER,      DCL_ITEM,    DCL_ITEM,    SIMPLE_VAR, ARRAY_VAR,
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
	/* 105          106          107          108		  109		  */
	   0,			0,           ACTUAL_PARAM,0,		  0,
	/* 110          111			 112*/
	   IDENT,       NUMBER,		 0
};	//변경된 부분 : MiniC.lst에 기재된 rule number에 따른 생성 규칙 및 노드 생성에 맞추어 rule name또한 rule number에 맞게 순서를 조정
	//현재 MiniC.lst에 기재된 생성규칙의 개수는 112개이므로 index 112까지는 원소가 존재해야 함.
	//IDENT와 NUMBER의 경우 복수의 생성규칙에서 생성되기에 해당되는 생성규칙마다 IDENT, NUMBER가 존재해야 함.
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
	printf("%d ", n);	//변경된 부분 : 좀 더 right parse를 한 눈에 보기 위해 rule number만 출력하도록 함
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

#define LABEL_SIZE 10
#define SYMTAB_SIZE 100

FILE *sourceFile;
FILE *ucodeFile;
FILE *astFile;

int base = 1, offset = 1, width = 1;
int lvalue, rvalue;

enum opcodeEnum {
    notop,	neg,	incop,	decop,	dup,
    add,	sub,	mult,	divop,	modop,	swp,
    andop,	orop,	gt,	lt,	ge,	le,	eq,	ne,
    lod,	str,	ldc,	lda,
    ujp,	tjp,	fjp,
    chkh,	chkl,
    ldi,	sti,
    call,	ret,	retv,	ldp,	proc,	endop,
    nop,	bgn,	sym
};

char *opcodeName[] = {
    "notop",    "neg",	"inc",	"dec",	"dup",
    "add",	"sub",	"mult",	"div",	"mod",	"swp",
    "and",	"or",	"gt",	"lt",	"ge",	"le",	"eq",	"ne",
    "lod",	"str",	"ldc",	"lda",
    "ujp",	"tjp",	"fjp",
    "chkh",	"chkl",
    "ldi",	"sti",
    "call",	"ret",	"retv",	"ldp",	"proc",	"end",
    "nop",	"bgn",	"sym"
};

enum typeEnum {
    INT_TYPE,	VOID_TYPE,	VAR_TYPE,	CONST_TYPE,	FUNC_TYPE
};

typedef struct tableType {
    char name[LABEL_SIZE];
    int typeSpecifier;
    int typeQualifier;
    int base;
    int offset;
    int width;
    int initialValue;
    int level;
} SymbolTable;

SymbolTable symbolTable[SYMTAB_SIZE];
int symLevel = 0;
int stTop;

void initSymbolTable()
{
    stTop = 0;
}

void icg_error(int errno)
{
    printf("ICG_ERROR: %d\n", errno);
}

//////////////////////////////////////////////////////////////////////////// Declaration
int insert(char *name, int typeSpecifier, int typeQualifier,
        int base, int offset, int width, int initialValue)
{
    SymbolTable *stptr = &symbolTable[stTop];
    strcpy(stptr->name, name);
    stptr->typeSpecifier = typeSpecifier;
    stptr->typeQualifier = typeQualifier;
    stptr->base = base;
    stptr->offset = offset;
    stptr->width = width;
    stptr->initialValue = initialValue;
    stptr->level = symLevel;

    return ++stTop;
}

int typeSize(int typeSpecifier)
{
    if(typeSpecifier == INT_TYPE)
        return 1;
    else {
        printf("not yet implemented\n");
        return 1;
    }
}

void processSimpleVariable(Node *ptr, int typeSpecifier, int typeQualifier)
{
    Node *p = ptr->son;     // variable name(=> identifier)
    Node *q = ptr->brother; // initial value part
    int stIndex, size, initialValue;
    int sign = 1;

    if(ptr->token.number != SIMPLE_VAR) printf("error in SIMPLE_VAR\n");

    if(typeQualifier == CONST_TYPE) {   // constant type
        if(q == NULL) {
            printf("%s must have a constant value\n", ptr->son->token.value.id);
            return;
        }
        if(q->token.number == UNARY_MINUS) {
            sign = -1;
            q = q->son;
        }
        initialValue = sign * q->token.value.num;

        stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
                0/*base*/, 0/*offset*/, 0/*width*/, initialValue);
    } else {
        size = typeSize(typeSpecifier);
        stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
                base, offset, width, 0);
        offset += size;
    }
}

void processArrayVariable(Node *ptr, int typeSpecifier, int typeQualifier)
{
    Node *p = ptr->son; // variable name(=> identifier)
    int stIndex, size;

    if(ptr->token.number != ARRAY_VAR) {
        printf("error in ARRAY_VAR\n");
        return;
    }
    if(p->brother == NULL) // no size
        printf("array size must be specified\n");
    else size = p->brother->token.value.num;

    size *= typeSize(typeSpecifier);

    stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
            base, offset, size, 0);
    offset += size;
}

void processDeclaration(Node *ptr)
{
    int typeSpecifier, typeQualifier;
    Node *p, *q;

    if(ptr->token.number != DCL_SPEC) icg_error(4);

    // printf("processDeclaration\n");
    // step 1: process DCL_SPEC
    typeSpecifier = INT_TYPE; // default type
    typeQualifier = VAR_TYPE;
    p = ptr->son;
    while(p) {
        if(p->token.number == INT_NODE) typeSpecifier = INT_TYPE;
        else if(p->token.number == CONST_NODE)
            typeQualifier = CONST_TYPE;
        else { // AUTO, EXTERN, REGISTER, FLOAT, DOUBLE, SIGNED, UNSIGEND
            printf("not yet implemented\n");
            return;
        }
        p = p->brother;
    }

    // step 2: process DCL_ITEM
    p = ptr->brother;
    if(p->token.number != DCL_ITEM) icg_error(5);

    while(p) {
        q = p->son; // SIMPLE_VAR or ARRAY_VAR
        switch(q->token.number) {
            case SIMPLE_VAR: // simple variable
                processSimpleVariable(q, typeSpecifier, typeQualifier);
                break;
            case ARRAY_VAR:  // array variable
                processArrayVariable(q, typeSpecifier, typeQualifier);
                break;
            default:
                printf("error in SIMPLE_VAR or ARRAY_VAR\n");
                break;
        }
        p = p->brother;
    }
}

//////////////////////////////////////////////////////////////////////////// Expression
int lookup(char *name)
{
    int i;
    for(i=0; i<stTop; i++) {
        if((strcmp(name, symbolTable[i].name) == 0) && (symbolTable[i].level == symLevel)) {
            return i;
        }
    }
    return -1;
}

void emit0(int opcode)
{
    fprintf(ucodeFile, "           %s\n", opcodeName[opcode]);
}

void emit1(int opcode, int operand)
{
    fprintf(ucodeFile, "           %s %d\n", opcodeName[opcode], operand);
}

void emit2(int opcode, int operand1, int operand2)
{
    fprintf(ucodeFile, "           %s %d %d\n", opcodeName[opcode], operand1, operand2);
}

void emit3(int opcode, int operand1, int operand2, int operand3)
{
    fprintf(ucodeFile, "           %s %d %d %d\n", opcodeName[opcode], operand1, operand2, operand3);
}

void emitJump(int opcode, char *label)
{
    fprintf(ucodeFile, "           %s %s\n", opcodeName[opcode], label);
}

void rv_emit(Node *ptr)
{
    int stIndex;

    if(ptr->token.number == tnumber)        // number
        emit1(ldc, ptr->token.value.num);
    else {                                  // identifier
        stIndex = lookup(ptr->token.value.id);
        if(stIndex == -1) return;
        if(symbolTable[stIndex].typeQualifier == CONST_TYPE) // constant
            emit1(ldc, symbolTable[stIndex].initialValue);
        else if(symbolTable[stIndex].width > 1)     // array var
            emit2(lda, symbolTable[stIndex].base, symbolTable[stIndex].offset);
        else                                        // simple var
            emit2(lod, symbolTable[stIndex].base, symbolTable[stIndex].offset);
    }
}

void processOperator(Node *ptr);
int checkPredefined(Node *ptr)
{
    Node *p = NULL;
    if(strcmp(ptr->token.value.id, "read") == 0) {
        emit0(ldp);
        p = ptr->brother; // ACTUAL_PARAM
        while(p) {
            if(p->noderep == nonterm) processOperator(p);
            else rv_emit(p);
            p = p->brother;
        }
        emitJump(call, "read");
        return 1;
    }
    else if(strcmp(ptr->token.value.id, "write") == 0) {
        emit0(ldp);
        p = ptr->brother; // ACTUAL_PARAM
        while(p) {
            if(p->noderep == nonterm) processOperator(p);
            else rv_emit(p);
            p = p->brother;
        }
        emitJump(call, "write");
        return 1;
    }
    else if(strcmp(ptr->token.value.id, "lf") == 0) {
        emitJump(call, "lf");
        return 1;
    }
    return 0;
}

void processOperator(Node *ptr)
{
    switch(ptr->token.number) {
        // assignment operator
        case ASSIGN_OP:
        {
            Node *lhs = ptr->son, *rhs = ptr->son->brother;
            int stIndex;

            // step 1: generate instructions for left-hand side if INDEX node.
            if(lhs->noderep == nonterm) { // array variable
                lvalue = 1;
                processOperator(lhs);
                lvalue = 0;
            }

            // step 2: generate instructions for right-hand side
            if(rhs->noderep == nonterm) processOperator(rhs);
            else rv_emit(rhs);

            // step 3: generate a store instruction
            if(lhs->noderep == terminal) { // simple variable
                stIndex = lookup(lhs->token.value.id);
                if(stIndex == -1) {
                    printf("undefined variable : %s\n", lhs->token.value.id);
                    return;
                }
                emit2(str, symbolTable[stIndex].base, symbolTable[stIndex].offset);
            } else
                emit0(sti);
            break;
        }

        // complex assignment operators
        case ADD_ASSIGN: case SUB_ASSIGN: case MUL_ASSIGN:
        case DIV_ASSIGN: case MOD_ASSIGN:
        {
            Node *lhs = ptr->son, *rhs = ptr->son->brother;
            int nodeNumber = ptr->token.number;
            int stIndex;

            ptr->token.number = ASSIGN_OP;
            // step 1: code generation for left hand side
            if(lhs->noderep == nonterm) {
                lvalue = 1;
                processOperator(lhs);
                lvalue = 0;
            }
            ptr->token.number = nodeNumber;
            // step 2: code generation for repeating part
            if(lhs->noderep == nonterm)
                processOperator(lhs);
            else rv_emit(lhs);
            // step 3: code generation for right hand side
            if(rhs->noderep == nonterm)
                processOperator(rhs);
            else rv_emit(rhs);
            // step 4: emit the corresponding operation code
            switch(ptr->token.number) {
                case ADD_ASSIGN: emit0(add); break;
                case SUB_ASSIGN: emit0(sub); break;
                case MUL_ASSIGN: emit0(mult); break;
                case DIV_ASSIGN: emit0(divop); break;
                case MOD_ASSIGN: emit0(modop); break;
            }
            // step 5: code generation for store code
            if(lhs->noderep == terminal) {
                stIndex = lookup(lhs->token.value.id);
                if(stIndex == -1) {
                    printf("undefined variable : %s\n", lhs->son->token.value.id);
                    return;
                }
                emit2(str, symbolTable[stIndex].base, symbolTable[stIndex].offset);
            } else
                emit0(sti);
            break;
        }

        // binary(arithmetic/relational/logical) operators
        case ADD: case SUB: case MUL: case DIV: case MOD:
        case EQ: case NE: case GT: case LT: case GE: case LE:
        case LOGICAL_AND: case LOGICAL_OR:
        {
            Node *lhs = ptr->son, *rhs = ptr->son->brother;

            // step 1: visit left operand
            if(lhs->noderep == nonterm) processOperator(lhs);
            else rv_emit(lhs);
            // step 2: visit right operand
            if(rhs->noderep == nonterm) processOperator(rhs);
            else rv_emit(rhs);
            // step 3: visit root
            switch(ptr->token.number) {
                case ADD: emit0(add); break;            // arithmetic operators
                case SUB: emit0(sub); break;
                case MUL: emit0(mult); break;
                case DIV: emit0(divop); break;
                case MOD: emit0(modop); break;
                case EQ: emit0(eq); break;              // relational operators
                case NE: emit0(ne); break;
                case GT: emit0(gt); break;
                case LT: emit0(lt); break;
                case GE: emit0(ge); break;
                case LE: emit0(le); break;
                case LOGICAL_AND: emit0(andop); break;  // logical operators
                case LOGICAL_OR: emit0(orop); break;
            }
            break;
        }

        // unary operators
        case UNARY_MINUS: case LOGICAL_NOT:
        {
            Node *p = ptr->son;

            if(p->noderep == nonterm) processOperator(p);
            else rv_emit(p);
            switch(ptr->token.number) {
                case UNARY_MINUS: emit0(neg); break;
                case LOGICAL_NOT: emit0(notop); break;
            }
            break;
        }

        // increment/decrement operators
        case PRE_INC: case PRE_DEC: case POST_INC: case POST_DEC:
        {
            Node *p = ptr->son; Node *q;
            int stIndex; // int amount = 1;
            if(p->noderep == nonterm) processOperator(p); // compute operand
            else rv_emit(p);

            q = p;
            while(q->noderep != terminal) q = q->son;
            if(!q || (q->token.number != tident)) {
                printf("increment/decrement operators can not be applied in expression\n");
                return;
            }
            stIndex = lookup(q->token.value.id);
            if(stIndex == -1) return;

            switch(ptr->token.number) {
                case PRE_INC:
                    emit0(incop);
                    // if(isOperation(ptr)) emit0(dup);
                    break;
                case PRE_DEC:
                    emit0(decop);
                    // if(isOperation(ptr)) emit0(dup);
                    break;
                case POST_INC:
                    // if(isOperation(ptr)) emit0(dup);
                    emit0(incop);
                    break;
                case POST_DEC:
                    // if(isOperation(ptr)) emit0(dup);
                    emit0(decop);
                    break;
            }
            if(p->noderep == terminal) {
                stIndex = lookup(p->token.value.id);
                if(stIndex == -1) return;
                emit2(str, symbolTable[stIndex].base, symbolTable[stIndex].offset);
            } else if(p->token.number == INDEX) { // compute index
                lvalue = 1;
                processOperator(p);
                lvalue = 0;
                emit0(swp);
                emit0(sti);
            }
            else printf("error in increment/decrement operators\n");
            break;
        }

        case INDEX:
        {
            Node *indexExp = ptr->son->brother;
            int stIndex;

            if(indexExp->noderep == nonterm) processOperator(indexExp);
            else rv_emit(indexExp);
            stIndex = lookup(ptr->son->token.value.id);
            if(stIndex == -1) {
                printf("undefined variable: %s\n", ptr->son->token.value.id);
                return;
            }
            emit2(lda, symbolTable[stIndex].base, symbolTable[stIndex].offset);
            emit0(add);
            if(!lvalue) emit0(ldi); // rvalue
            break;
        }

        case CALL:
        {
            Node *p = ptr->son;     // function name
            char *functionName;
            int stIndex; int noArguments;
            if(checkPredefined(p))  // predefined(Library) functions
                break;

            // handle for user function
            functionName = p->token.value.id;
            stIndex = lookup(functionName);
            if(stIndex == -1) break; // undefined function !!!
            noArguments = symbolTable[stIndex].width;

            emit0(ldp);
            p = p->brother;     // ACTUAL_PARAM
            while(p) {          // processing actual arguemtns
                if(p->noderep == nonterm) processOperator(p);
                else rv_emit(p);
                noArguments--;
                p = p->brother;
            }
            if(noArguments > 0)
                printf("%s: too few actual arguments", functionName);
            if(noArguments < 0)
                printf("%s: too many actual arguments", functionName);
            emitJump(call, ptr->son->token.value.id);
            break;
        }
    } // end switch
}

//////////////////////////////////////////////////////////////////////////// Statement
void genLabel(char *label)
{
    static int labelNum = 0;
    sprintf(label, "$$%d", labelNum++);
}

void emitLabel(char *label)
{
    int length;
    length = strlen(label);
    fprintf(ucodeFile, "%s", label);
    for(; length < LABEL_SIZE+1; length++)
        fprintf(ucodeFile, " ");
    fprintf(ucodeFile, "nop\n");
}

void processCondition(Node *ptr)
{
    if(ptr->noderep == nonterm) processOperator(ptr);
    else rv_emit(ptr);
}

void processStatement(Node *ptr)
{
    Node *p;
    int returnWithValue;

    switch(ptr->token.number) {
        case COMPOUND_ST:
            p = ptr->son->brother; // STAT_LIST
            p = p->son;
            while(p) {
                processStatement(p);
                p = p->brother;
            }
            break;
        case EXP_ST:
            if(ptr->son != NULL) processOperator(ptr->son);
            break;
        case RETURN_ST:
            if(ptr->son != NULL) {
                returnWithValue = 1;
                p = ptr->son;
                if(p->noderep == nonterm)
                    processOperator(p); // return value
                else rv_emit(p);
                emit0(retv);
            } else 
                emit0(ret);
            break;
        case IF_ST:
        {
            char label[LABEL_SIZE];

            genLabel(label);
            processCondition(ptr->son);             // condition part
            emitJump(fjp, label);
            processStatement(ptr->son->brother);    // true part
            emitLabel(label);
        }
        break;
        case IF_ELSE_ST:
        {
            char label1[LABEL_SIZE], label2[LABEL_SIZE];

            genLabel(label1); genLabel(label2);
            processCondition(ptr->son);             // condition part
            emitJump(fjp, label1);
            processStatement(ptr->son->brother);    // true part
            emitJump(ujp, label2);
            emitLabel(label1);
            processStatement(ptr->son->brother->brother); // false part
            emitLabel(label2);
        }
        break;
        case WHILE_ST:
        {
            char label1[LABEL_SIZE], label2[LABEL_SIZE];

            genLabel(label1); genLabel(label2);
            emitLabel(label1);
            processCondition(ptr->son);             // condition part
            emitJump(fjp, label2);
            processStatement(ptr->son->brother);    // loop body
            emitJump(ujp, label1);
            emitLabel(label2);
        }
        break;
        default:
            printf("not yet implemented.\n");
            break;
    } // end switch
}

//////////////////////////////////////////////////////////////////////////// function
void processSimpleParamVariable(Node *ptr, int typeSpecifier, int typeQualifier)
{
    Node *p = ptr->son;     // variable name(=> identifier)
    int stIndex, size;

    if(ptr->token.number != SIMPLE_VAR) printf("error in SIMPLE_VAR\n");

    size = typeSize(typeSpecifier);
    stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
            base, offset, 0, 0);
    offset += size;
}

void processArrayParamVariable(Node *ptr, int typeSpecifier, int typeQualifier)
{
    Node *p = ptr->son; // variable name(=> identifier)
    int stIndex, size;

    if(ptr->token.number != ARRAY_VAR) {
        printf("error in ARRAY_VAR\n");
        return;
    }

    size = typeSize(typeSpecifier);
    stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
            base, offset, width, 0);
    offset += size;
}

void processParamDeclaration(Node *ptr)
{
    int typeSpecifier, typeQualifier;
    Node *p, *q;

    if(ptr->token.number != DCL_SPEC) icg_error(4);

    // printf("processParamDeclaration\n");
    // step 1: process DCL_SPEC
    typeSpecifier = INT_TYPE; // default type
    typeQualifier = VAR_TYPE;
    p = ptr->son;
    while(p) {
        if(p->token.number == INT_NODE) typeSpecifier = INT_TYPE;
        else if(p->token.number == CONST_NODE)
            typeQualifier = CONST_TYPE;
        else { // AUTO, EXTERN, REGISTER, FLOAT, DOUBLE, SIGNED, UNSIGEND
            printf("not yet implemented\n");
            return;
        }
        p = p->brother;
    }

    // step 2: process SIMPLE_VAR, ARRAY_VAR
    p = ptr->brother; // SIMPLE_VAR or ARRAY_VAR
    switch(p->token.number) {
        case SIMPLE_VAR: // simple variable
            processSimpleParamVariable(p, typeSpecifier, typeQualifier);
            break;
        case ARRAY_VAR:  // array variable
            processArrayParamVariable(p, typeSpecifier, typeQualifier);
            break;
        default:
            printf("error in SIMPLE_VAR or ARRAY_VAR\n");
            break;
    }
}
void emitFunc(char *FuncName, int operand1, int operand2, int operand3)
{
    int label;
    label = strlen(FuncName);
    fprintf(ucodeFile, "%s", FuncName);
    for(; label < LABEL_SIZE+1; label++)
        fprintf(ucodeFile, " ");
    fprintf(ucodeFile, "proc %d %d %d\n", operand1, operand2, operand3);
}

void processFuncHeader(Node *ptr)
{
    int noArguments, returnType;
    int stIndex;
    Node *p;

    // printf("processFuncHeader\n");
    if(ptr->token.number != FUNC_HEAD)
        printf("error in processFuncHeader\n");
    // step 1: process the function return type
    p = ptr->son->son;
    while(p) {
        if(p->token.number == INT_NODE) returnType = INT_TYPE;
        else if(p->token.number == VOID_NODE) returnType = VOID_TYPE;
        else printf("invalid function return type\n");
        p = p->brother;
    }

    // step 2: count the number of formal parameters
    p = ptr->son->brother->brother; // FORMAL_PARA
    p = p->son; // PARAM_DCL

    noArguments = 0;
    while(p) {
        noArguments++;
        p = p->brother;
    }

    // step 3: insert the function name
    stIndex = insert(ptr->son->brother->token.value.id, returnType, FUNC_TYPE,
            1/*base*/, 0/*offset*/, noArguments/*width*/, 0/*initialValue*/);
    // if(!strcmp("main", functionName)) mainExist = 1;
}

void processFunction(Node *ptr)
{
    Node *p, *q;
    int sizeOfVar = 0;
    int numOfVar = 0;
    int stIndex;

    base++;
    offset = 1;

    if(ptr->token.number != FUNC_DEF) icg_error(4);

    // step 1: process formal parameters
    p = ptr->son->son->brother->brother; // FORMAL_PARA
    p = p->son; // PARAM_DCL
    while(p) {
        if(p->token.number == PARAM_DCL) {
            processParamDeclaration(p->son); // DCL_SPEC
            sizeOfVar++;
            numOfVar++;
        }
        p = p->brother;
    }

    // step 2: process the declaration part in function body
    p = ptr->son->brother->son->son; // DCL
    while(p) {
        if(p->token.number == DCL) {
            processDeclaration(p->son);
            q = p->son->brother;
            while(q) {
                if(q->token.number == DCL_ITEM) {
                    if(q->son->token.number == ARRAY_VAR) {
                        sizeOfVar += q->son->son->brother->token.value.num;
                    }
                    else {
                        sizeOfVar += 1;
                    }
                    numOfVar++;
                }
                q = q->brother;
            }
        }
        p = p->brother;
    }

    // step 3: emit the function start code
    p = ptr->son->son->brother;	// IDENT
    emitFunc(p->token.value.id, sizeOfVar, base, 2);
    for(stIndex = stTop-numOfVar; stIndex<stTop; stIndex++) {
        emit3(sym, symbolTable[stIndex].base, symbolTable[stIndex].offset, symbolTable[stIndex].width);
    }

    // step 4: process the statement part in function body
    p = ptr->son->brother;	// COMPOUND_ST
    processStatement(p);

    // step 5: check if return type and return value
    p = ptr->son->son;	// DCL_SPEC
    if(p->token.number == DCL_SPEC) {
        p = p->son;
        if(p->token.number == VOID_NODE)
            emit0(ret);
        else if(p->token.number == CONST_NODE) {
            if(p->brother->token.number == VOID_NODE)
                emit0(ret);
        }
    }

    // step 6: generate the ending codes
    emit0(endop);
    base--;
    symLevel++;
}

void genSym(int base)
{
}

void codeGen(Node *ptr)
{
    Node *p;
    int globalSize;

    initSymbolTable();
    // step 1: process the declaration part
    for(p=ptr->son; p; p=p->brother) {
        if(p->token.number == DCL) processDeclaration(p->son);
        else if(p->token.number == FUNC_DEF) processFuncHeader(p->son);
        else icg_error(3);
    }

    // dumpSymbolTable();
    globalSize = offset-1;
    // printf("size of global variables = %d\n", globalSize);

    genSym(base);

    // step 2: process the function part
    for(p=ptr->son; p; p=p->brother)
        if(p->token.number == FUNC_DEF) processFunction(p);
    // if(!mainExist) warningmsg("main does not exist");

    // step 3: generate code for starting routine
    //      bgn     globalSize
    //      ldp
    //      call    main
    //      end
    emit1(bgn, globalSize);
    emit0(ldp);
    emitJump(call, "main");
    emit0(endop);
}

int main(int argc, char* argv[])
{
	char fileName[30];
    Node *root;

    printf(" *** start of Mini C Compiler\n");
    if(argc != 2) {
        icg_error(1);
        exit(1);
    }
    strcpy(fileName, argv[1]);
    printf("   * source file name: %s\n", fileName);

    freopen(fileName, "r", stdin); // stdin redirect
    if((sourceFile = fopen(fileName, "r")) == NULL) {
        icg_error(2);
        exit(1);
    }
    astFile = fopen(strcat(strtok(fileName, "."), ".ast"),  "w");
    ucodeFile = fopen(strcat(strtok(fileName, "."), ".uco"),  "w");

    printf(" === start of Parser\n");
    root = parser();
    printTree(root, 0);
    printf(" === start of ICG\n");
    codeGen(root);
    printf(" *** end of Mini C Compiler\n");

    fclose(sourceFile);
    fclose(astFile);
    fclose(ucodeFile);
    return 0;
}