#include <stdio.h>

#define LABEL_SIZE 10
#define TABLE_SIZE 100

struct SymbolTable 
{
    char name[LABEL_SIZE];
    int typeSpecifier;
    int typeQualifier;
    int base;
    int offset;
    int width;
    int initialValue;
};//Symbol table 구조체 정의

typedef enum 
{
	NONE_SPEC, VOID_SPEC, INT_SPEC, CHAR_SPEC, FLOAT_SPEC
} typeSpecifier;//type specifier 정의

typedef enum 
{
	NONE_QUAL, CONST_QUAL, VAR_QUAL, FUNC_QUAL, PARAM_QUAL
} typeQualifier;//type qualifier 정의



struct SymbolTable symbolTable[TABLE_SIZE]; //Symbol table 구현
int st_top; //Symbol table의 top
int base, offset; //base와 offset

void initSymbolTable()
{
    base = 1;
    offset = 1;
    st_top = 0;
} //base와 offset, st_top 초기화

int insert(char *name, int typeSpecifier, int typeQualifier,
        int base, int offset, int width, int initialValue)
{
    struct SymbolTable *stptr = &symbolTable[st_top]; //symnol table 상단의 값 가져옴
    strcpy(stptr->name, name);  
    stptr->typeSpecifier = typeSpecifier;
    stptr->typeQualifier = typeQualifier;
    stptr->base = base;
    stptr->offset = offset;
    stptr->width = width;
    stptr->initialValue = initialValue;     //symbol table의 속성 복사 진행
   
    st_top++;                               //st_top의 값 1 증가
    return st_top;                          //st_top 반환
}

int lookup(char *name)
{
    int i;
    for(i=0; i<st_top; i++) 
        if(!strcmp(name, symbolTable[i].name))  //함수, 변수 명칭과 symbol table에 저장된 함수, 변수의 명칭이 같은지 확인
            return i;   //index 반환
    return -1;
}

void genSym(int base)
{
	for(int stIndex=0; stIndex <st_top; stIndex++) //s global variable definition
        if(symbolTable[stIndex].base == base)
            emitSym(symbolTable[stIndex].base, symbolTable[stIndex].offset, symbolTable[stIndex].width); 
            //입력받은 base 값과 같은 base 값을 가진 symbol table의 원소를 읽어낸다.
}