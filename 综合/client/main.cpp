/************************************************************/
/* @�γ�����		C++�γ����	��Ŀ�� �û�ע����ƽ̨��¼	*/
/* @���ߣ�			л�2018211208��						*/
/* @��ʦ��			����									*/
/* @����޸�ʱ�䣺	2020/08/22 17��50						*/
/* @�ļ�����		main.cpp								*/
/* @�ļ�˵����		�����ܴ��룬���ڲ���					*/
/*----------------------------------------------------------*/
/* @��ע��			��������ѭ�����ù�˾ϰ�����ʹ�á�����*/
/*					��(Pokemon)����ָ����С����				*/
/************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include <winsock2.h>
#include <string.h>
using namespace std;

#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


//������
int main(int argc, char* argv[])
{
	cout << "System is Initializing..." << endl;
	
	char tmpStr[100] = { 0 };
	int continueFlag = 1;
	int loginFlag = 0;

	//socket��س�ʼ��
	int error;//���󾯸�λ
	int sendLen;//�ɹ����ͳ���
	int receiveLen;//�ɹ����ճ���
	char sendBuf[1000] = "c";//���ͻ�����
	char receiveBuf[1000] = { 0 };//���ջ�����
	u_short port = 1145;//�˿� Ĭ��1145
	char ip[16] = "127.0.0.1";//ip Ĭ�ϱ���(127.0.0.1)

	if (argc > 1)//��ȡ��Ĭ��ip��˿�
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

	//��ʼ�� DLL
	WSADATA wsaData;
	error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error != 0)
	{
		cout << "��ʼ���׽��ֿ�ʧ��" << endl;
		return 0;
	}

	//�����׽���
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���������������
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr(ip);
	sockAddr.sin_port = htons(port);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	cout << endl << "���ӷ�����" << endl << endl;

	//����ѡ��
	while(1)
	{
		//���շ��������ص�����
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
		if (receiveLen < 0)
		{
			cout << "����ʧ��,�������ѶϿ�" << endl;
			break;
		}
		else
		{
			cout << receiveBuf;
		}

		//���������������
		cin >> sendBuf;
		sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		strcpy(tmpStr, sendBuf);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		if (sendLen < 0) cout << "����ʧ��" << endl;
		if (strcmp("1", tmpStr) == 0)//��½
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			if (receiveLen < 0)
			{
				cout << "����ʧ��,�������ѶϿ�" << endl;
				break;
			}
			else
			{
				cout << receiveBuf;
			}
			while (strcmp("��½�ɹ�\n", receiveBuf) != 0)
			{
				cin >> sendBuf;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				strcpy(tmpStr, sendBuf);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (receiveLen < 0)
				{
					cout << "����ʧ��,�������ѶϿ�" << endl;
					break;
				}
				else
				{
					cout << receiveBuf;
				}
				if (strcmp("��½ʧ�ܣ�", receiveBuf) == 0)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
				}
			}
			loginFlag = 1;
			break;
		}
		else if (strcmp("2", tmpStr) == 0)//ע��
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			if (receiveLen < 0)
			{
				cout << "����ʧ��,�������ѶϿ�" << endl;
				break;
			}
			else
			{
				cout << receiveBuf;
			}
			while (strcmp("ע��ɹ����ѵ�½\n", receiveBuf) != 0)
			{
				cin >> sendBuf;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				strcpy(tmpStr, sendBuf);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (receiveLen < 0)
				{
					cout << "����ʧ��,�������ѶϿ�" << endl;
					break;
				}
				else
				{
					cout << receiveBuf;
				}
				if (strcmp("ע��ʧ�ܣ�", receiveBuf) == 0)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
				}
			}
			memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			cout << receiveBuf;
			loginFlag = 1;
			break;
		}
		else if (strcmp("3", tmpStr) == 0)
		{
			while (1)
			{
				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (strcmp("###end###", receiveBuf) == 0) break;
				else cout << receiveBuf;
			}
		}
		else if (strcmp("4", tmpStr) == 0)
		{
			cout << "��ǰ�����û���" << endl;
			while (1)
			{
				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (strcmp("###end###", receiveBuf) == 0) break;
				else cout << receiveBuf;
			}
		}
		else if (strcmp("5", tmpStr) == 0)
		{
			cout << "�ѶϿ�" << endl;
			break;
		}
		cout << endl;
	}

	//��½�ɹ�
	while (loginFlag)
	{
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
		cout << endl << receiveBuf;
		cin >> sendBuf;
		sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		strcpy(tmpStr, sendBuf);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		if (sendLen < 0) cout << "����ʧ��" << endl;
		if (strcmp("1", tmpStr) == 0)//��ս
		{
			//��ʼ��ս
			int autoBattle = 0;//�Ƿ��Զ���ս 0��1��
			int battleType = 0;//ս������ 0����1����
			while (continueFlag)
			{
				//��¼ս��ģʽ
				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				cout << receiveBuf;
				cin >> sendBuf;
				battleType = atoi(sendBuf);
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				cout << receiveBuf;
				cin >> sendBuf;
				if (strcmp("1", sendBuf) == 0)autoBattle = 1;
				else if (strcmp("2", sendBuf) == 0)autoBattle = 0;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����

				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				cout << receiveBuf;
				cin >> sendBuf;
				sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����

				while (1)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
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
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
					}
				}

				if (autoBattle == 0)//���Զ�
				{
					while (1)
					{
						memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
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
									memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
									receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
									cout << receiveBuf;
									break;
								}
								else
								{
									cout << receiveBuf;
									cin >> sendBuf;
									sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
									memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
									memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
									receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
								}
							}
						}
					}
				}
				else//�Զ�
				{
					while (1)
					{
						memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
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

				//ս������
				while (1)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					if (strcmp("#forget#", receiveBuf) == 0)
					{
						while (1)
						{
							memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
							receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
							if (strcmp("#learnEnd#", receiveBuf) == 0 || strcmp("#allEnd#", receiveBuf) == 0)
							{
								memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
								receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
								cout << receiveBuf;
								break;
							}
							else
							{
								cout << receiveBuf;
								cin >> sendBuf;
								sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
							}
						}
						break;
					}
					else if (strcmp("������һ��ս������Y/N����", receiveBuf) == 0)
					{
						cout << endl;
						cout << receiveBuf;
						cin >> sendBuf;
						sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						if (strcmp("N", sendBuf) == 0 || strcmp("n", sendBuf) == 0)
						{
							continueFlag = 0;
						}
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						cout << endl;
						break;
					}
					else if (strcmp("#lossPokemon#", receiveBuf) == 0)
					{
						while (1)
						{
							memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
							receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
							if (strcmp("#lossEnd#", receiveBuf) == 0) break;
							else
							{
								cout << receiveBuf;
								cin >> sendBuf;
								sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
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
				memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
				receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
				if (strcmp("#seeStart#", receiveBuf) == 0)
				{
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
					cout << receiveBuf;
					break;
				}
				else
				{
					cout << receiveBuf;
					cin >> sendBuf;
					sendLen = send(sock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				}
			}
		}
		else if (strcmp("3", tmpStr) == 0)
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
			receiveLen = recv(sock, receiveBuf, sizeof(receiveBuf), NULL);
			cout << receiveBuf;
		}
		else if (strcmp("4", tmpStr) == 0)
		{
			break;
		}
	}

	

	//�ر��׽���
	closesocket(sock);

	//��ֹʹ�� DLL
	WSACleanup();

	cout << "�����������лʹ��" << endl;

	return 0;
}