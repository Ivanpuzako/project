
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <iostream> 
#include <cstdio>
#include <clocale>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <vector>
#include "a.h"
#include <Windows.h>

extern "C" { 
	word* Stack; 
}

using namespace std;
int main(int argc, char* argv[]) {
	
	
	WIN32_FIND_DATAW wfd;
	wchar_t str1[100];
	cout << "Enter like C:\\abc\\*:    " << endl;;
	wcin >> str1;
	HANDLE const hFind = FindFirstFileW(str1, &wfd);
	int i = 0;
	if (INVALID_HANDLE_VALUE != hFind)
	{
		char ad[100] = "";
		char name[100] = "";;
		char s[100] = "";
		wchar_t* p = str1;
		while (*p != '\0') 
		{
			strcat(s, (char*)p);
			strcat(ad, (char*)p);

			p++;
		}
		wchar_t* g = NULL;
		int u;
		do
		{
			u = 0;
			while (u < 100) {
				if (s[u] == '*') {
					s[u] = '\0';
						break;
				}
				u++;
			}
			//std::wcout << &wfd.cFileName[0] << std::endl;
			for (i = 0; i < 50; i++) {

				if ((int)wfd.cFileName[i] == 52428 || (char)wfd.cFileName[i] == '\0') {
					
					break;
				}
				if ((char)wfd.cFileName[0] == '.') {
					goto begin;
				}
				g = &wfd.cFileName[i];
				strcat(s, (char*)g);
				strcat(name, (char*)g);
				//cout << (char)wfd.cFileName[i];
			}
			cout << endl;
		FILE *f = fopen(s, "rb");
		if (!f) return 0;
		fseek(f, 0, SEEK_END);
		size_t filesize = ftell(f);
		fseek(f, 0, SEEK_SET);
		char* Buffer = new char[filesize + 1];
		size_t res = 0;
		res = fread(Buffer, filesize, 1, f);
		if (res == 0) {
			cout << "NO";
			return 0;
		}Register Reg;
		Reg.AX = 0;
		Reg.BP = 0;
		Reg.BX = 0;
		Reg.CX = 0;
		Reg.DI = 0;
		Reg.DX = 0;
		Reg.IP = NULL;
		Reg.SI = 0;
		Register* Regp = &Reg;
		byte* MemorySegment = new byte[65335];

		unsigned char Com1;
		unsigned char Com2[2];
		unsigned char Com3[3];
		unsigned char Com4[4];
		int CommandNum = 0;




		bool isDetected = 0;

		Reg.IP = &Buffer[0];
		for (int f = 0; f < filesize; f++) {
			int Length = Getlength(*Reg.IP);
			if (Length == 4) {
				for (int i = 0; i < Length; i++) {
					Com4[i] = *Reg.IP;
					Reg.IP++;
				}

				CommandNum = Instruction(Com4);
				Call_Instruction(CommandNum, Com4, 4, Regp, MemorySegment);


			}
			else if (Length == 3) {
				for (int i = 0; i < Length; i++) {
					Com3[i] = *Reg.IP;
					Reg.IP++;
				}

				CommandNum = Instruction(Com3);
				Call_Instruction(CommandNum, Com3, 3, Regp, MemorySegment);

			}
			else if (Length == 2) {
				for (int i = 0; i < Length; i++) {
					Com2[i] = *Reg.IP;
					Reg.IP++;
				}

				CommandNum = Instruction(Com2);
				Call_Instruction(CommandNum, Com2, 2, Regp, MemorySegment);

			}
			else if (Length == 1) {
				Com1 = *Reg.IP;
				Reg.IP++;
				CommandNum = Instruction(&Com1);
				isDetected = Call_Instruction(CommandNum, &Com1, 1, Regp, MemorySegment);
				if (!isDetected) {

				}
				else {
					cout << name << " --> ";
					cout << "Virus detected " << endl;
					break;
					return 0;
				}

			}
			else if (Length == -1) {
				cout << name << " --> ";
				cout << "safe" << endl;
				break;
				return 0;
			}
		}
		begin:
		strcpy(s,ad);
		strcpy(name, "");
		
		} while (NULL != FindNextFileW(hFind, &wfd));

		FindClose(hFind);
	}
	return 0;
}