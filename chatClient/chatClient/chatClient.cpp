// chatClient.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ChatClientNode.h"
#include <iostream>
#include <string>
int _tmain(int argc, _TCHAR* argv[])
{
	for (int i=0;i<10000;++i)
	{
		std::cout<<"第 "<<i<<" 个客户端进行连接！"<<std::endl;
		ChatClientNode* pClient = new ChatClientNode(i);
		int nRet = pClient->Verication();
		if (!nRet)
		{
			std::cout<<"第 "<<i<<" 个客户端验证通过！"<<std::endl;
		}
		else
		{
			std::cout<<"第 "<<i<<" 个客户端验证失败！"<<std::endl;
			delete pClient;
			continue;
		}
		nRet = pClient->Init();
		if (!nRet)
		{
			std::cout<<"第 "<<i<<" 个客户端初始化完成！"<<std::endl;
			Sleep(200);
			continue;
		}
		std::cout<<"第 "<<i<<" 个客户端初始化失败！"<<std::endl;
		delete pClient;
	}
	return 0;
}

