#include <iostream>

#include "a.h"

word* Stack = new word[200];

int Getlength(byte Opcode) 
{
	switch (Opcode) {
		//stosw
	case 0xAB://stosw
		return 1;
		break;
		//Dec
	case 0x48://Dec ax
		return 1;
		break;
	case 0x4d://Dec bP
		return 1;
		break;
	case 0x4b://Dec bx
		return 1;
		break;
	case 0x49://Dec cx
		return 1;
		break;
	case 0x4f://Dec di
		return 1;
		break;
	case 0x4a://Dec dx 
		return 1;
		break;
	case 0x4e://Dec si
		return 1;
		break;
	/*case 0x4c://Dec sP
		return 1;
		break;*/
		//Inc
	case 0x40://Inc ax
		return 1;
		break;
	case 0x41://Inc cx
		return 1;
		break;
	case 0x42://Inc dx
		return 1;
		break;
	case 0x43://Inc bx
		return 1;
		break;
	/*case 0x44://Inc sP
		return 1;
		break;*/
	case 0x45://Inc bP
		return 1;
		break;
	case 0x46://Inc si
		return 1;
		break;
	case 0x47://Inc di
		return 1;
		break;
		//PoP
	case 0x58://PoP ax 
		return 1;
		break;
	case 0x59://PoP cx
		return 1;
		break;
	case 0x5a://PoP dx 
		return 1;
		break;
	case 0x5b://PoP bx
		return 1;
		break;
	case 0x5c://PoP sP 
		return 1;
		break;
	case 0x5d://PoP bP 
		return 1;
		break;
	case 0x5e://PoP si 
		return 1;
		break;
	case 0x5f://PoP di 
		return 1;
		break;
		//Push
	case 0x50://Push ax 
		return 1;
		break;
	case 0x51://Push cx 
		return 1;
		break;
	case 0x52://Push dx
		return 1;
		break;
	case 0x53://Push bx 
		return 1;
		break;
	case 0x54://Push sP 
		return 1;
		break;
	case 0x55://Push bP 
		return 1;
		break;
	case 0x56://Push si
		return 1;
		break;
	case 0x57://Push di
		return 1;
		break;
		//mov
	case 0xb8://mov AX, iw
		return 3;
		break;
	case 0xb9://mov CX, iw
		return 3;
		break;
	case 0xba://mov DX, iw
		return 3;
		break;
	case 0xbb://mov BX, iw
		return 3;
		break;
	/*case 0xbc://mov SP, iw
		return 3;
		break;*/
	case 0xbd://mov BP, iw
		return 3;
		break;
	case 0xbe://mov SI, iw
		return 3;
		break;
	case 0xbf://mov DI, iw
		return 3;
		break;
	case 0x8b://mov rw, rmw
		return 2;
		break;
		//xor //81-6
	case 0x33://xor rw, rmw
		return 2;
		break;
	case 0x81://xor rmw, iw
		return 4;
		break;
	case 0x35://xor AX, iw
		return 3;
		break;
		//xchg 
	case 0x87://xchg  rmw, rw
		return 2;
		break;
		//Add //81-0
	case 0x05://Add AX, iw
		return 3;
		break;
	case 0x03://Add rw, rmw
		return 2;
		break;
		//sub //81-5
	case 0x2b://sub rw, rmw
		return 2;
		break;
	case 0x2d://sub AX, iw
		return 3;
		break;
	default:
		return -1;
		break;
	}
}
int Mask2(byte A) 
{
	return A & 0b00000111;
}
int Mask1(byte a) 
{
	return a & 0b00111000;
}
word* Operand2 (byte A, Register* P) 
{
	byte B = Mask2(A);
	word* Ptr;
	Ptr = NULL;
	switch (B)
	{
	case 0b00000000:
		Ptr = &(P->AX);//AX
		break;
	case 0b00000001:
		Ptr = &(P->CX);//CX
		break;
	case 0b00000010:
		Ptr = &(P->DX);//DX
		break;
	case 0b00000011:
		Ptr = &(P->BX);//BX
		break;
	case 0b00000101:
		Ptr = &(P->BP);//BP
		break;
	case 0b00000110:
		Ptr = &(P->SI);//SI
		break;
	case 0b00000111:
		Ptr = &(P->DI);//DI
		break;
	default:
		break;
	}
	return Ptr;
}

word* Operand1(byte A, Register* P) 
{
	word* Ptr;
	Ptr = NULL; 
	byte B = Mask1(A);
	switch (B)
	{
	case 0b00000000:
		Ptr = &(P->AX);//AX
		break;
	case 0b00001000:
		Ptr = &(P->CX);//CX
		break;
	case 0b00010000:
		Ptr = &(P->DX);//DX
		break;
	case 0b00011000:
		Ptr = &(P->BX);//BX
		break;
	case 0b00101000:
		Ptr = &(P->BP);//BP
		break;
	case 0b00110000:
		Ptr = &(P->SI);//SI
		break;
	case 0b00111000:
		Ptr = &(P->DI);//DI
		break;
	default:
		break;
	}
	return Ptr;
}

void Stosw(Register *P, byte* Memory) 
{
	word Val = P->AX;
	word Adres = P->DI;
	byte Byte1 = Val % 256;
	byte Byte2 = (Val - Byte1) / 256;
	Memory[Adres] = Byte1;
	Memory[Adres + 1] = Byte2;
	P->DI += 2;


}
void Mov(Register* P, byte* Code) 
{
	if (*Code == 0xb8) 
	{
		P->AX = (Code[2] * 16 * 16 + Code[1]);
	}
	else if (*Code == 0xb9) {
		P->CX = (Code[2] * 16 * 16 + Code[1]);
	}
	else if (*Code == 0xba) {
		P->DX = (Code[2] * 16 * 16 + Code[1]);
	}
	else if (*Code == 0xbb) {
		P->BX = (Code[2] * 16 * 16 + Code[1]);
	}
	else if (*Code == 0xbd) {
		P->BP = (Code[2] * 16 * 16 + Code[1]);
	}
	else if (*Code == 0xbe) {
		P->SI = (Code[2] * 16 * 16 + Code[1]);
	}
	else if (*Code == 0xbf) {
		P->DI = (Code[2] * 16 * 16 + Code[1]);
	}
	else if (*Code == 0x8b) {
		*Operand1(*(Code + 1), P) = *Operand2(*(Code + 1), P);
	}
		

}
void Xor(Register *P, byte* Code)
{
	word result;
	if (*Code == 0x81)
{
		result = *Operand2(*(Code + 1), P) ^ ((*(Code + 2)) + (*(Code + 3) * 16 * 16));
		*Operand2(*(Code + 1), P) = result;
	}//xor rw, iw
	else if (*Code == 0x33) {
		result = *Operand1(*(Code + 1), P) ^ *Operand2(*(Code + 1), P);
		*Operand1(*(Code + 1), P) = result;
	}//xor rw, rmw
	else if (*Code == 0x35) {
		P->AX ^= (unsigned char)(*(Code + 2) * 16 * 16) + (unsigned char)(*(Code + 1));
	}//xor AX, iw
	else {
		std::cout << "error xor";

	}

}

void Push_Pop(Register* P, byte* Code) 
{
	static word* SP = &Stack[199];
	switch (*Code) 
	{
	case 0x50://Push ax 
		SP--;
		*SP = P->AX;
		break;
	case 0x51://Push cx 
		SP--;
		*SP = P->CX;
		break;
	case 0x52://Push dx
		SP--;
		*SP = P->DX;
		break;
	case 0x53://Push bx 
		SP--;
		*SP = P->BX;
		break;
	/*case 0x54://Push sP 
		P->SP--;
		*P->SP = P->AX;
		break;*/
	case 0x55://Push bP 
		SP--;
		*SP = P->BP;
		break;
	case 0x56://Push si
		SP--;
		*SP = P->SI;
		break;
	case 0x57://Push di
		SP--;
		*SP = P->DI;
		break;


	case 0x58://PoP ax 
		P->AX = *SP;
		SP++;
		break;
	case 0x59://PoP cx
		P->CX = *SP;
		SP++;
		break;
	case 0x5a://PoP dx 
		P->DX = *SP;
		SP++;
		break;
	case 0x5b://PoP bx
		P->BX = *SP;
		SP++;
		break;
	/*case 0x5c://PoP sP 
		return 1;
		break;*/
	case 0x5d://PoP bP 
		P->BP = *SP;
		SP++;
		break;
	case 0x5e://PoP si 
		P->SI = *SP;
		SP++;
		break;
	case 0x5f://PoP di 
		P->DI = *SP;
		SP++;
	default:
		break;
	}
}

void Sub(Register *P, byte* Code) 
{
	word result;
	if (*Code == 0x81) 
	{
		result = *Operand2(*(Code + 1), P) - ((*(Code + 2) + (*(Code + 3) * 16 * 16)));
		*Operand2(*(Code + 1), P) = result;
	}//sub rw, iw
	else if (*Code == 0x2b) 
	{
		result = *Operand1(*(Code + 1), P) - *Operand2(*(Code + 1), P);
		*Operand1(*(Code + 1), P) = result;
	}//sub rw, rmw
	else if (*Code == 0x2d) 
	{
		P->AX -= (*(Code + 1) + (*(Code + 2) * 16 * 16));
	}//sub AX, iw
	else 
	{
		std::cout << "error sub";
	}
}
void Xchg(Register *P, byte* Code) 
{
	word *P1 = Operand1(*(Code + 1), P);
	word *P2 = Operand2(*(Code + 1), P);
	Swap(*P1, *P2);
}
void Swap(word &A, word &B) 
{
	word Temp = A;
	A = B;
	B = Temp;
}
void Add(Register* P, byte* Code) 
{
	word result;
		if (*Code == 0x81) 
		{
			result = *Operand2(*(Code + 1), P) + (*(Code + 2)) + (*(Code + 3) * 16 * 16);
			*Operand2(*(Code+1), P) = result;
		}//Add rw, iw
		else if (*Code == 0x03) 
		{
			result = *Operand1(*(Code + 1), P) + *Operand2(*(Code + 1), P);
			*Operand1(*(Code + 1), P) = result;
		}//Add rw, rmw
		else if (*Code == 0x05) 
		{
			P->AX += (*(Code + 2) * 16 * 16) + (*(Code + 1));
		}
		else 
		{
			std::cout << "error Add";
		}

}

void Inc(Register *P, byte* Code) 
{
	switch (*Code) 
	{
	case 0x48://Inc ax
		P->AX++;
		break;
	case 0x49://Inc cx
		P->CX++;
		break;
	case 0x4a://Inc dx
		P->DX++;
		break;
	case 0x4b://Inc bx
		P->BX++;
		break;
	/*case 0x44://Inc sP
		return 1;
		break;*/
	case 0x4d://Inc bP
		P->BP++;
		break;
	case 0x4e://Inc si
		P->SI++;
		break;
	case 0x4f://Inc di
		P->DI++;
		break;
	default:
		break;
	}
}
void Dec(Register*P, byte* Code) 
{
	switch (*Code) 
	{
	case 0x40://Inc ax
		P->AX--;
		break;
	case 0x41://Inc cx
		P->CX--;
		break;
	case 0x42://Inc dx
		P->DX--;
		break;
	case 0x43://Inc bx
		P->BX--;
		break;
		/*case 0x44://Inc sP
		return 1;
		break;*/
	case 0x45://Inc bP
		P->BP--;
		break;
	case 0x46://Inc si
		P->SI--;
		break;
	case 0x47://Inc di
		P->DI--;
		break;
	}
	
}

int Instruction(byte* Opcode) 
{
	byte Code = *Opcode;
	if (Code == 0xab) {
		return 1;//stosw
	}
	else if (Code == 0x48 || Code == 0x4d || Code == 0x4b || Code == 0x49 || Code == 0x4f || Code == 0x4a || Code == 0x4e || Code == 0x4c) {
		return 2;//Dec
	}
	else if (Code == 0x40 || Code == 0x41 || Code == 0x42 || Code == 0x43 || Code == 0x44 || Code == 0x45 || Code == 0x46 || Code == 0x47) {
		return 3;//Inc
	}
	else if (Code == 0x58 || Code == 0x59 || Code == 0x5a || Code == 0x5b || Code == 0x5c || Code == 0x5d || Code == 0x5e || Code == 0x5f) {
		return 4;//PoP
	}
	else if (Code == 0x50 || Code == 0x51 || Code == 0x52 || Code == 0x53 || Code == 0x54 || Code == 0x55 || Code == 0x56 || Code == 0x57) {
		return 5;//Push
	}
	else if (Code == 0xb8 || Code == 0xb9 || Code == 0xba || Code == 0xbb || Code == 0xbc || Code == 0xbd || Code == 0xbe || Code == 0xbf || Code == 0x8b) {
		return 6;//mov
	}
	else if (Code == 0x33 || Code == 0x35 || (Code == 0x81 && ((*(Opcode + 1) & 0b00111000) == 0b00110000))) {
		return 7;//xor
	}
	else if (Code == 0x87) {
		return 8;//xchg
	}
	else if (Code == 0x05 || Code == 0x03 || (Code == 0x81 && ((*(Opcode + 1) & 0b00111000) == 0b00000000))) {
		return 9;//Add
	}
	else if (Code == 0x2b || Code == 0x2d || (Code == 0x81 && ((*(Opcode + 1) & 0b00111000) == 0b00101000))) {
		return 10;//sub
	}
	else {
		return -1;
	}
}

bool Call_Instruction(int ComNum, byte* Opcode, int length, Register* P, byte* Memory) 
{
	
	if (ComNum == 1) 
	{
		Stosw(P, Memory);
		if (Memory[0x0100] == 'V' && Memory[0x0101] == 'i' && Memory[0x0102] == 'r' && Memory[0x0103] == 'u'
			&& Memory[0x0104] == 's' && Memory[0x0105] == 'C' && Memory[0x0106] == 'o' && Memory[0x0107] == 'd' && Memory[0x0108] == 'e'
			&& Memory[0x0109] == 'G' && Memory[0x010a] == 'e' && Memory[0x010b] == 'n' && Memory[0x010c] == 'e' && Memory[0x010d] == 'r'
			&& Memory[0x010e] == 'a' && Memory[0x010f] == 't' && Memory[0x0110] == 'o' && Memory[0x0111] == 'r' && Memory[0x0112] == ' '
			&& Memory[0x0113] == 'b' && Memory[0x0114] == 'y' && Memory[0x0115] == ' ' && Memory[0x0116] == 'R' && Memory[0x0117] == 'e'
			&& Memory[0x0118] == 'd' && Memory[0x0119] == 'A' && Memory[0x011a] == 'r' && Memory[0x011b] == 'c') {
		
			//std::cout << "Virus detected!!" << std::endl;
			
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (ComNum == 2) 
	{
		Dec(P, Opcode);
		return 0;
	}
	else if (ComNum == 3) 
	{
		Inc(P, Opcode);
		return 0;
	}
	else if (ComNum == 4 || ComNum == 5) 
	{
		Push_Pop(P, Opcode);
		return 0;
	}
	/*else if (ComNum == 5) {
		Push(P, Opcode);
		return 0;
	}*/
	else if (ComNum == 6) 
	{
		Mov(P, Opcode);
		return 0;
	}
	else if (ComNum == 7) 
	{
		Xor(P, Opcode);
		return 0;
	}
	else if (ComNum == 8) 
	{
		Xchg(P, Opcode);
		return 0;
	}
	else if (ComNum == 9) 
	{
		Add(P, Opcode);
		return 0;
	}
	else if (ComNum == 10) 
	{
		Sub(P, Opcode);
		return 0;
	}
}











