#pragma once

#include <WinSock2.h>
#include <iostream>
#include <stdio.h>
#include <string>


//�������ڵ�
class ChatClientNode
{
public:
	ChatClientNode(int nNumber = 0);
	~ChatClientNode(void);
	
	//��Ȩ��֤
	int Verication();

	//��ʼ��
	int Init();				//��ʼ��socket

private:

	void Close();				//�ر�
private:
	SOCKET m_st;				//socket
	HANDLE m_hRecv;				//�����߳�
	HANDLE m_hSend;				//�����߳�
	int m_nNumber;
};

