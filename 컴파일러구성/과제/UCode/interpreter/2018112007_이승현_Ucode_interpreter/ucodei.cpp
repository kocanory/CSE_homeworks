/*******************************************************************
 *                                                                 *
 *           Ucode Interpreter(C++ Version)                        *
 *                           1. Mini PASCAL Version : 2000.1.20    *
 *                           2. Mini C      Version : 2003.3.27    *
 *                                                                 *
 *******************************************************************/
#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

using namespace std;

const int MAXINSTR = 2000;
const int MAXLABELS = 300;
const int STACKSIZE = 1000;
const int LABELSIZE = 10;
const int NO_OPCODES = 41;

fstream inputFile;
ofstream outputFile;

enum opcode {
	notop, neg, incop, decop, dup, swp, add, sub, mult, divop,
	modop, andop, orop, gt, lt, ge, le, eq, ne,
	lod, ldc, lda, ldi, ldp, str, sti, ujp, tjp, fjp,
	call, ret, retv, chkh, chkl, nop, proc, endop, bgn, sym,
	dump, none
}; //operator마다 숫자를 부여합니다. 
   //이는 부여된 숫자를 이용해 opcodeName 배열에서 opcode 이름을 가져오려고 하기 때문입니다.  


char* opcodeName[NO_OPCODES] = {
	 "notop", "neg",  "inc", "dec",  "dup", "swp",  "add", "sub",
	 "mult",  "div",  "mod", "and",  "or",  "gt",   "lt",  "ge",
	 "le",    "eq",   "ne",	 "lod",  "ldc", "lda",  "ldi", "ldp",
	 "str",   "sti",  "ujp", "tjp",  "fjp", "call", "ret", "retv",
	 "chkh",  "chkl", "nop", "proc", "end", "bgn",  "sym", "dump",
	 "none"
};	//operator의 이름이 저장된 배열입니다.
	//위의 enum opcode에 저장된 opcode 숫자들을 이용해 접근하게 됩니다. 

int executable[NO_OPCODES] = {
	/*notop*/ 1, /*neg*/  1, /*inc*/ 1, /*dec*/  1, /*dup*/  1,
	/*swp*/   1, /*add*/  1, /*sub*/ 1, /*mult*/ 1, /*div*/  1,
	/*mod*/   1, /*and*/  1, /*or*/  1, /*gt*/   1, /*lt*/   1,
	/*ge*/    1, /*le*/   1, /*eq*/  1, /*ne*/   1, /*lod*/  1,
	/*ldc*/   1, /*lda*/  1, /*ldi*/ 1, /*ldp*/  1, /*str*/  1,
	/*sti*/   1, /*ujp*/  1, /*tjp*/ 1, /*fjp*/  1, /*call*/ 1,
	/*ret*/   1, /*retv*/ 1, /*chkh*/1, /*chkl*/ 1, /*nop*/  0,
	/*proc*/  1, /*end*/  0, /*bgn*/ 0, /*sym*/  0, /*dump*/ 1,
	/*none*/  0
}; //operator별로 실행가능 여부를 표현합니다.

int opcodeCycle[NO_OPCODES] = {
	/*notop*/  5, /*neg*/  5, /*inc*/  1, /*dec*/   1, /*dup*/    5,
	/*swp*/   10, /*add*/ 10, /*sub*/ 10, /*mult*/ 50, /*div*/  100,
	/*mod*/  100, /*and*/ 10, /*or*/  10, /*gt*/   20, /*lt*/    20,
	/*ge*/    20, /*le*/  20, /*eq*/  20, /*ne*/   20, /*lod*/    5,
	/*ldc*/    5, /*lda*/  5, /*ldi*/ 10, /*ldp*/  10, /*str*/    5,
	/*sti*/   10, /*ujp*/ 10, /*tjp*/ 10, /*fjp*/  10, /*call*/  30,
	/*ret*/   30, /*retv*/30, /*chkh*/ 5, /*chkl*/  5, /*nop*/    0,
	/*proc*/  30, /*end*/  0, /*bgn*/  0, /*sym*/   0, /*dump*/ 100,
	/*none*/   0
};	//operator 별로 cycle 횟수를 저장합니다.

int staticCnt[NO_OPCODES], dynamicCnt[NO_OPCODES];
enum { FALSE, TRUE };
enum procIndex { READPROC = -1, WRITEPROC = -2, LFPROC = -3 };

typedef struct {
	int opcode;
	int value1;
	int value2;
	int value3;
} Instruction; //instruction을 구조체로 정의합니다.
Instruction instrBuf[MAXINSTR];	//instruction을 저장할 buffer를 정의합니다.

void errmsg(string s, string s2 = "")
{
	cerr << "error !!!  " << s << ":  " << s2 << "\n"; //에러 메시지를 출력합니다.
	exit(1);
}

class UcodeiStack {
	int size;
	int sp;
	int* stackArray;
public:
	void push(int);
	int pop();
	int top() { return sp; }
	void spSet(int n) { sp = n; }
	void dump();
	int& operator[](int);
	UcodeiStack(int);
	~UcodeiStack() { delete[] stackArray; }
};	//코드를 실행하기 위한 stack을 구현합니다.

class Label {
	struct fixUpList {
		int instrAddress;
		struct fixUpList* next;
	};
	struct labelEntry {
		char labelName[LABELSIZE];
		int address;
		struct fixUpList* instrList;
	};
	struct labelEntry labelTable[MAXLABELS];
	int labelCnt;
	void addFix(struct fixUpList*, int);
public:
	void insertLabel(char[], int);
	void findLabel(char[], int);
	Label();
	virtual ~Label() { }
};	//instruction list와 label에 대한 작업 정의

class Assemble {
	int instrCnt;
	char lineBuffer[80];
	int bufIndex;
	Label labelProcess;
	char label[LABELSIZE];
	void getLabel();
	int getOpcode();
	int getOperand();
	void instrWrite();
public:
	void assemble();
	int startAddr;
	Assemble() {
		startAddr = 0;
		instrCnt = 0;
		bufIndex = 0;
		memset(lineBuffer, 0, sizeof(lineBuffer));
		memset(label, 0, sizeof(label));
	}
}; //operator와 operand, label을 가져와 어떤 피연산자와 연산을 하는지 정리하여 파일로 출력하는 작업 정의

class Interpret {
	UcodeiStack stack;
	int arBase;
	long int tcycle;
	long int exeCount;
	void predefinedProc(int);
	int findAddr(int);
	void statistic();
public:
	void execute(int);
	Interpret();
	virtual ~Interpret() { }
}; //입력받은 ucode 파일을 interpret하는 작업 담당

UcodeiStack::UcodeiStack(int size)
{
	stackArray = new int[size];	//size를 입력받아 stack을 생성합니다.
	sp = -1;
	push(-1); push(-1); push(-1); push(0);
	push(0);  push(0);  push(-1); push(1);	
}

void UcodeiStack::push(int value)
{
	if (sp == STACKSIZE) errmsg("push()", "Stack Overflow...");
	stackArray[++sp] = value;	//sp를 증가시키고 값을 저장합니다.
}

int UcodeiStack::pop()
{
	if (sp == 0) errmsg("pop()", "Stack Underflow...");
	return stackArray[sp--]; //마지막에 위치하는 값을 반환하고 sp를 감소시킵니다.
}

void UcodeiStack::dump()
{
	int i;

	cout << "stack dump : ";
	for (i = 0; i <= sp; ++i)
		cout << ' ' << i << ':' << stackArray[i]; //현재 stack에 저장되어 있는 값을 출력합니다.
	cout << '\n';
}

int& UcodeiStack::operator[](int index)
{
	return stackArray[index]; //index를 입력으로 받아 operator를 반환합니다.
}

Label::Label()
{
	labelCnt = 2;
	strcpy(labelTable[0].labelName, "read");	//0번째 위치에 read label을 저장합니다.
	labelTable[0].address = READPROC;			//read procedure 지정
	labelTable[0].instrList = NULL;				
	strcpy(labelTable[1].labelName, "write");	//1번째 위치에 write label을 저장합니다.
	labelTable[1].address = WRITEPROC;			//write procedure 지정
	labelTable[1].instrList = NULL;
	strcpy(labelTable[2].labelName, "lf");		//2번째 위치에 lf label을 지정합니다.
	labelTable[2].address = LFPROC;				//lf procedure 지정
	labelTable[2].instrList = NULL;
}

void Label::insertLabel(char label[], int value)
{
	struct fixUpList* ptr;
	int index;

	for (index = 0; (index <= labelCnt)
		&& strcmp(labelTable[index].labelName, label); index++);	//label 탐색
	labelTable[index].address = value;	//해당하는 label 주소 저장
	if (index > labelCnt) {//index가 label table을 벗어난 경우, 즉 label을 못찾은 경우
		strcpy(labelTable[index].labelName, label);	//label을 테이블에 복사
		labelCnt = index;	//label count 변경
		labelTable[index].instrList = NULL;
	}
	else {
		ptr = labelTable[index].instrList;	//현재 label에 지정된 instruction 지정
		labelTable[index].instrList = NULL;	
		while (ptr) {  // backpatching
			instrBuf[ptr->instrAddress].value1 = value; //instruction을 탐색하면서 값 변경
			ptr = ptr->next;
		}
	}
}

void Label::findLabel(char label[], int instr)
{
	struct fixUpList* ptr;
	int index;

	for (index = 0; (index <= labelCnt) &&
		strcmp(label, labelTable[index].labelName); index++); //label 탐색
	if (index > labelCnt) { // not found
		strcpy(labelTable[index].labelName, label); //label을 테이블에 복사
		labelCnt = index;	//label count 변경
		ptr = new fixUpList; //새 instructin list 생성
		if (ptr == NULL) errmsg("findLabel()", "Out of memory -- new");
		labelTable[index].instrList = ptr; //linstructin list 저장
		ptr->instrAddress = instr;	//포인터에 instruction 저장
		ptr->next = NULL;
	}
	else {                // found
		ptr = labelTable[index].instrList; //label에서 instruction 불러옴
		if (ptr) addFix(ptr, instr); //instruction list 추가
		else instrBuf[instr].value1 = labelTable[index].address; //label의 주소 저장
	}
}

void Label::addFix(struct fixUpList* prev, int instr)
{
	struct fixUpList* succ;

	while (prev->next) prev = prev->next; //instruction list 내 이동
	succ = new fixUpList;	//새 instruction list 생성
	if (succ == NULL) errmsg("addFix()", "Out of memory"); //생성되지 않았다면 에러메시지 출력
	succ->instrAddress = instr; //instruction 저장
	succ->next = NULL; //새 instructin list 뒤에 null 지정
	prev->next = succ; //뒤에 새 instruction list 연결
	//   delete succ;
}

void Assemble::getLabel()
{
	int i;

	while (isspace(lineBuffer[bufIndex])) bufIndex++; //공백 무시
	for (i = 0; i <= LABELSIZE && !isspace(label[i] = lineBuffer[bufIndex]);
		bufIndex++, i++); //공백 나올때까지 label 탐색
	label[i] = '\0'; //null 값 저장
}

int Assemble::getOpcode()
{
	char mnemonic[5];
	int index;

	// always start at 12-th column.
	bufIndex = 11;
	index = 0;
	while (index < 5 && !isspace(lineBuffer[bufIndex])) {
		mnemonic[index++] = lineBuffer[bufIndex++]; //mnemonic 배열에 버퍼 값 저장
	}
	mnemonic[index] = '\0';

	for (index = notop; index < none; index++)
		if (!strcmp(mnemonic, opcodeName[index])) break; //mnemonic 값과 operator 값을 비교

	if (index == none) errmsg("Illegal opcode", mnemonic); //operator를 찾지 못했다면 에러메시지 출력
	return index;
}

int Assemble::getOperand()
{
	int result;

	while (isspace(lineBuffer[bufIndex])) bufIndex++; //공백 무시
	result = 0;
	while (isdigit(lineBuffer[bufIndex]) && lineBuffer[bufIndex] != '\n')
		result = 10 * result + (lineBuffer[bufIndex++] - '0'); //버퍼에서 값을 꺼내 10진수의 값으로 복원
	return result; 
}

void Assemble::instrWrite()
{
	int i, j;
	char ch;

	inputFile.seekg(0, ios::beg);
	outputFile << "\n line       object           ucode  source program\n\n";
	for (i = 1; i <= instrCnt; i++)
	{
		outputFile.width(4);
		outputFile << i << "    ("; //line number 출력
		outputFile.width(2);
		outputFile << instrBuf[i].opcode; //operator number 출력
		j = instrBuf[i].opcode; //operator의 종류에 따라 operand 개수 다름
		if (j == chkl || j == chkh || j == ldc || j == bgn ||
			j == ujp || j == call || j == fjp || j == tjp) {
			outputFile.width(5);
			outputFile << instrBuf[i].value1 << "     "; //operand 출력
		}
		else if (j == lod || j == str || j == lda || j == sym || j == proc) {
			outputFile.width(5);
			outputFile << instrBuf[i].value1; //operand 1 출력
			outputFile.width(5);
			outputFile << instrBuf[i].value2; //operand 2 출력
		}
		else outputFile << "          ";
		outputFile << ")     ";
		while ((ch = inputFile.get()) != '\n')  // copy input to output
			outputFile.put(ch); //ucode 복사 및 출력
		outputFile.put('\n');
	}
	outputFile << "\n\n   ****    Result    ****\n\n";
}

void Assemble::assemble()
{
	int done = FALSE;
	int end = FALSE;
	int n;

	cout << " == Assembling ... ==" << '\n';
	while (!inputFile.eof() && !inputFile.fail() && !end) {
		instrCnt++; bufIndex = 0;
		inputFile.getline(lineBuffer, sizeof(lineBuffer)); //파일을 한 줄씩 입력받음
		if (!isspace(lineBuffer[0])) {
			getLabel(); //label을 얻어옵니다.
			labelProcess.insertLabel(label, instrCnt); //label process에 label과 instruction count를 저장합니다.
		}
		instrBuf[instrCnt].opcode = n = getOpcode(); //operator 값 불러옵니다.
		staticCnt[n]++;
		switch (n) {
		case chkl:
		case chkh:
		case ldc:
			instrBuf[instrCnt].value1 = getOperand(); //operand 하나 필요
			break;
		case lod:
		case str:
		case lda:
		case sym:
			instrBuf[instrCnt].value1 = getOperand();
			instrBuf[instrCnt].value2 = getOperand(); //operand 둘 필요
			break;
		case proc:
			instrBuf[instrCnt].value1 = getOperand();
			instrBuf[instrCnt].value2 = getOperand();
			instrBuf[instrCnt].value3 = getOperand(); //operand 셋 필요
			break;
		case bgn:
			instrBuf[instrCnt].value1 = getOperand(); //operand 하나 필요
			startAddr = instrCnt; //시작 주소 지정
			done = TRUE;
			break;
		case ujp:
		case call:
		case fjp:
		case tjp:
			getLabel(); //label 불러옵니다.
			labelProcess.findLabel(label, instrCnt); //해당하는 label을 찾습니다.
			break;
		case endop:
			if (done) end = TRUE; 
		}
	}
	instrWrite();
}

Interpret::Interpret()
	: stack(STACKSIZE) //stack 초기화
{
	arBase = 4; //base 값 초기화
	tcycle = 0; //사이클 수 초기화
	exeCount = 0; //실행 수 초기화
}

int Interpret::findAddr(int n)
{
	int temp;

	if (!instrBuf[n].value1) //값이 존재하지 않는 경우
		errmsg("findAddr()", "Lexical level is zero ..."); 
	else if (instrBuf[n].value2 < 1) //값이 음수를 가지는 경우
		errmsg("findAddr()", "Negative offset ...");
	for (temp = arBase; instrBuf[n].value1 != stack[temp + 3]; temp = stack[temp]) {
		if ((temp > STACKSIZE) || (temp < 0)) //stack의 범위를 벗어난 경우
			cout << "Lexical level :  " << instrBuf[n].value1 << ' '
			<< "Offset        :  " << instrBuf[n].value2 << '\n';
	}
	return (temp + instrBuf[n].value2 + 3);
}

void Interpret::predefinedProc(int procIndex)
{
	static ifstream dataFile;
	static int readFirst = TRUE;

	//   char dataFileName[20];
	int data, temp;

	if (procIndex == READPROC)           // read
	{
		/*
		if (readFirst) {
			 cout << "\nEnter Data File Name : ";
			 cin >> dataFileName;
			 dataFile.open(dataFileName, ios::in);
			 if (dataFileName == NULL)
				   errmsg("checkPredefined()", "Data file open error ...");
			 readFirst = FALSE;
		}
		dataFile >> data;
		*/
		cin >> data; //데이터 입력
		temp = stack.pop(); //stack에서 값을 가져옴
		stack[temp] = data; //해당되는 자리에 입력한 값 저장
		stack.spSet(stack.top() - 4); //sp 조정
	}
	else if (procIndex == WRITEPROC) {   // write
		temp = stack.pop(); //stack에서 값을 가져옴
		cout << ' ' << temp; //가져온 값 출력
		outputFile << ' ' << temp; //가져온 값 파일에 출력
		stack.spSet(stack.top() - 4); //sp 조정
	}
	else if (procIndex == LFPROC) {    // lf : line feed
		outputFile.put('\n');//아랫줄로 이동
		cout << "\n";
	}
}

void Interpret::statistic()
{
	int i, opcode;

	outputFile << "\n\n\n             " << "##### Statistics #####\n";
	outputFile << "\n\n    ****  Static Instruction Counts  ****\n\n";
	for (i = 0, opcode = notop; opcode < none; opcode++) {
		if (staticCnt[opcode] != 0) {
			outputFile.width(5);
			outputFile.setf(ios::left, ios::adjustfield);
			outputFile << opcodeName[opcode] << "  =  "; //operator 출력
			outputFile.width(5);
			outputFile.setf(ios::left, ios::adjustfield);
			outputFile << staticCnt[opcode] << "   "; //static count 출력
			i++;
			if (i % 4 == 0) outputFile.put('\n');
		}
	}
	outputFile << "\n\n    ****  Dynamic instruction counts  ****\n\n";
	for (i = 0, opcode = notop; opcode < none; opcode++) {
		if (dynamicCnt[opcode] != 0) {
			outputFile.width(5);
			outputFile.setf(ios::left, ios::adjustfield);
			outputFile << opcodeName[opcode] << "  =  "; //operator 출력
			outputFile.width(8);
			outputFile.setf(ios::left, ios::adjustfield);
			outputFile << dynamicCnt[opcode] << "  "; //dynamic count 출력
			i++;
			if (i % 4 == 0) outputFile << "\n"; //operator 4개 단위로 라인 출력
		}
	}
	outputFile << "\n\n Executable instruction count  =   " << exeCount; //instruction count을 파일에 출력
	outputFile << "\n\n Total execution cycle         =   " << tcycle;	 //총 cycle 횟수를 파일에 출력
	outputFile << "\n";
}

void Interpret::execute(int startAddr)
{
	int parms = 0;
	int temp, temp1;
	int pc;

	pc = startAddr;
	cout << " == Executing ...  ==\n";
	cout << " == Result         ==\n";
	while (pc >= 0)
	{
		dynamicCnt[instrBuf[pc].opcode]++; //dynamic count 증가
		if (executable[instrBuf[pc].opcode]) exeCount++; //excutable한 연산이라면 count 증가
		tcycle += opcodeCycle[instrBuf[pc].opcode]; //사이클 수 증가

		switch (instrBuf[pc].opcode)
		{
		case notop:
			stack.push(!stack.pop()); //not 연산한 값을 push
			break;
		case neg:
			stack.push(-stack.pop()); //negation 연산한 값을 push
			break;
		case add:
			stack.push(stack.pop() + stack.pop()); //값 두개를 pop한 후 더하여 push
			break;
		case divop:
			temp = stack.pop(); //나눌 수를 가져옴
			if (temp == 0) errmsg("execute()", "Divide Zero ..."); //0으로 나눌 수 업으므로 에러
			stack.push(stack.pop() / temp); //값을 pop한 후 미리 가져온 값으로 나누고 push
			break;
		case sub:
			temp = stack.pop(); //뺄 수를 가져옴
			stack.push(stack.pop() - temp); //값을 pop한 후 앞에서 가져온 값으로 빼고 push
			break;
		case mult:
			stack.push(stack.pop() * stack.pop()); //값 두개를 가져와 곱하고 push
			break;
		case modop:
			temp = stack.pop(); //나눌 수를 가져옴
			stack.push(stack.pop() % temp);//앞서 가져온 값으로 나누고 나온 나머지를 push
			break;
		case andop:
			stack.push(stack.pop() & stack.pop()); //두 값을 가져와 and 연산 후 push
			break;
		case orop:
			stack.push(stack.pop() | stack.pop()); //두 값을 가져와 or 연산 후 push
			break;
		case gt:
			temp = stack.pop(); //비교할 값을 가져옴
			stack.push(stack.pop() > temp); //비교할 값이 더 큰지 계산 후 push
			break;
		case lt:
			temp = stack.pop(); //비교할 값 가져옴
			stack.push(stack.pop() < temp); //비교할 값이 더 작은지 계산 후 push
			break;
		case ge:
			temp = stack.pop(); //비교할 값 가져옴
			stack.push(stack.pop() >= temp); //비교할 값이 더 크거나 같은지 계산 후 push
			break;
		case le:
			temp = stack.pop(); //비교할 값 가져옴
			stack.push(stack.pop() <= temp); //비교할 값이 더 작거나 같은지 게산 후 push
			break;
		case eq:
			temp = stack.pop(); //비교할 값 가져옴
			stack.push(stack.pop() == temp); //비교할 값과 같은지 계산 후 push
			break;
		case ne:
			temp = stack.pop(); //비교할 값 가져옴
			stack.push(stack.pop() != temp); //비교할 값과 다른지 계산 후 push
			break;
		case swp:
			temp = stack.pop(); //값을 가져옴
			temp1 = stack.pop(); //또 다른 값을 가져옴
			stack.push(temp);
			stack.push(temp1); //서로 순서를 바꾸어 push
			break;
		case lod:			// load
			stack.push(stack[findAddr(pc)]); //pc값으로 주소를 찾아 stack에서 값을 가져와 push
			break;
		case ldc:			// load constant
			stack.push(instrBuf[pc].value1); //instruction 버퍼에서 해당되는 값을 push
			break;
		case lda:			// load address
			stack.push(findAddr(pc)); //주소를 push
			break;
		case str:			// store
			stack[findAddr(pc)] = stack.pop(); //stack에서 값을 가져와 해당되는 주소에 저장
			break;
		case ldi:			// load indirect
			if ((stack.top() <= 0) || (stack.top() > STACKSIZE))
				errmsg("execute()", "Illegal ixa instruction ..."); //stack에서 가져올 값이 stack의 범위 안에 있는지 확인
			temp = stack.pop(); //값을 가져옴
			stack.push(temp); //값을 push
			stack[stack.top()] = stack[temp]; //앞서 가져온 값을 index로 하여 값을 가져와 stack에 저장
			break;
		case sti:			// store indirect
			temp = stack.pop(); //stack에서 값을 가져옴
			stack[stack.pop()] = temp; //stack에서 값을 또 가져와 그 값을 index로 하고, 앞서 가져온 값을 그 위치에 저장
			break;
		case ujp:
			pc = instrBuf[pc].value1 - 1; //이전 pc 값으로 이동
			break;
		case tjp:
			if (stack.pop()) pc = instrBuf[pc].value1 - 1; //stack에서 가져온 값이 0보다 크다면 pc 값 변화
			break;
		case fjp:
			if (!stack.pop()) pc = instrBuf[pc].value1 - 1; //stack에서 가져온 값이 0이라면 pc 값 변화
			break;
		case chkh:
			temp = stack.pop();//stack에서 값을 가져옴
			if (temp > instrBuf[pc].value1) //현재 pc에 저장된 값보다 크다면
				errmsg("execute()", "High check failed..."); //에러 메시지 출력
			stack.push(temp); //다시 stack에 push
			break;
		case chkl:
			temp = stack.pop(); //stack에서 값을 가져옴
			if (temp < instrBuf[pc].value1) //현재 pc에 저장된 값보다 작다면
				errmsg("execute()", "Low check failed..."); //에러 메시지 출력
			stack.push(temp); //다시 stack에 push
			break;
		case ldp:
			parms = stack.top() + 1;				// sp 저장
			stack.spSet(stack.top() + 4);			// 파라미터 구성
			break;
		case call:
			if ((temp = instrBuf[pc].value1) < 0) predefinedProc(temp);
			else {
				stack[parms + 2] = pc + 1;	// 복귀할 주소 저장
				stack[parms + 1] = arBase;		// dynamic chain
				arBase = parms;				// base값 변경
				pc = instrBuf[pc].value1 - 1;// 함수가 저장된 위치로 이동	
			}
			break;
		case retv:
			temp = stack.pop();
		case ret:
			stack.spSet(arBase - 1);				// sp 조정
			if (instrBuf[pc].opcode == retv)		// 반환할 값을 push
				stack.push(temp);
			pc = stack[arBase + 2] - 1;				// 복귀 주소 복구
			arBase = stack[arBase + 1];			// base값 복구
			break;
		case proc:
			// value 1: (size of paras + size of local vars)
			// value 2: block number(base)
			// value 3: static level => lexical level(staic chain)
			stack.spSet(arBase + instrBuf[pc].value1 + 3); //sp 조정
			stack[arBase + 3] = instrBuf[pc].value2;  //현재 pc에 저장된 값을 stack에 저장
			for (temp = stack[arBase + 1]; stack[temp + 3] !=
				instrBuf[pc].value3 - 1; temp = stack[temp]);
			stack[arBase] = temp;			// static chain
			break;
		case endop:
			pc = -2; //pc가 -2로 변화 -> execution 종료
			break;
		case bgn:
			stack.spSet(stack.top() + instrBuf[pc].value1); //stack의 top 값과 현재 pc에 저장되어 있는 값으로 sp 결정
			break;
		case nop:
		case sym:
			break;
			/* augmented operation codes */
		case incop:	/* increment operation */
			temp = stack.pop();
			stack.push(++temp); //값을 1 증가 시킨 후 push
			break;
		case decop:	/* decrement operation */
			temp = stack.pop();
			stack.push(--temp); //값을 1 감소 시킨 후 push
			break;
		case dup:		/* duplicate */
			temp = stack.pop();
			stack.push(temp); 
			stack.push(temp); //동일한 값을 두 번 push 
			break;
		case dump:	/* dump */
			stack.dump(); //현재 stack에 저장된 값을 출력
			break;
		}
		pc++; //pc값 증가
	}
	cout << '\n';
	statistic();
}

int main(int argc, char* argv[])
{
	Assemble sourceProgram;
	Interpret binaryProgram;

	if (argc != 3) errmsg("main()", "Wrong number of arguments");

	inputFile.open(argv[1], ios::in);
	if (!inputFile) errmsg("cannot open input file", argv[1]);

	outputFile.open(argv[2], ios::out);
	// if (!outputFile) errmsg("cannot open output file", argv[2]);

	sourceProgram.assemble(); //입력받은 ucode파일에서 operator와 operand를 하나로 묶습니다.
	binaryProgram.execute(sourceProgram.startAddr); //assemble한 program을 실행하고 결과 값을 출력합니다.

	inputFile.close();
	outputFile.close();
}
