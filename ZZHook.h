#pragma once
#include <Windows.h>
#include <iostream>
#define Log(message) std::cout<<message<<std::endl;
void DWORD_To_char(DWORD& address, char*& arry);
std::string WString2String(const std::wstring& ws);
std::wstring String2WString(const std::string& s);


struct Shell_Code
{//,
	unsigned char pushad = 0x60;
	unsigned char pushfd = 0x9C;
	unsigned char pushadToSelfFun = 0x60;//pushad
	unsigned char mov[4] = { 0xC7, 0x44, 0x24, 0xFC };
	unsigned char move_Fun_To_Esp[4]; //�Լ������ĵ�ַ���� [esp-0x4]
	unsigned char call_Esp[4] = { 0xFF, 0x54, 0x24, 0xFC };//call DWORD PTR [esp-0x4]
	//83 C4 20
	unsigned  char AddEsp20[3] = { 0x83, 0xC4, 0x20 };//Add Esp,20
	unsigned char popfd = 0x9d;//popfd
	unsigned char popad = 0x61;//popad
	//����ԭʼ��call
	//unsigned char ret = 0xC3;
	//unsigned char ori_call[5];// call 0xxxxxx  ���ĵ����������Լ�������Ӳ����
	//unsigned char mov_Eax= 0xB8;
	//push ���ص�ַ
	//
	//jmp ԭ����ͷ
	unsigned char push_back_Add = 0x68;
	unsigned char Back_Add[4];   //�ѷ��ص�ַ����eax ��jmp��ȥ
	//mov    DWORD PTR [esp-0x4],0x12345678
	unsigned char jmp_to_ori_fun[4] = { 0xC7, 0x44, 0x24, 0xFC };
	unsigned char ori_fun_head_add[4];
	//  jmp    DWORD PTR [esp-0x4]
	unsigned char jmp_to_back_head[4] = { 0xFF, 0x64, 0x24, 0xFC };

	//unsigned char jmp_eax[2] = { 0xFF, 0xE0 };
	//Shell_Code(char* &move_Fun_To_Esp, char* &Back_Add, char* &ori_fun_head_add) {
	Shell_Code(char*& move_Fun_To_Esp, char*& Back_Add, DWORD& ori_fun_head_add) {
		memcpy_s(this->move_Fun_To_Esp, 4, move_Fun_To_Esp, 4);   //Ҫ��ת���ĺ����ĵ�ַ
		memcpy_s(this->Back_Add, 4, Back_Add, 4);                 //callִ������ת�صĵ�ַ
		memcpy_s(this->ori_fun_head_add, 4, &ori_fun_head_add, 4); //ԭ������ַͷ
	}

};


class _declspec(dllexport) Hook {
private:

public:
	DWORD hookAddr;
	BYTE backCode[5];
	HANDLE hProcess;

	Hook(DWORD hookAddr);
	~Hook();
	int StartHook(LPVOID Naked_fun_space, DWORD My_fun);
	bool UnHook();

};