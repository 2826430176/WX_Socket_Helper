
#include "pch.h"
#include "MemOpt.h"
#include "ProcessOpt.h"
#include "FindPattern.h"
#include "PubLic.h"
#pragma warning(disable:4996)

DWORD Recv_Msg_ADD = 0;
DWORD wxid_getDetail_ADD = 0;
DWORD Send_Normal_msg_ADD = 0;
int Main_Match_Pattern() {
	printf_s("��ǰ����PID:   %#x\n", GetCurrentProcessId());

	CProcessOpt po(GetCurrentProcessId());
	po.m_hProcess = GetCurrentProcess();
	InitializeSigCopyMemory(GetCurrentProcessId(), "WeChatWin.dll");
	
	
	const char* Recv_msg_Tzm = "83C0F250E8????????83C40C85C0";//������Ϣ
	DWORD modBase = 0;
	//DWORD dwData = GeekXFindPattern(Recv_msg_Tzm, &modBase, 0x0);//�µ�Ѱַ���ĺ��� ����Ŀ����̿��ڴ�ȫ���� �� ������  �ķ�ʽ �� ָ�뷨������ַ �ٶȼ���
	Recv_Msg_ADD = GeekXFindPattern(Recv_msg_Tzm, &modBase, 0x0);//�µ�Ѱַ���ĺ��� ����Ŀ����̿��ڴ�ȫ���� �� ������  �ķ�ʽ �� ָ�뷨������ַ �ٶȼ���
	
	const char* wxid_getDetail_Tzm = "89????50E8??????????????01E8??????????????00E8????????84c00f";//wxid��ȡ������Ϣ
	wxid_getDetail_ADD = GeekXFindPattern(wxid_getDetail_Tzm, &modBase, 0x4);

	
	const char* send_normal_msg_Tzm = "8D8d????????E8????????83C40C508d8d????????c645";//������ͨ��Ϣ������
	
	Send_Normal_msg_ADD= GeekXFindPattern(send_normal_msg_Tzm, &modBase, 0x6);
	printf_s("������ͨ��Ϣ�������ַ       %#x\n", Send_Normal_msg_ADD);
	Send_Normal_msg_ADD=Read_OriFun_ADD(po.GetProcessHandle(), Send_Normal_msg_ADD);

	FinalizeScan();



	printf_s("������Ϣ��ַ           %#x\n", Recv_Msg_ADD);
	printf_s("������ͨ��Ϣ��ַ       %#x\n", Send_Normal_msg_ADD);
	printf_s("wxid��ȡ��ϸ��Ϣ��ַ   %#x\n", wxid_getDetail_ADD);


	return TRUE;
	//CMemOpt mo(po.GetProcessHandle(), dwData);
	//mo.ReadMem(&dwData, 4);
	//printf_s("%#x\n", dwData);
}