/************************************************************/
/* @课程名：		C++课程设计	题目二 用户注册与平台登录	*/
/* @作者；			谢睿（2018211208）						*/
/* @教师：			待定									*/
/* @最后修改时间：	2020/08/22 17：50						*/
/* @文件名：		main.cpp								*/
/* @文件说明：		主功能代码，用于测试					*/
/*----------------------------------------------------------*/
/* @备注：			本程序遵循任天堂公司习惯用语，使用“宝可*/
/*					梦(Pokemon)”代指宠物小精灵				*/
/************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include <winsock2.h>
#include <string.h>
using namespace std;

#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


//主函数
int main(int argc, char* argv[])
{
	cout << "System is Initializing..." << endl;
	
	char tmpStr[100] = { 0 };
	int continueFlag = 1;
	int loginFlag = 0;

	//socket相关初始化
	int error;//错误警告位
	int sendLen;//成功发送长度
	int receiveLen;//成功接收长度
	char sendBuf[1000] = "c";//发送缓冲区
	char receiveBuf[1000] = { 0 };//接收缓冲区
	u_short port = 1145;//端口 默认1145
	char ip[16] = "127.0.0.1";//ip 默认本机(127.0.0.1)

	if (argc > 1)//获取非默认ip与端口
	{
		strcpy(ip, argv[1]);
		cout << "Server IP is : " << ip << endl;
		if (argc > 2)
		{
			port = std::stoi(argv[2]);
			cout << "Server Port is : " << port << endl;
		}
		else
		{
			cout << "Server Port is : 1145 by default" << endl;
		}
	}
	else
	{
		cout << "Server IP is : 127.0.0.1 by default" << endl;
		cout << "Server Port is : 1145 by default" << endl;
	}

	//初始化 DLL
	WSADATA wsaData;
	error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error != 0)
	{
		cout << "初始化套接字库失败" << endl;
		return 0;
	}

	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(ip);
	sockAddr.sin_port = htons(port);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	cout << endl << "连接服务器" << endl << endl;

	//功能选择
	while(1)
	{
		//接收服务器传回的数据
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
		if (receiveLen < 0)
		{
			cout << "接收失败,服务器已断开" << endl;
			break;
		}
		else
		{
			cout << receiveBuf;
		}

		//向服务器发送数据
		cin >> sendBuf;
		sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		strcpy(tmpStr, sendBuf);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		if (sendLen < 0) cout << "发送失败" << endl;
		if (strcmp("1", tmpStr) == 0)//登陆
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			if (receiveLen < 0)
			{
				cout << "接收失败,服务器已断开" << endl;
				break;
			}
			else
			{
				cout << receiveBuf;
			}
			while (strcmp("登陆成功\n", receiveBuf) != 0)
			{
				cin >> sendBuf;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				strcpy(tmpStr, sendBuf);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (receiveLen < 0)
				{
					cout << "接收失败,服务器已断开" << endl;
					break;
				}
				else
				{
					cout << receiveBuf;
				}
				if (strcmp("登陆失败，", receiveBuf) == 0)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
				}
			}
			loginFlag = 1;
			break;
		}
		else if (strcmp("2", tmpStr) == 0)//注册
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			if (receiveLen < 0)
			{
				cout << "接收失败,服务器已断开" << endl;
				break;
			}
			else
			{
				cout << receiveBuf;
			}
			while (strcmp("注册成功，已登陆\n", receiveBuf) != 0)
			{
				cin >> sendBuf;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				strcpy(tmpStr, sendBuf);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (receiveLen < 0)
				{
					cout << "接收失败,服务器已断开" << endl;
					break;
				}
				else
				{
					cout << receiveBuf;
				}
				if (strcmp("注册失败，", receiveBuf) == 0)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
				}
			}
			memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			cout << receiveBuf;
			loginFlag = 1;
			break;
		}
		else if (strcmp("3", tmpStr) == 0)
		{
			while (1)
			{
				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (strcmp("###end###", receiveBuf) == 0) break;
				else cout << receiveBuf;
			}
		}
		else if (strcmp("4", tmpStr) == 0)
		{
			cout << "当前在线用户：" << endl;
			while (1)
			{
				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (strcmp("###end###", receiveBuf) == 0) break;
				else cout << receiveBuf;
			}
		}
		else if (strcmp("5", tmpStr) == 0)
		{
			cout << "已断开" << endl;
			break;
		}
		cout << endl;
	}

	//登陆成功
	while (loginFlag)
	{
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
		cout << endl << receiveBuf;
		cin >> sendBuf;
		sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		strcpy(tmpStr, sendBuf);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		if (sendLen < 0) cout << "发送失败" << endl;
		if (strcmp("1", tmpStr) == 0)//对战
		{
			//开始对战
			int autoBattle = 0;//是否自动对战 0否1是
			int battleType = 0;//战斗类型 0升级1决斗
			while (continueFlag)
			{
				//记录战斗模式
				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				cout << receiveBuf;
				cin >> sendBuf;
				battleType = atoi(sendBuf);
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				cout << receiveBuf;
				cin >> sendBuf;
				if (strcmp("1", sendBuf) == 0)autoBattle = 1;
				else if (strcmp("2", sendBuf) == 0)autoBattle = 0;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区

				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				cout << receiveBuf;
				cin >> sendBuf;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区

				while (1)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					if (strcmp("#selectEnd#", receiveBuf) == 0)
					{
						break;
					}
					else
					{
						cout << receiveBuf;
						cin >> sendBuf;
						sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
					}
				}

				if (autoBattle == 0)//非自动
				{
					while (1)
					{
						memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
						receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
						if (strcmp("#battleOver#", receiveBuf) == 0)
						{
							break;
						}
						else
						{
							while (1)
							{
								if (strcmp("#skillOver#", receiveBuf) == 0)
								{
									memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
									receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
									cout << receiveBuf;
									break;
								}
								else
								{
									cout << receiveBuf;
									cin >> sendBuf;
									sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
									memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
									memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
									receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
								}
							}
						}
					}
				}
				else//自动
				{
					while (1)
					{
						memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
						receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
						if (strcmp("#battleOver#", receiveBuf) == 0)
						{
							break;
						}
						else
						{
							cout << receiveBuf;
						}
					}
				}

				//战斗结束
				while (1)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					if (strcmp("#forget#", receiveBuf) == 0)
					{
						while (1)
						{
							memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
							receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
							if (strcmp("#learnEnd#", receiveBuf) == 0 || strcmp("#allEnd#", receiveBuf) == 0)
							{
								memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
								receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
								cout << receiveBuf;
								break;
							}
							else
							{
								cout << receiveBuf;
								cin >> sendBuf;
								sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
							}
						}
						break;
					}
					else if (strcmp("继续下一场战斗？（Y/N）：", receiveBuf) == 0)
					{
						cout << endl;
						cout << receiveBuf;
						cin >> sendBuf;
						sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						if (strcmp("N", sendBuf) == 0 || strcmp("n", sendBuf) == 0)
						{
							continueFlag = 0;
						}
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						cout << endl;
						break;
					}
					else if (strcmp("#lossPokemon#", receiveBuf) == 0)
					{
						while (1)
						{
							memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
							receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
							if (strcmp("#lossEnd#", receiveBuf) == 0) break;
							else
							{
								cout << receiveBuf;
								cin >> sendBuf;
								sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
							}
						}
					}
					else
					{
						cout << receiveBuf;
					}
				}
				cout << endl;
			}
			continueFlag = 1;
		}
		else if (strcmp("2", tmpStr) == 0)
		{
			while (1)
			{
				memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (strcmp("#seeStart#", receiveBuf) == 0)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
					break;
				}
				else
				{
					cout << receiveBuf;
					cin >> sendBuf;
					sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				}
			}
		}
		else if (strcmp("3", tmpStr) == 0)
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			cout << receiveBuf;
		}
		else if (strcmp("4", tmpStr) == 0)
		{
			break;
		}
	}

	

	//关闭套接字
	closesocket(sock);

	//终止使用 DLL
	WSACleanup();

	cout << "程序结束，感谢使用" << endl;

	return 0;
}