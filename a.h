
#ifndef _A_
#define _A_
typedef unsigned short int word;
typedef unsigned char byte;
struct Register {
	word AX;
	word BX;
	word CX;
	word DX;
	word SI;
	word DI;
	word BP;

	char* IP;
};

int Getlength(byte opcode);
int Instruction(byte* opcode);
bool Call_Instruction(int comNum, byte* opcode, int length, Register* p, byte* memory);
void Stosw(Register *p, byte* memory);
void Mov(Register* p, byte* code);
void Xor(Register* p, byte* code);
void Sub(Register* p, byte* code);
void Xchg(Register *p, byte* code);
void Add(Register *p, byte* code);
void Push_Pop(Register* p, byte* code);
void Inc(Register *p, byte* code);
void Dec(Register *p, byte* code);
void Swap(word &a, word &b);


#endif
