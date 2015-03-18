#include "StdAfx.h"
#include "ChatClientNode.h"

#pragma comment(lib,"ws2_32.lib")

//接收消息
DWORD WINAPI RecvMsg(LPVOID lpParamter)
{
	SOCKET* st = (SOCKET*)lpParamter;
	while(1)
	{
		char buf[256] = {0};
		if(recv(*st,buf,sizeof(buf),0)<=0)
		{
			   return 0;
		}
		printf("%s\n",buf);
	}
}
//发送消息
DWORD WINAPI SendMsg(LPVOID lpParamter)
{
	SOCKET* st = (SOCKET*)lpParamter;
	while (1)
	{
		char szbuf[256] = {0};
		int n=10;
		int b = 0x50000001;
		std::string str = "I'm Client!";
		int nPos = 0;
		sprintf(szbuf,"%d",n);
		nPos+=32;
		sprintf(szbuf+nPos,"%x",b);
		nPos+=32;
		sprintf(szbuf+nPos,"%s",str.c_str());

		send(*st,str.c_str(),str.length(),0);//发给服务器
		Sleep(500);
	}
	return 0;
}



ChatClientNode::ChatClientNode(int nNumber)
	:m_nNumber(nNumber)
{
	m_hSend = NULL;
	m_hRecv = NULL;

}


ChatClientNode::~ChatClientNode(void)
{
	Close();
}


//授权验证
int ChatClientNode::Verication()
{
	WORD wdVersion = MAKEWORD(1,1);
	WSAData wsaData;
	int nRet = WSAStartup(wdVersion,&wsaData);
	if (!nRet)
	{
		SOCKET st  = socket(AF_INET,SOCK_STREAM,0);
		SOCKADDR_IN clientsock_in;
		clientsock_in.sin_addr.S_un.S_addr=inet_addr("118.26.239.241");
		clientsock_in.sin_family=AF_INET;
		clientsock_in.sin_port=htons(9897);

		nRet =  connect(st,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//开始连接
		if (!nRet)
		{
			std::string str = "I need Veri ";
			send(st,str.c_str(),str.length(),0);//发给服务器

			char buf[256] = {0};
			if(recv(st,buf,sizeof(buf),0)<=0)
			{
				closesocket(st);
				WSACleanup();
				return -1;
			}
			printf("%s\n",buf);
			closesocket(st);
			WSACleanup();
			return 0;
		}
		closesocket(st);
		WSACleanup();
	}
	return -1;
}

//初始化socket
int  ChatClientNode::Init()
{
	WORD wdVersion = MAKEWORD(1,1);
	WSAData wsaData;
	int nRet = WSAStartup(wdVersion,&wsaData);
	if (!nRet)
	{
		m_st  = socket(AF_INET,SOCK_STREAM,0);
		SOCKADDR_IN clientsock_in;
		clientsock_in.sin_addr.S_un.S_addr=inet_addr("118.26.239.241");
		clientsock_in.sin_family=AF_INET;
		clientsock_in.sin_port=htons(9896);

		nRet =  connect(m_st,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));//开始连接
		if (!nRet)
		{
			m_hRecv = CreateThread(NULL,0,RecvMsg,&m_st,0,NULL);
			m_hSend = CreateThread(NULL,0,SendMsg,&m_st,0,NULL);
			return 0;
		}
	}
	return -1;
}


//关闭
void ChatClientNode::Close()
{
	if (m_hRecv)
	{
			CloseHandle(m_hRecv);
	}
	if (m_hSend)
	{
		CloseHandle(m_hSend);
	}

	
	closesocket(m_st);
	WSACleanup();
}