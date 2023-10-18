/********************************************************
 *         Code emitting functions                      *
 *                                       2003. 3. 18.   *
 ********************************************************/

#define numberOfOpcodes 40           // 35 + 4 + 1

typedef enum {
     notop, neg,   incop, decop, dup,  swp, add,  sub,   mult, divop,
	 modop, andop, orop,  gt,    lt,   ge,  le,   eq,    ne,
	 lod,   ldc,   lda,   ldi,   ldp,  str, sti,  ujp,   tjp,  fjp,
	 call,  ret,   retv,  chkh,  chkl, nop, proc, endop, bgn,  sym,
	 none
} opcode;

char *mnemonic[numberOfOpcodes] = {
     "notop", "neg",  "inc", "dec",  "dup", "swp",  "add", "sub",
	 "mult",  "div",  "mod", "and",  "or",  "gt",   "lt",  "ge",
	 "le",    "eq",   "ne",	 "lod",  "ldc", "lda",  "ldi", "ldp",
	 "str",   "sti",  "ujp", "tjp",  "fjp", "call", "ret", "retv",
	 "chkh",  "chkl", "nop", "proc", "end", "bgn",  "sym", "none"
};

void emit0(opcode op)
{
	fprintf (ucodeFile, "           ");
	fprintf (ucodeFile, "%-10s\n", mnemonic[op]);						//operator 출력
}

void emit1(opcode op, int num)
{
	fprintf (ucodeFile, "           ");
	fprintf (ucodeFile, "%-10s %5d\n", mnemonic[op], num);				//operator와 num 출력
}

void emit2(opcode op, int base, int offset)
{
  fprintf (ucodeFile, "           ");
  fprintf (ucodeFile, "%-10s %5d %5d\n", mnemonic[op], base, offset);	//operator와 base, offset 출력
}
void emit3(opcode op, int p1, int p2, int p3)
{
  fprintf (ucodeFile, "           ");
  fprintf (ucodeFile, "%-10s %5d %5d %5d\n", mnemonic[op], p1, p2, p3);	//operator와 p1, p2, p3 출력

}

void emitLabel(char *label)
{
	int i, noBlanks;

	fprintf (ucodeFile, "%s", label);//label 출력
	noBlanks = 12-strlen(label);
	for (i=1; i<noBlanks; ++i)
		fprintf (ucodeFile, " ");	//공백 출력
	fprintf (ucodeFile, "%-10s\n", mnemonic[nop]);	//nop 출력

}

void emitJump(opcode op, char *label)
{
  fprintf (ucodeFile, "           ");
  fprintf (ucodeFile, "%-10s %s\n", mnemonic[op], label);	//operator와 label 출력
}

void emitSym(int base, int offset, int size)
{
	fprintf (ucodeFile, "           ");
	fprintf (ucodeFile, "%-10s %5d %5d %5d\n", mnemonic[sym], base, offset, size);	//operator와 base, offset, size 출력
}

void emitFunc(char *label, int base, int offset, int size)
{
	int i, noBlanks;

	fprintf (ucodeFile, "%s", label);//label 출력
	noBlanks = 12-strlen(label);
	for (i=1; i<noBlanks; ++i)
		fprintf (ucodeFile, " ");	//공백 출력
	fprintf (ucodeFile, "%-10s", mnemonic[proc]); //proc 출력
	fprintf (ucodeFile, " ");
	fprintf (ucodeFile, "%5d %5d %5d\n", base, offset, size);	//base, offset, size 출력
}
