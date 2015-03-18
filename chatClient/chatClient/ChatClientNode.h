#pragma once

#include <WinSock2.h>
#include <iostream>
#include <stdio.h>
#include <string>


//聊天程序节点
class ChatClientNode
{
public:
	ChatClientNode(int nNumber = 0);
	~ChatClientNode(void);
	
	//授权验证
	int Verication();

	//初始化
	int Init();				//初始化socket

private:

	void Close();				//关闭
private:
	SOCKET m_st;				//socket
	HANDLE m_hRecv;				//接收线程
	HANDLE m_hSend;				//接收线程
	int m_nNumber;
};

