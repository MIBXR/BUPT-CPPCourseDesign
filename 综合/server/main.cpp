/************************************************************/
/* @�γ�����		C++�γ����	��Ŀ�� �û�ע����ƽ̨��¼	*/
/* @���ߣ�			л�2018211208��						*/
/* @��ʦ��			���鲨									*/
/* @����޸�ʱ�䣺	2020/09/01 19��22						*/
/* @�ļ�����		main.cpp								*/
/* @�ļ�˵����		�����ܴ��룬���ڲ����Լ�����ʵ��		*/
/*----------------------------------------------------------*/
/* @��ע��			��������ѭ�����ù�˾ϰ�����ʹ�á�����*/
/*					��(Pokemon)����ָ����С����				*/
/************************************************************/

#include<iostream>
#include<fstream>
#include<string>
#include<winsock2.h>
#include<string.h>
#include"header.h"
#include"PokemonList.h"
#include"server.h"
using namespace std;

#pragma comment (lib, "ws2_32.lib")  //���� ws2_32.dll


//ȫ�ֱ�����
//int pokemonNumOwned = 0;//���ӵ�еı�������
int expNeeded[14] = { 20,40,60,90,120,160,200,250,300,350,400,500,700,1000 };//�������辭��ֵ
double effectiveness[10][10] = { {1,   1,   1,   1,   1,   1,   1,   1,   1,   1  },
								 {1,   0.5, 2,   0.5, 2,   1,   1,   1,   2,   0.5},
								 {1,   0.5, 0.5, 1,   0.5, 0.5, 2,   1,   1,   0.5},
								 {1,   2,   0.5, 0.5, 1,   1,   2,   1,   1,   0.5},
								 {1,   0.5, 2,   1,   1,   0.5, 1,   1,   1,   1  },
								 {1,   1,   2,   1,   2,   1,   1,   0.5, 1,   1  },
								 {1,   2,   0.5, 1,   0.5, 0,   1,   2,   1,   1  },
								 {1,   1,   0.5, 2,   1,   2,   0,   0.5, 1,   0.5},
								 {1,   0.5, 2,   0.5, 1,   2,   2,   1,   0.5, 2  },
								 {1,   1,   1,   1,   1,   1,   1,   1,   1,   2  } };//Ԫ����˱�
int userNum = 0;//����ע���û���
int activeUserNum = 0;//��ǰ�����û�
CLIENT_DATA* allClients = NULL;//���������û�������
char* virtualPokemonList;//�û���ѡ���ս�����⾫���б�
char* virtualPokemonName[10];//�û���ѡ���ս�����⾫������
int* virtualPokemonData[10];//�û���ѡ���ս�����⾫������


//�����߳�
DWORD WINAPI ServerThread(LPVOID lpParameter)
{
	//�����������
	CLIENT_DATA* pmd = (CLIENT_DATA*)lpParameter;
	SOCKET* clntSock = pmd->clientSocket;
	User* client = pmd->clientUser;
	int state = pmd->state;

	int menuFlag = 1;//�˳��˵���־λ
	int tmpData[9] = { FIRE,POWER,0,1,2,10,1,2,2 };//��ʼ������
	char tmpStr[100] = { 0 };//���ڿ����Լ��Ƚϵ���ʱ����
	int sendLen;//�ɹ����ͳ���
	int receiveLen;//�ɹ����ճ���
	char sendBuf[MAX_BUF_SIZE] = "This is a message from server\n";//���ͻ�����
	char receiveBuf[MAX_BUF_SIZE] = { 0 };//���ջ�����
	int round = 0;//��������
	double winRate = 0;//ʤ��

	srand(time(0));

	//���˵��Լ���½����
	char tmpBuf[32] = { 0 };
	ifstream userFile("./DATA/userData.txt");
	userFile >> tmpBuf;
	userFile >> userNum;
	userFile.close();

	char uName[32] = { 0 };
	char uPass[32] = { 0 };
	int result = 0;
	cout << "�ͻ������ӳɹ�" << endl << endl;
	
	while (menuFlag)
	{
		strcpy(sendBuf, "\n����δ��½����ѡ��\n"
						"1.�û���¼\n"
						"2.�û�ע��\n"
						"3.�鿴ע���û���Ϣ\n"
						"4.�鿴�����û�\n"
						"5.�Ͽ��������������\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		if (receiveLen < 0)
		{
			cout << "����ʧ��,�ͻ����ѶϿ�" << endl;
			menuFlag = 0;
			break;
		}
		else
		{
			if (strcmp("1", receiveBuf) == 0)//��½
			{
				cout << "�û���½" << endl;
				int tryCount = 2;
				while (tryCount >= 0)
				{
					strcpy(sendBuf, "�������û���(32�ַ�����)��\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uName, receiveBuf);
					strcpy(sendBuf, "����������(32�ַ�����)��\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uPass, receiveBuf);

					client = new User(uName, uPass, 1, result);
					pmd->clientUser = client;
					if (result == 0)
					{
						pmd->state = LOGINED;
						menuFlag = 0;
						strcpy(sendBuf, "��½�ɹ�\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						break;
					}
					else if (result == 1)
					{
						itoa(tryCount, tmpStr, 10);
						strcpy(sendBuf, "��½ʧ�ܣ�"); 
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						strcpy(sendBuf, "�û������ڣ������Գ���");
						strcat(sendBuf, tmpStr);
						strcat(sendBuf, "��\n");
						memset(tmpStr, 0, sizeof(tmpStr));
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						delete client;
						Sleep(10);
					}
					else if (result == 2)
					{
						itoa(tryCount, tmpStr, 10);
						strcpy(sendBuf, "��½ʧ�ܣ�");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						strcpy(sendBuf, "������󣬻����Գ���");
						strcat(sendBuf, tmpStr);
						strcat(sendBuf, "��\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						delete client;
						Sleep(10);
					}
					else if (result == 3)
					{
						itoa(tryCount, tmpStr, 10);
						strcpy(sendBuf, "��½ʧ�ܣ�");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						strcpy(sendBuf, "�����ظ���½�������Գ���");
						strcat(sendBuf, tmpStr);
						strcat(sendBuf, "��\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						delete client;
						Sleep(10);
					}
					tryCount--;
				}
			}
			else if (strcmp("2", receiveBuf) == 0)//ע��
			{
				cout << "�û�ע��" << endl;
				while (1)
				{
					strcpy(sendBuf, "�������û���(32�ַ�����)��\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uName, receiveBuf);
					strcpy(sendBuf, "����������(32�ַ�����)��\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
					memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uPass, receiveBuf);
					client = new User(uName, uPass, 0, result);
					if (result == 0)//ע��ɹ�
					{
						pmd->clientUser = client;
						pmd->state = LOGINED;
						menuFlag = 0;
						strcpy(sendBuf, "ע��ɹ����ѵ�½\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						userNum++;
						strcpy(sendBuf, "���3ֻ��ʼ������\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						break;
					}
					else if (result == 1)//ע��ʧ�ܣ��û����ظ�
					{
						strcpy(sendBuf, "ע��ʧ�ܣ�");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						strcpy(sendBuf, "�û����ظ�\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
					}
				}
			}
			else if (strcmp("3", receiveBuf) == 0)//�鿴�û���Ϣ
			{
				strcpy(sendBuf, "�û���Ϣ���£�\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				char dataName[100] = { 0 };
				int dataNum = 0;
				int bufNum = 0;
				ifstream userFile("./DATA/userData.txt");
				userFile.getline(dataName, 100);
				userFile.getline(dataName, 100);
				for (int i = 0; i < userNum; i++)
				{
					userFile >> dataName;
					//cout << "�û���" << dataName << ", ";
					strcpy(sendBuf, "�û���");
					strcat(sendBuf, dataName);
					strcat(sendBuf, ", ");
					while (strcmp("#pokemon#", dataName) != 0)//��λ����������λ��
					{
						userFile >> dataName;
					}
					userFile >> dataNum;
					//cout << "��" << dataNum << "ֻ�����Σ�" << endl;
					itoa(dataNum, tmpStr, 10);
					strcat(sendBuf, "��");
					strcat(sendBuf, tmpStr);
					strcat(sendBuf, "ֻ�����Σ�\n");
					memset(tmpStr, 0, sizeof(tmpStr));
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
					Sleep(10);
					for (int j = 0; j < dataNum; j++)
					{
						//cout << j + 1 << ".";
						userFile >> dataName; //cout << "���������壺" << dataName << ", ";
						strcpy(sendBuf, "���������壺");
						strcat(sendBuf, dataName);
						strcat(sendBuf, ", ");
						userFile >> bufNum; //cout << data[0] << endl; //Ԫ�� 
						userFile >> bufNum;//����
						userFile >> dataName; //cout << "���������֣�" << dataName << ", ";
						strcat(sendBuf, "���������֣�");
						strcat(sendBuf, dataName);
						strcat(sendBuf, ", ");
						userFile >> bufNum;//EXP
						userFile >> bufNum; //cout << "�ȼ���" << bufNum << endl;//LV
						itoa(bufNum, tmpStr, 10);
						strcat(sendBuf, "�ȼ���");
						strcat(sendBuf, tmpStr);
						strcat(sendBuf, "\n");
						userFile >> bufNum;//ATK
						userFile >> bufNum;//HP
						userFile >> bufNum;//DEF
						userFile >> bufNum;//SPEED
						userFile >> bufNum;//Index
						userFile >> dataName;
						userFile.getline(dataName, 100);
						memset(tmpStr, 0, sizeof(tmpStr));
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
					}
					//cout << endl;
					userFile >> dataName;
					userFile.getline(dataName, 100);
				}
				Sleep(10);
				strcpy(sendBuf, "###end###");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				userFile.close();
				Sleep(10);
			}
			else if (strcmp("4", receiveBuf) == 0)//�鿴�����û�
			{
				//cout << "��ǰ�����û���" << endl;
				CLIENT_DATA* showData = allClients;
				char thisName[32] = { 0 };
				while (showData)
				{
					if (showData->state == LOGINED)
					{
						showData->clientUser->getUsername(thisName);
						strcpy(sendBuf, thisName);
						strcat(sendBuf, "\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						//cout << thisName << endl;
						Sleep(10);
					}
					showData = showData->nextData;
				}
				Sleep(10);
				strcpy(sendBuf, "###end###");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else if (strcmp("5", receiveBuf) == 0)//�˳�
			{
				pmd->state = UNLOGIN;
				menuFlag = 0;
				break;
			}
			else
			{
				cout << "ָ�����" << endl;
			}
		}
	}
	//system("pause");

	//�˳����˵��������Ӳ˵����������
	int battleWith = 0;//���������ս�ı����α��
	Pokemon* servPokem;//���������½�������
	Pokemon* clntPokem;//���û��½�������
	if (pmd->state == LOGINED)//��½�ɹ�
	{
		while (1)
		{
			strcpy(sendBuf, "����ѡ��\n"
				"1.���ж�ս\n"
				"2.�鿴ʤ��\n"
				"3.�鿴����\n"
				"4.�˳���½����������\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
			receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
			if (receiveLen < 0)
			{
				cout << "����ʧ��,�ͻ����ѶϿ�" << endl;
				break;
			}
			else
			{
				if (strcmp("1", receiveBuf) == 0)//��ս
				{
					//client->loadPokemon();
					//client->selectPokemon(clntSock);
					//system("pause");
					while (1)
					{
						char tmpName[32] = { 0 };
						int tmpStatus[7] = { 0 };
						int autoBattle = 0;//�Ƿ��Զ���ս 0��1��
						int battleType = 0;//ս������ 0����1����

						strcpy(sendBuf, "ѡ��������ͣ�\n"
							"1.������\n"
							"2.������\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (receiveLen < 0) cout << "����ʧ��,�ͻ����ѶϿ�" << endl;
						else
						{
							if (strcmp("1", receiveBuf) == 0)battleType = 0;
							else if (strcmp("2", receiveBuf) == 0)battleType = 1;
							else cout << "ָ�����" << endl;
						}
						strcpy(sendBuf, "ѡ��ս��ģʽ��\n"
							"1.�Զ�ս��(ϵͳ���ʹ��˫�������εļ���)\n"
							"2.�ֶ�ս��(�û�����ѡ��˫�������εļ���)\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (receiveLen < 0)
						{
							cout << "����ʧ��,�ͻ����ѶϿ�" << endl;
							break;
						}
						else
						{
							if (strcmp("1", receiveBuf) == 0)autoBattle = 1;
							else if (strcmp("2", receiveBuf) == 0)autoBattle = 0;
							else cout << "ָ�����" << endl;
						}
						strcpy(sendBuf, "ѡ���ս�����Σ�\n");
						strcat(sendBuf, virtualPokemonList);
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (receiveLen < 0)
						{
							cout << "����ʧ��,�ͻ����ѶϿ�" << endl;
							break;
						}
						else
						{
							battleWith = atoi(receiveBuf);
							battleWith--;
						}
						switch (battleWith)
						{
						case 0:
							servPokem = new Bulbasaur(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 1:
							servPokem = new Charizard(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 2:
							servPokem = new Squirtle(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 3:
							servPokem = new Caterpie(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 4:
							servPokem = new Pidgeotto(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 5:
							servPokem = new Diglett(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 6:
							servPokem = new Pikachu(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 7:
							servPokem = new Snorunt(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 8:
							servPokem = new Dragonite(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						case 9:
							servPokem = new Pikachu(virtualPokemonName[battleWith], virtualPokemonData[battleWith]);
							break;
						default:
							servPokem = new Bulbasaur(virtualPokemonName[0], virtualPokemonData[0]);
							break;
						}

						client->loadPokemon();//���뱦����
						client->selectPokemon(clntSock);//ѡ���ս������
						clntPokem = client->usingPokemon;//ʹ�ñ�����

						while ((*clntPokem).getHP() > 0 && (*servPokem).getHP() > 0)//���˫�����ɼ���ս��
						{
							//������
							if (round % (*servPokem).getSPEED() == 0)
							{
								(*servPokem).attack((*clntPokem), autoBattle, clntSock);
								if ((*clntPokem).getHP() == 0) break;
								Sleep(101);
							}
							if (round % (*clntPokem).getSPEED() == 0)
							{
								(*clntPokem).attack((*servPokem), autoBattle, clntSock);
								if ((*servPokem).getHP() == 0) break;
								Sleep(101);
							}
							if (round < MAX_32_INT)round++;
							else round = 0;

							/*�غ���
							if ((*servPokem).getSPEED() <= (*clntPokem).getSPEED())//�ٶȿ�ı��������֣�һ�������������
							{
								cout << "����������" << endl;
								(*servPokem).attack((*clntPokem));
								if ((*clntPokem).getHP() == 0) break;
								(*clntPokem).attack((*servPokem));
								cout << "�غϽ�����������һ�غ�" << endl << endl;
							}
							else
							{
								cout << "�ͻ�������" << endl;
								(*clntPokem).attack((*servPokem));
								if ((*servPokem).getHP() == 0) break;
								(*servPokem).attack((*clntPokem));
								cout << "�غϽ�����������һ�غ�" << endl << endl;
							}
							*/
						}
						strcpy(sendBuf, "#battleOver#");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						Sleep(10);
						//��ս�������������
						if ((*clntPokem).getHP() == 0)//����ͻ��������޷�ս�����������ʤ��
						{
							client->allBattlePlus();
							if (battleType == 0)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "�ͻ�ս�ܣ�" << tmpName << "�����4�㾭��ֵ" << endl;
								strcpy(sendBuf, "ս��ʧ�ܣ�");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "�����4�㾭��ֵ\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 4);
							}
							else if (battleType == 1)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "�ͻ�ս�ܣ�" << tmpName << "�����4�㾭��ֵ" << endl;
								strcpy(sendBuf, "ս��ʧ�ܣ�");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "�����4�㾭��ֵ\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 4);
								client->lossPokemon(clntSock);
							}
						}
						else//�ͻ�ʤ��
						{
							client->allBattlePlus();
							client->winBattlePlus();
							(*servPokem).recover();
							if (battleType == 0)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "�ͻ�ʤ����" << tmpName << "�����15�㾭��ֵ" << endl;
								strcpy(sendBuf, "ս��ʤ����");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "�����15�㾭��ֵ\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 15);
							}
							else if (battleType == 1)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "�ͻ�ʤ����" << tmpName << "�����15�㾭��ֵ" << endl;
								strcpy(sendBuf, "ս��ʤ����");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "�����15�㾭��ֵ\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 15);
								client->getPokemon(servPokem);
								strcpy(sendBuf, "�ѻ�ö�ս������\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
								Sleep(10);
							}
						}
						//�ָ�������
						(*servPokem).recover();
						(*clntPokem).recover();
						client->saveAllToFile();
						strcpy(sendBuf, "������һ��ս������Y/N����");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (strcmp("N", receiveBuf) == 0 || strcmp("n", receiveBuf) == 0)
						{
							break;
						}
					}
				}
				else if (strcmp("2", receiveBuf) == 0)//��ѯʤ��
				{
					while (1)
					{
						strcpy(sendBuf, "����Ҫ��ѯʤ�ʵ��û�����");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
						memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						winRate = client->seeWinRate(receiveBuf);
						if (winRate != -1)
						{
							winRate = winRate * 100;
							char tmpRate[1024] = { 0 };
							strcpy(sendBuf, "#seeStart#");
							sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
							memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
							Sleep(10);
							ofstream tmpFile("./TMP/tmp.txt", ios::out);
							tmpFile << winRate;
							tmpFile.close();
							ifstream tmpFile1("./TMP/tmp.txt");
							tmpFile1.getline(tmpRate, sizeof(tmpRate));
							strcpy(sendBuf, "ʤ����");
							strcat(sendBuf, tmpRate);
							strcat(sendBuf, "%\n");
							sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
							memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
							break;
						}
						else
						{
							strcpy(sendBuf, "���޴��ˣ��Ƿ��������룿��Y/N����");
							sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
							memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
							memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
							receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
							if (strcmp("N", receiveBuf) == 0 || strcmp("n", receiveBuf) == 0)
							{
								break;
							}
						}
					}
				}
				else if (strcmp("3", receiveBuf) == 0)//��ѯ����
				{
					switch(client->getquantityBadge())
					{
					case GOLD:
						strcpy(sendBuf, "ӵ�н��ʡ�����������¡���");
						break;
					case SILVER:
						strcpy(sendBuf, "ӵ�����ʡ�����������¡���");
						break;
					case COPPER:
						strcpy(sendBuf, "ӵ��ͭ�ʡ�����������¡���");
						break;
					default:
						strcpy(sendBuf, "û�С�����������¡���");
					}
					switch (client->getadvancedBadge())
					{
					case GOLD:
						strcat(sendBuf, "ӵ�н��ʡ��߼�������¡�\n");
						break;					   
					case SILVER:				   
						strcat(sendBuf, "ӵ�����ʡ��߼�������¡�\n");
						break;					   
					case COPPER:				   
						strcat(sendBuf, "ӵ��ͭ�ʡ��߼�������¡�\n");
						break;
					default:
						strcat(sendBuf, "û�С��߼�������¡�\n");
					}
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				}
				else if (strcmp("4", receiveBuf) == 0)//�˳�
				{
					break;
				}
			}
		}
	}
	else
	{
		cout << "�û�δ��¼" << endl;
	}

	//�ƺ���������˿ͻ�
	CLIENT_DATA* tmpClientData = NULL;
	tmpClientData = pmd;
	if (pmd->prevData)//���ǰ�滹�пͻ�
		pmd->prevData->nextData = pmd->nextData;
	else
		allClients = pmd->nextData;
	if (pmd->nextData)//������滹�пͻ�
		pmd->nextData->prevData = pmd->prevData;
	free(pmd);
	activeUserNum--;

	//�����ǰ��Ծ�û���
	cout << "activeUserNum:" << activeUserNum << endl;
	cout << "���̽���" << endl << endl;
	return 0;
}

//������
int main(int argc, char* argv[])
{
	cout << "System is Initializing..." << endl;

	CLIENT_DATA* preClient = NULL;//��һ�������Ŀͻ���
	CLIENT_DATA* nowClient = NULL;//��ǰ�������û��ͻ���

	//socket��س�ʼ��
	int error;//���󾯸�λ
	int sendLen;//�ɹ����ͳ���
	int receiveLen;//�ɹ����ճ���
	char sendBuf[MAX_BUF_SIZE] = "s";//���ͻ�����
	char receiveBuf[MAX_BUF_SIZE] = { 0 };//���ջ�����
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

	//��ʼ�����⾫���б�
	virtualPokemonList = (char*)malloc(1000 * sizeof(char));
	for (int k = 0; k < 10; k++)
	{
		virtualPokemonName[k] = (char*)malloc(100 * sizeof(char));
		virtualPokemonData[k] = (int*)malloc(9 * sizeof(int));
	}
	strcpy(virtualPokemonList,	"1.Bulbasaur(��������), LV=1, HP=12, ATK=2, DEF=1, SPEED=2.\n"
								"2.Charizard(�����),	LV=1, HP=11, ATK=3, DEF=1, SPEED=2.\n"
								"3.Squirtle(�����), LV=1, HP=10, ATK=2, DEF=2, SPEED=2.\n"
								"4.Caterpie(��ë��), LV=1, HP=10, ATK=3, DEF=1, SPEED=2.\n"
								"5.Pidgeotto(�ȱ���),	LV=1, HP=10, ATK=2, DEF=1, SPEED=1.\n"
								"6.Diglett(����), LV=1, HP=13, ATK=2, DEF=1, SPEED=2.\n"
								"7.Pikachu(Ƥ����), LV=5, HP=30, ATK=12, DEF=5, SPEED=1.\n"
								"8.Snorunt(ѩͯ��), LV=5, HP=27, ATK=15, DEF=3, SPEED=2.\n"
								"9.Dragonite(����), LV=10, HP=50, ATK=22, DEF=11, SPEED=2.\n"
								"10.Pikachu(Ƥ����), LV=15, HP=75, ATK=30, DEF=15, SPEED=1.\n");
	strcpy(virtualPokemonName[0], "Bulbasaur");
	strcpy(virtualPokemonName[1], "Charizard");
	strcpy(virtualPokemonName[2], "Squirtle");
	strcpy(virtualPokemonName[3], "Caterpie");
	strcpy(virtualPokemonName[4], "Pidgeotto");
	strcpy(virtualPokemonName[5], "Diglett");
	strcpy(virtualPokemonName[6], "Pikachu");
	strcpy(virtualPokemonName[7], "Snorunt");
	strcpy(virtualPokemonName[8], "Dragonite");
	strcpy(virtualPokemonName[9], "Pikachu(Powerful)");
	virtualPokemonData[0][0] = GRASS;
	virtualPokemonData[0][1] = BEARABLE;
	virtualPokemonData[0][2] = 0;
	virtualPokemonData[0][3] = 1;
	virtualPokemonData[0][4] = 2;
	virtualPokemonData[0][5] = 12;
	virtualPokemonData[0][6] = 1;
	virtualPokemonData[0][7] = 2;
	virtualPokemonData[0][8] = BLUBASAUR;
	virtualPokemonData[1][0] = FIRE;
	virtualPokemonData[1][1] = POWER;
	virtualPokemonData[1][2] = 0;
	virtualPokemonData[1][3] = 1;
	virtualPokemonData[1][4] = 3;
	virtualPokemonData[1][5] = 11;
	virtualPokemonData[1][6] = 1;
	virtualPokemonData[1][7] = 2;
	virtualPokemonData[1][8] = CHARIZARD;
	virtualPokemonData[2][0] = WATER;
	virtualPokemonData[2][1] = DEDENSIVE;
	virtualPokemonData[2][2] = 0;
	virtualPokemonData[2][3] = 1;
	virtualPokemonData[2][4] = 2;
	virtualPokemonData[2][5] = 10;
	virtualPokemonData[2][6] = 2;
	virtualPokemonData[2][7] = 2;
	virtualPokemonData[2][8] = SQUIRTLE;
	virtualPokemonData[3][0] = BUG;
	virtualPokemonData[3][1] = POWER;
	virtualPokemonData[3][2] = 0;
	virtualPokemonData[3][3] = 1;
	virtualPokemonData[3][4] = 3;
	virtualPokemonData[3][5] = 10;
	virtualPokemonData[3][6] = 1;
	virtualPokemonData[3][7] = 2;
	virtualPokemonData[3][8] = CATERPIE;
	virtualPokemonData[4][0] = FLY;
	virtualPokemonData[4][1] = AGILE;
	virtualPokemonData[4][2] = 0;
	virtualPokemonData[4][3] = 1;
	virtualPokemonData[4][4] = 2;
	virtualPokemonData[4][5] = 10;
	virtualPokemonData[4][6] = 1;
	virtualPokemonData[4][7] = 1;
	virtualPokemonData[4][8] = PIDGEOTTO;
	virtualPokemonData[5][0] = GROUND;
	virtualPokemonData[5][1] = BEARABLE;
	virtualPokemonData[5][2] = 0;
	virtualPokemonData[5][3] = 1;
	virtualPokemonData[5][4] = 2;
	virtualPokemonData[5][5] = 13;
	virtualPokemonData[5][6] = 1;
	virtualPokemonData[5][7] = 2;
	virtualPokemonData[5][8] = DIGLETT;
	virtualPokemonData[6][0] = ELECTRIC;
	virtualPokemonData[6][1] = AGILE;
	virtualPokemonData[6][2] = 0;
	virtualPokemonData[6][3] = 5;
	virtualPokemonData[6][4] = 12;
	virtualPokemonData[6][5] = 30;
	virtualPokemonData[6][6] = 5;
	virtualPokemonData[6][7] = 1;
	virtualPokemonData[6][8] = PIKACHU;
	virtualPokemonData[7][0] = ICE;
	virtualPokemonData[7][1] = POWER;
	virtualPokemonData[7][2] = 0;
	virtualPokemonData[7][3] = 5;
	virtualPokemonData[7][4] = 15;
	virtualPokemonData[7][5] = 27;
	virtualPokemonData[7][6] = 3;
	virtualPokemonData[7][7] = 2;
	virtualPokemonData[7][8] = SNORUNT;
	virtualPokemonData[8][0] = DRAGON;
	virtualPokemonData[8][1] = POWER;
	virtualPokemonData[8][2] = 0;
	virtualPokemonData[8][3] = 10;
	virtualPokemonData[8][4] = 22;
	virtualPokemonData[8][5] = 50;
	virtualPokemonData[8][6] = 11;
	virtualPokemonData[8][7] = 2;
	virtualPokemonData[8][8] = DRAGONITE;
	virtualPokemonData[9][0] = ELECTRIC;
	virtualPokemonData[9][1] = AGILE;
	virtualPokemonData[9][2] = 0;
	virtualPokemonData[9][3] = 15;
	virtualPokemonData[9][4] = 30;
	virtualPokemonData[9][5] = 75;
	virtualPokemonData[9][6] = 15;
	virtualPokemonData[9][7] = 1;
	virtualPokemonData[9][8] = PIKACHU;


	//��ʼ�� DLL
	WSADATA wsaData;
	error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error != 0)
	{
		cout << "��ʼ���׽��ֿ�ʧ��" << endl;
		return 0;
	}

	//�����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//���׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr(ip);  //����
	sockAddr.sin_port = htons(port);  //�˿�
	if (bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "���׽���ʧ��" << endl;
		closesocket(servSock);
		WSACleanup();
		return 0;
	}

	//�������״̬
	if (listen(servSock, 100) < 0)
	{
		cout << "�������ʧ��" << endl;
		closesocket(servSock);
		WSACleanup();
		return 0;
	}

	cout << "System startup is complete. Now, listening client" << endl;

	int tmpData[9] = { FIRE,POWER,0,1,2,10,1,2,2 };//��ʼ������

	allClients = (CLIENT_DATA*)malloc(sizeof(CLIENT_DATA));
	while (1)
	{
		//ѭ�����տͻ����������󲢴��������߳�
		SOCKET* clntSock = new SOCKET;
		SOCKADDR clntAddr;
		int nSize = sizeof(SOCKADDR);
		*clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

		if (activeUserNum == 0)
		{
			allClients = (CLIENT_DATA*)malloc(sizeof(CLIENT_DATA));
			nowClient = allClients;
			nowClient->clientSocket = NULL;
			nowClient->clientUser = NULL;
			nowClient->nextData = NULL;
			nowClient->prevData = NULL;
			nowClient->state = UNLOGIN;
		}
		else
		{
			nowClient = (CLIENT_DATA*)malloc(sizeof(CLIENT_DATA));
			nowClient->clientSocket = NULL;
			nowClient->clientUser = NULL;
			nowClient->nextData = NULL;
			nowClient->prevData = preClient;
			nowClient->state = UNLOGIN;
			preClient->nextData = nowClient;
		}

		nowClient->clientSocket = clntSock;

		if (*clntSock == SOCKET_ERROR)
		{
			cout << "������������ʧ��" << endl;
			closesocket(*clntSock);
		}
		else
		{
			cout << endl << "һ���ͻ��˳������ӵ���������socket�ǣ�" << *clntSock << endl;
			CreateThread(NULL, 0, &ServerThread, nowClient, 0, NULL);
		}

		activeUserNum++;
		preClient = nowClient;
	}
	//�ر��׽���
	closesocket(servSock);

	//��ֹ DLL ��ʹ��
	WSACleanup();

	//�ͷ�����Ŀռ�
	free(virtualPokemonList);
	for (int k = 0; k < 10; k++)
	{
		free(virtualPokemonName[k]);
		free(virtualPokemonData[k]);
	}

	return 0;
}