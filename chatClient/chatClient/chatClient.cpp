// chatClient.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ChatClientNode.h"
#include <iostream>
#include <string>
int _tmain(int argc, _TCHAR* argv[])
{
	for (int i=0;i<10000;++i)
	{
		std::cout<<"�� "<<i<<" ���ͻ��˽������ӣ�"<<std::endl;
		ChatClientNode* pClient = new ChatClientNode(i);
		int nRet = pClient->Verication();
		if (!nRet)
		{
			std::cout<<"�� "<<i<<" ���ͻ�����֤ͨ����"<<std::endl;
		}
		else
		{
			std::cout<<"�� "<<i<<" ���ͻ�����֤ʧ�ܣ�"<<std::endl;
			delete pClient;
			continue;
		}
		nRet = pClient->Init();
		if (!nRet)
		{
			std::cout<<"�� "<<i<<" ���ͻ��˳�ʼ����ɣ�"<<std::endl;
			Sleep(200);
			continue;
		}
		std::cout<<"�� "<<i<<" ���ͻ��˳�ʼ��ʧ�ܣ�"<<std::endl;
		delete pClient;
	}
	return 0;
}

