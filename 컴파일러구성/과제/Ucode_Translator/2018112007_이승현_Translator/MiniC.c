#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

FILE *astFile;                          // AST file
FILE *sourceFile;                       // miniC source program
FILE *ucodeFile;                        // ucode file

#include "Scanner.c"
#include "Parser.c"
#include "sdt.c"
#include "EmitCode.c"
#include "SymTab.c"

void codeGen(Node *ptr);
void processDeclaration(Node *ptr);
void processFuncHeader(Node *ptr);
void processFunction(Node *ptr);
void icg_error(int n);
void processSimpleVariable(Node *ptr, int typeSpecifier, int typeQualifier);
void processArrayVariable(Node *ptr, int typeSpecifier, int typeQualifier);
void processStatement(Node *ptr);
void processOperator(Node *ptr);
void processCondition(Node *ptr);
void rv_emit(Node *ptr);
void genLabel(char *label);
int checkPredefined(Node *ptr);
void set();
void reset();

int labelCount = 0;
int returnWithValue, lvalue;

int main(int argc, char *argv[])
{
	char fileName[30];
	Node *root;

	printf(" *** start of Mini C Compiler\n");
	if (argc != 2) {
		icg_error(1);
		exit(1);
	} //파일 입력을 제대로 받지 않은 경우 오류 메시지 출력 및 종료
	strcpy(fileName, argv[1]);
	printf("   * source file name: %s\n", fileName); //입력받은 minic 파일의 이름 출력

	if ((sourceFile = fopen(fileName, "r")) == NULL) {
		icg_error(2);
		exit(1);		//읽기 전용으로 파일을 읽을 수 없는 경우 에러메시지 출력 및 종료
	}
	astFile = fopen(strcat(strtok(fileName, "."), ".ast"), "w");	//ast 파일 출력
	ucodeFile = fopen(strcat(strtok(fileName, "."), ".uco"), "w");	//ucode 파일 출력

	printf(" === start of Parser\n");
    root = parser();	//parsing 진행 후 ast 구성
	printTree(root, 0);
	printf(" === start of ICG\n");
	codeGen(root);		//ast를 탐색하면서 ucode 생성
	printf(" *** end   of Mini C Compiler\n");
} // end of main

void codeGen(Node *ptr)
{
	Node *p;
	int globalSize;

	initSymbolTable();	//symbol table 초기화
	// first, process the declaration part
    for (p=ptr->son; p; p=p->brother) {
		if (p->token.number == DCL) 
		{
			processDeclaration(p->son);	//변수 선언 처리
			genSym(base);				//변수 명칭을 symbol table에 저장
		}
		else if (p->token.number == FUNC_DEF) processFuncHeader(p->son);	//함수 헤더 처리
		else icg_error(3);
	}

//	dumpSymbolTable();
	globalSize = offset-1;
//	printf("size of global variables = %d\n", globalSize);


	// second, process the function part
    for (p=ptr->son; p; p=p->brother)
		if (p->token.number == FUNC_DEF) processFunction(p);	//함수 정의 처리
//	if (!mainExist) warningmsg("main does not exist");

	// generate codes for start routine
	//          bgn    globalSize
	//			ldp
    //          call    main
	//          end
	emit1(bgn, globalSize);	//시작과 함께 전역 선언한 변수 및 함수의 크기 출력
	emit0(ldp);				//함수 파라미터 입력
	emitJump(call, "main");	//main 함수 call
	emit0(endop);			//함수 종료
}

void icg_error(int n)
{
	printf("icg_error: %d\n", n);	//입력받은 매개변수에 따라 에러메시지 출력
	//3:printf("A Mini C Source file must be specified.!!!\n");
	//"error in DCL_SPEC"
	//"error in DCL_ITEM"
}

void processDeclaration(Node *ptr)
{
	int typeSpecifier, typeQualifier;
	Node *p, *q;

	if (ptr->token.number != DCL_SPEC)	//현재 가리키는 포인터가 변수 타입이 아닌 경우 에러메시지 출력
		icg_error(4);

//	printf("processDeclaration\n");
	// 1. process DCL_SPEC
	typeSpecifier = INT_SPEC;		// default type
	typeQualifier = VAR_QUAL;		
	p = ptr->son;	
	while (p) {
		if (p->token.number == INT_NODE)    typeSpecifier = INT_SPEC;  			//int node일 떄 int type 변수
		else if (p->token.number == CONST_NODE)  typeQualifier = CONST_QUAL;	//const node일 떄 상수 변수
		else { // AUTO, EXTERN, REGISTER, FLOAT, DOUBLE, SIGNED, UNSIGNED
			   printf("not yet implemented\n");
		       return;
		}
		p = p->brother;	//형제 노드를 따라가면서 처리
	}

	// 2. process DCL_ITEM
	p = ptr->brother;
	if (p->token.number != DCL_ITEM)	//현재 가리키는 포인터가 변수 아이템이 아닌 경우 에러메시지 출력 
		icg_error(5);

	while (p) {
		q = p->son;    // SIMPLE_VAR or ARRAY_VAR

		switch (q->token.number) {
			case SIMPLE_VAR: {		// simple variable
				processSimpleVariable(q, typeSpecifier, typeQualifier);
				break;
			}
			case ARRAY_VAR: {		// one dimensional array
				processArrayVariable(q, typeSpecifier, typeQualifier);
				break;
			}
			default: printf("error in SIMPLE_VAR or ARRAY_VAR\n");
				break;
		} // end switch
		p = p->brother;
	} // end while
}


void processSimpleVariable(Node *ptr, int typeSpecifier, int typeQualifier)
{
	int stIndex, width, initialValue;
	int sign = 1;
	Node *p = ptr->son;          // variable name(=> identifier)
	Node *q = ptr->brother;      // initial value part

	if (ptr->token.number != SIMPLE_VAR)
		printf("error in SIMPLE_VAR\n");

	if (typeQualifier == CONST_QUAL) {		// constant type
		if (q == NULL) {
 		     printf("%s must have a constant value\n", ptr->son->token.value.id);
			 return;
		}
		if (q->token.number == UNARY_MINUS) {	//-가 붙은 경우
			sign = -1;	//sign 저장
			q = q->son;	//자손 노드로 이동
		}
		initialValue = sign * q->token.value.num;	//sign과 token value를 곱함

		stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
			             0/*base*/, 0/*offset*/, 0/*width*/, initialValue);	//symbol table에 저장
	} else {  // variable type
		width = 1;
		stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
			             base, offset, width, 0); //symbol table에 저장
		offset++; //offset 증가
	}
}

void processArrayVariable(Node *ptr, int typeSpecifier, int typeQualifier)
{
	int stIndex, size;
	Node *p = ptr->son;          // variable name(=> identifier)
	
	if (ptr->token.number != ARRAY_VAR) {
		printf("error in ARRAY_VAR\n");
		return;
	}
	if (p->brother == NULL)			// no size
		printf("array size must be specified\n");
	else size = p->brother->token.value.num; //형제 노드에서 size 값 가져옴

	stIndex = insert(p->token.value.id, typeSpecifier, typeQualifier,
		             base, offset, size, 0); //symbol table에 저장
	offset += size; //size만큼 offset 증가
}

void processFuncHeader(Node *ptr)
{
int noArguments, returnType;
	int stIndex;
	Node *p;

//	printf("processFuncHeader\n");
	if (ptr->token.number != FUNC_HEAD)
		printf("error in processFuncHeader\n");

	// 1. process the function return type
	p = ptr->son->son;
	while (p) {
		if (p->token.number == INT_NODE) returnType = INT_SPEC;			//int node인 경우 int type function
		else if (p->token.number == VOID_NODE) returnType = VOID_SPEC;	//void node인 경우 void type function
		else printf("invalid function return type\n");
		p = p->brother;
	}

	// 2. process formal parameters
	p = ptr->son->brother->brother;		// FORMAL_PARA
	p = p->son;							// PARAM_DCL
	
	noArguments = 0;
	while (p) {
		noArguments++;					//parameter의 개수 증가
		p = p->brother;					//형제 노드 탐색
	}

	// 3. insert the function name
	stIndex = insert(ptr->son->brother->token.value.id, returnType, FUNC_QUAL,
		             1/*base*/, 0/*offset*/, noArguments/*width*/, 0/*initialValue*/);
//	if (!strcmp("main", functionName)) mainExist = 1;
	//symbol table에 저장
}

void processFunction(Node *ptr)
{
	int paraType, noArguments = 0;
	int typeSpecifier, returnType;
	int p1, p2, p3;
	int stIndex = 0;
	Node *p, *q;
	char *functionName;
//	int i, j;

//	printf("processFunction\n");
	if (ptr->token.number != FUNC_DEF)
		printf("error in processFunction\n");

  // set symbol table for the function
	set();

	// 1. process formal parameters
	p = ptr->son->son->brother->brother; // FORMAL_PARA
    p = p->son; // PARAM_DCL
    while (p) {
		q = p->son->son;					// DCL_SPEC
		switch (q->token.number) {
			case INT_NODE : typeSpecifier = INT_SPEC;  break;	//int node이면 int type 변수
			default: printf("invalid function argument type\n");
		}
		q = p->son->brother;				// SIMPLE_VAR or ARRAY_VAR
		if (q->token.number == SIMPLE_VAR) paraType = 0;		//simple variable parameter type
	    else if (q->token.number == ARRAY_VAR) paraType = 1;	//array variable parameter type
		else printf("invalid argument passing\n");

		if (paraType == 0) paraType = 1;
		else if (paraType == 1){
			paraType = p->brother->token.value.num;	//형제 노드의 토큰 값을 parameter type으로 사용
		}
		stIndex = insert(q->son->token.value.id, typeSpecifier, PARAM_QUAL, base, offset, paraType, 0); //symbol table에 저장
		offset++;	//offset 증가
		noArguments++;	//parameter 등장 횟수 증가
		p = p->brother;	//형제 노드 탐색
	}
	// 2. process the declaration part in function body
	p = ptr->son->brother;			// COMPOUND_ST
	p = p->son->son;				// DCL
	// ...
	while (p) {
		processDeclaration(p->son);	//함수 선언부 처리	
		p = p->brother;				//형제 노드 탐색
	}

	// 3. emit the function start code
		// fname       proc      p1 p2 p3
		// p1 = size of local variables + size of arguments
		// p2 = block number
		// p3 = lexical level
	p1 = offset-1;	//지역 변수의 argument의 개수 
	p2 = p3 = base;	//base 값 저장
	functionName = ptr->son->son->brother->token.value.id; //함수명 저장
	emitFunc(functionName, p1, p2, p3);	//함수 명과 파라미터들 출력


//	dumpSymbolTable();
	genSym(base);	//symbol table에 저장된 변수들 출력

	// 4. process the statement part in function body
	p = ptr->son->brother->son->brother;	// STAT_LIST
	returnWithValue = 0;
	p = p->son;
	while(p)
	{
		processStatement(p);	//함수 body(statements) 처리
		p = p->brother;			//형제 노드 탐색
	}

	// 5. check if return type and return value
	stIndex = lookup(functionName); //함수 명이 저장된 symbol table의 index 반환
	if (stIndex == -1) return;		//함수가 저장되어 있지 않음
	returnType = symbolTable[stIndex].typeSpecifier;	//함수 반환형 저장
	if ((returnType == VOID_SPEC) && returnWithValue)
		printf("void return type must not return a value\n");
	if ((returnType == INT_SPEC) && !returnWithValue)
		printf("int return type must return a value\n");	//각 반환형 별 올바른 반환인지 검사

	// 6. generate the ending codes
	if (!returnWithValue) emit0(ret);	//반환 되는 값의 변화가 없음
	emit0(endop);						//end operator 출력

	// reset symbol table
	reset();							//symbol table 재설정
}

void processStatement(Node *ptr)
{
	Node *p;

	if (ptr == NULL) return;		// null statement

	switch (ptr->token.number) {
	case COMPOUND_ST:
		p = ptr->son->brother;		// STAT_LIST
		p = p->son;
		while (p) {
			processStatement(p);	//statements 처리
			p = p->brother;			//형제 노드 처리
		}
		break;
	case EXP_ST:
		if (ptr->son != NULL) processOperator(ptr->son); //expression 처리
		break;
	case RETURN_ST:
		if (ptr->son != NULL) {
			returnWithValue = 1;
			p = ptr->son;
			if (p->noderep == nonterm)
				processOperator(p); // return value
			else rv_emit(p);	//terminal에 저장된 값 return
			emit0(retv);		//retv 출력
		} else
			emit0(ret);			//ret 출력
		break;
	case IF_ST:
		{
			char label[LABEL_SIZE];

			genLabel(label);						//label 생성
			processCondition(ptr->son);				// condition
			emitJump(fjp, label);					//false일 때 jump
			processStatement(ptr->son->brother);	// true part
			emitLabel(label);						//label 출력
		}
		break;
	case IF_ELSE_ST:
		{
			char label1[LABEL_SIZE], label2[LABEL_SIZE];

			genLabel(label1);	//label 생성
			genLabel(label2);	//label 생성
			processCondition(ptr->son);				// condition
			emitJump(fjp, label1);					//false일 때 jump
			processStatement(ptr->son->brother);	// true part
			emitJump(ujp, label2);					//ture part 처리 후 if문 바깥으로 jump
			emitLabel(label1);						//label 출력
			processStatement(ptr->son->brother->brother);	// false part
			emitLabel(label2);								//label 출력
		}
		break;
	case WHILE_ST:
		{
			char label1[LABEL_SIZE], label2[LABEL_SIZE];

			genLabel(label1);	//label 생성
			genLabel(label2);	//label 생성
			emitLabel(label1);	//label 생성
			processCondition(ptr->son);				// condition
			emitJump(fjp, label2);					//false일 때 jump
			processStatement(ptr->son->brother);	// loop body
			emitJump(ujp, label1);					//조건부 파트로 jump
			emitLabel(label2);						//label 출력
		}
		break;
	default:
		printf("not yet implemented.\n");
		break;
	} //end switch
}

void genLabel(char *label)
{
	sprintf(label, "$$%d", labelCount++);	//label 생성
}

void processCondition(Node *ptr)
{
	if (ptr->noderep == nonterm) processOperator(ptr);	//조건부 파트 처리
		else rv_emit(ptr);
}

void rv_emit(Node *ptr)
{
	int stIndex;

	if (ptr->token.number == tnumber)		// number
		emit1(ldc, ptr->token.value.num);	// 숫자 출력
	else {									// identifier
		stIndex = lookup(ptr->token.value.id);
		if (stIndex == -1) return;
		if (symbolTable[stIndex].typeQualifier == CONST_QUAL)		// constant
			emit1(ldc, symbolTable[stIndex].initialValue);			//상수 변수 출력
		else if (symbolTable[stIndex].width > 1)					// array var
			emit2(lda, symbolTable[stIndex].base, symbolTable[stIndex].offset);	//배열의 첫 주소 출력
		else														// simple var
			emit2(lod, symbolTable[stIndex].base, symbolTable[stIndex].offset);	//변수 출력
	}
}

void processOperator(Node *ptr)
{
	int stIndex;

	if (ptr->noderep == terminal) {
		printf("illegal expression\n");
		return;
	}

	switch (ptr->token.number) {
	case ASSIGN_OP:
	{
		Node *lhs = ptr->son, *rhs = ptr->son->brother;

		// generate instructions for left-hane side if INDEX node.
		if (lhs->noderep == nonterm) {		// index variable
			lvalue = 1;
			processOperator(lhs);			//lhs 처리
			lvalue = 0;
		}
		// generate instructions for right-hane side
		if (rhs->noderep == nonterm) processOperator(rhs);	//rhs 처리
		else rv_emit(rhs);	//terminal 처리
		
		// generate a store instruction
		if (lhs->noderep == terminal) {		// simple variable
			stIndex = lookup(lhs->token.value.id);
			if (stIndex == -1) {
				printf("undefined variable : %s\n", lhs->token.value.id);
				return;
			}
			emit2(str, symbolTable[stIndex].base, symbolTable[stIndex].offset);	//str 출력
		} else								// array variable
			emit0(sti);						//sti 출력
		break;
	}
	case ADD_ASSIGN: case SUB_ASSIGN: case MUL_ASSIGN: case DIV_ASSIGN:
	case MOD_ASSIGN:
	{
		Node *lhs = ptr->son, *rhs = ptr->son->brother;
		int nodeNumber = ptr->token.number;

		ptr->token.number = ASSIGN_OP;
		if (lhs->noderep == nonterm) {	// code generation for left hand side
			lvalue = 1;
			processOperator(lhs);		//lhs 처리
			lvalue = 0;
		}
		ptr->token.number = nodeNumber;
		if (lhs->noderep == nonterm)	// code generation for repeating part
			processOperator(lhs);		//lhs 처리
			else rv_emit(lhs);			//terminal 처리
		if (rhs->noderep == nonterm) 	// code generation for right hand side
			processOperator(rhs);		//rhs 처리
			else rv_emit(rhs);			//terminal 처리

		switch (ptr->token.number) {
			case ADD_ASSIGN: emit0(add);	break;	//add 출력
			case SUB_ASSIGN: emit0(sub);	break;	//sub 출력
			case MUL_ASSIGN: emit0(mult);	break;	//mult 출력
			case DIV_ASSIGN: emit0(divop);	break;	//divop 출력
			case MOD_ASSIGN: emit0(modop);	break;	//modop 출력
		}
		if (lhs->noderep == terminal) {	// code generation for store code
			stIndex = lookup(lhs->token.value.id);	//변수 명 탐색
			if (stIndex == -1) {
				printf("undefined variable : %s\n", lhs->son->token.value.id);
				return;
			}
			emit2(str, symbolTable[stIndex].base, symbolTable[stIndex].offset); //str 출력
		} else
			emit0(sti); //sti 출력
		break;
	}
/*
	// logical operators(new computation of and/or operators: 2001.10.21)
	case AND: case OR:
		{
			Node *lhs = ptr->son, *rhs = ptr->son->brother;
			char label[LABEL_SIZE];

			genLabel(label);

			if (lhs->noderep == nonterm) processOperator(lhs);
				else rv_emit(lhs);
			emit0(dup);

			if (ptr->token.number == AND) emitJump(fjp, label);
			else if (ptr->token.number == OR) emitJump(tjp, label);

			// pop the first operand and push the second operand
			emit1(popz, 15);	// index 15 => swReserved7(dummy)
			if (rhs->noderep == nonterm) processOperator(rhs);
				else rv_emit(rhs);

			emitLabel(label);
			break;
		}
*/
	// arithmetic operators
	case ADD: case SUB: case MUL: case DIV: case MOD:
	// relational operators
	case EQ:  case NE: case GT: case LT: case GE: case LE:
	// logical operators
	case LOGICAL_AND: case LOGICAL_OR:
		{
			Node *lhs = ptr->son, *rhs = ptr->son->brother;

			if (lhs->noderep == nonterm) processOperator(lhs); //lhs 처리
				else rv_emit(lhs);							   //terminal 처리
			if (rhs->noderep == nonterm) processOperator(rhs); //rhs 처리
				else rv_emit(rhs);							   //terminal 처리
			switch (ptr->token.number) {
				case ADD: emit0(add);	break;			// arithmetic operators
				case SUB: emit0(sub);	break;
				case MUL: emit0(mult);	break;
				case DIV: emit0(divop);	break;
				case MOD: emit0(modop);	break;
				case EQ:  emit0(eq);	break;			// relational operators
				case NE:  emit0(ne);	break;
				case GT:  emit0(gt);	break;
				case LT:  emit0(lt);	break;
				case GE:  emit0(ge);	break;
				case LE:  emit0(le);	break;
				case LOGICAL_AND: emit0(andop);	break;	// logical operators
				case LOGICAL_OR : emit0(orop);	break;
			}
			break;
		}
	// unary operators
	case UNARY_MINUS: case LOGICAL_NOT:
		{
			Node *p = ptr->son;

			if (p->noderep == nonterm) processOperator(p); //value 계산
				else rv_emit(p);						   //terminal 처리
			switch (ptr->token.number) {
				case UNARY_MINUS: emit0(neg);			   //neg 출력
							      break;
				case LOGICAL_NOT: emit0(notop);			   //notop 출력
							      break;
			}
		break;
		}
	// increment/decrement operators
	case PRE_INC: case PRE_DEC: case POST_INC: case POST_DEC:
		{
			Node *p = ptr->son;
			Node *q;
			int stIndex;
			int amount = 1;

			if (p->noderep == nonterm) processOperator(p);		// compute value
				else rv_emit(p);								//terminal 처리

			q = p;
			while (q->noderep != terminal) q = q->son;			//value 얻어넴
			if (!q || (q->token.number != tident)) {
				printf("increment/decrement operators can not be applied in expression\n");
				break;
			}
			stIndex = lookup(q->token.value.id);			    //변수 명 탐색
			if (stIndex == -1) return;

			switch (ptr->token.number) {
				case PRE_INC: emit0(incop);						//incop 출력
//							  if (isOperation(ptr)) emit0(dup);
							  break;
				case PRE_DEC: emit0(decop);						//decop 출력
//							  if (isOperation(ptr)) emit0(dup);
							  break;
				case POST_INC:
//							   if (isOperation(ptr)) emit0(dup);
							   emit0(incop);					//incop 출력
							   break;
				case POST_DEC:
//							   if (isOperation(ptr)) emit0(dup);
							   emit0(decop);					//decop 출력
							   break;
			}
			if (p->noderep == terminal) {
				stIndex = lookup(p->token.value.id);			//변수 명 탐색
				if (stIndex == -1) return;
				emit2(str, symbolTable[stIndex].base, symbolTable[stIndex].offset); //str 출력
			} else if (p->token.number == INDEX) {				// compute index
				lvalue = 1;
				processOperator(p->son);						// compute value
				lvalue = 1;
				emit0(swp);										//주소가 밑에 오도록 swap
				emit0(sti);									    //sti 출력
			}
			else printf("error in prefix/postfix operator\n");
		break;
		}
	case INDEX:
		{
			Node *indexExp = ptr->son->brother;

			if (indexExp->noderep == nonterm) processOperator(indexExp);        //compute value
				else rv_emit(indexExp);										    //terminal 처리
			stIndex = lookup(ptr->son->token.value.id);							//변수 명 탐색
			if (stIndex == -1) {
				printf("undefined variable : %s\n", ptr->son->token.value.id);
				return;
			}
			emit2(lda, symbolTable[stIndex].base, symbolTable[stIndex].offset);	//lda 출력
			emit0(add);														    //add 출력 -> 배열 값 추출
			if (!lvalue) emit0(ldi);	// rvalue
			break;
		}
	case CALL:
	{
		Node *p = ptr->son;		// function name
		char *functionName;
		int stIndex;
		int noArguments;
		if (checkPredefined(p)) // library functions
			break;

		// handle for user function
		functionName = p->token.value.id;
		stIndex = lookup(functionName);
		if (stIndex == -1) break;			// undefined function !!!
		noArguments = symbolTable[stIndex].width;

		emit0(ldp);
		p = p->brother;			// ACTUAL_PARAM
		while (p) {				// processing actual arguments
			if (p->noderep == nonterm) processOperator(p); //compute parameter value
			else rv_emit(p);							   //terminal 처리
			noArguments--;								   //argument 개수 감소
			p = p->brother;
		}
		if (noArguments > 0) printf("%s: too few actual arguments", functionName);
		if (noArguments < 0) printf("%s: too many actual arguments", functionName);
		emitJump(call, ptr->son->token.value.id);          //call 출력
		break;
	}
	} //end switch
}

int checkPredefined(Node *ptr)
{
	char *functionName;
	int stIndex;

	functionName = ptr->token.value.id;
	if (!strcmp(functionName, "read")) {	// read procedure : call by address
		stIndex = lookup(ptr->brother->token.value.id); //함수 명 탐색
		if (stIndex == -1) return 1;
		emit0(ldp);											 //parameter load
		emit2(lda, symbolTable[stIndex].base, symbolTable[stIndex].offset);	//lda 출력
		emitJump(call, "read");								 //read로 jump
		return 1;
	}
	if (!strcmp(functionName, "write")) {	// write procedure
		emit0(ldp);							//parameter load
		if (ptr->brother->noderep == nonterm) processOperator(ptr->brother); //compute value
			else rv_emit(ptr->brother);										 //terminal 처리
		emitJump(call, "write");											 //write로 jump			
		return 1;
	}
	return 0;
}

void set()
{
	base++;		//base 증가
	offset = 1; //offset 초기화
}

void reset()
{
	base--; //base 감소
}