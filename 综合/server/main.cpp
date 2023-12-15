/************************************************************/
/* @课程名：		C++课程设计	题目二 用户注册与平台登录	*/
/* @作者；			谢睿（2018211208）						*/
/* @教师：			王洪波									*/
/* @最后修改时间：	2020/09/01 19：22						*/
/* @文件名：		main.cpp								*/
/* @文件说明：		主功能代码，用于测试以及功能实现		*/
/*----------------------------------------------------------*/
/* @备注：			本程序遵循任天堂公司习惯用语，使用“宝可*/
/*					梦(Pokemon)”代指宠物小精灵				*/
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

#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


//全局变量区
//int pokemonNumOwned = 0;//玩家拥有的宝可梦数
int expNeeded[14] = { 20,40,60,90,120,160,200,250,300,350,400,500,700,1000 };//升级所需经验值
double effectiveness[10][10] = { {1,   1,   1,   1,   1,   1,   1,   1,   1,   1  },
								 {1,   0.5, 2,   0.5, 2,   1,   1,   1,   2,   0.5},
								 {1,   0.5, 0.5, 1,   0.5, 0.5, 2,   1,   1,   0.5},
								 {1,   2,   0.5, 0.5, 1,   1,   2,   1,   1,   0.5},
								 {1,   0.5, 2,   1,   1,   0.5, 1,   1,   1,   1  },
								 {1,   1,   2,   1,   2,   1,   1,   0.5, 1,   1  },
								 {1,   2,   0.5, 1,   0.5, 0,   1,   2,   1,   1  },
								 {1,   1,   0.5, 2,   1,   2,   0,   0.5, 1,   0.5},
								 {1,   0.5, 2,   0.5, 1,   2,   2,   1,   0.5, 2  },
								 {1,   1,   1,   1,   1,   1,   1,   1,   1,   2  } };//元素相克表
int userNum = 0;//所有注册用户数
int activeUserNum = 0;//当前在线用户
CLIENT_DATA* allClients = NULL;//所有在线用户的链表
char* virtualPokemonList;//用户可选择对战的虚拟精灵列表
char* virtualPokemonName[10];//用户可选择对战的虚拟精灵名字
int* virtualPokemonData[10];//用户可选择对战的虚拟精灵属性


//服务线程
DWORD WINAPI ServerThread(LPVOID lpParameter)
{
	//传入参数处理
	CLIENT_DATA* pmd = (CLIENT_DATA*)lpParameter;
	SOCKET* clntSock = pmd->clientSocket;
	User* client = pmd->clientUser;
	int state = pmd->state;

	int menuFlag = 1;//退出菜单标志位
	int tmpData[9] = { FIRE,POWER,0,1,2,10,1,2,2 };//初始化数据
	char tmpStr[100] = { 0 };//用于拷贝以及比较的临时数组
	int sendLen;//成功发送长度
	int receiveLen;//成功接收长度
	char sendBuf[MAX_BUF_SIZE] = "This is a message from server\n";//发送缓冲区
	char receiveBuf[MAX_BUF_SIZE] = { 0 };//接收缓冲区
	int round = 0;//出招轮数
	double winRate = 0;//胜率

	srand(time(0));

	//主菜单以及登陆工作
	char tmpBuf[32] = { 0 };
	ifstream userFile("./DATA/userData.txt");
	userFile >> tmpBuf;
	userFile >> userNum;
	userFile.close();

	char uName[32] = { 0 };
	char uPass[32] = { 0 };
	int result = 0;
	cout << "客户机连接成功" << endl << endl;
	
	while (menuFlag)
	{
		strcpy(sendBuf, "\n您还未登陆，请选择：\n"
						"1.用户登录\n"
						"2.用户注册\n"
						"3.查看注册用户信息\n"
						"4.查看在线用户\n"
						"5.断开与服务器的连接\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		if (receiveLen < 0)
		{
			cout << "接收失败,客户机已断开" << endl;
			menuFlag = 0;
			break;
		}
		else
		{
			if (strcmp("1", receiveBuf) == 0)//登陆
			{
				cout << "用户登陆" << endl;
				int tryCount = 2;
				while (tryCount >= 0)
				{
					strcpy(sendBuf, "请输入用户名(32字符以下)：\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uName, receiveBuf);
					strcpy(sendBuf, "请输入密码(32字符以下)：\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uPass, receiveBuf);

					client = new User(uName, uPass, 1, result);
					pmd->clientUser = client;
					if (result == 0)
					{
						pmd->state = LOGINED;
						menuFlag = 0;
						strcpy(sendBuf, "登陆成功\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						break;
					}
					else if (result == 1)
					{
						itoa(tryCount, tmpStr, 10);
						strcpy(sendBuf, "登陆失败，"); 
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						strcpy(sendBuf, "用户不存在，还可以尝试");
						strcat(sendBuf, tmpStr);
						strcat(sendBuf, "次\n");
						memset(tmpStr, 0, sizeof(tmpStr));
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						delete client;
						Sleep(10);
					}
					else if (result == 2)
					{
						itoa(tryCount, tmpStr, 10);
						strcpy(sendBuf, "登陆失败，");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						strcpy(sendBuf, "密码错误，还可以尝试");
						strcat(sendBuf, tmpStr);
						strcat(sendBuf, "次\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						delete client;
						Sleep(10);
					}
					else if (result == 3)
					{
						itoa(tryCount, tmpStr, 10);
						strcpy(sendBuf, "登陆失败，");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						strcpy(sendBuf, "请勿重复登陆，还可以尝试");
						strcat(sendBuf, tmpStr);
						strcat(sendBuf, "次\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						delete client;
						Sleep(10);
					}
					tryCount--;
				}
			}
			else if (strcmp("2", receiveBuf) == 0)//注册
			{
				cout << "用户注册" << endl;
				while (1)
				{
					strcpy(sendBuf, "请输入用户名(32字符以下)：\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uName, receiveBuf);
					strcpy(sendBuf, "请输入密码(32字符以下)：\n");
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
					memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
					receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
					strcpy(uPass, receiveBuf);
					client = new User(uName, uPass, 0, result);
					if (result == 0)//注册成功
					{
						pmd->clientUser = client;
						pmd->state = LOGINED;
						menuFlag = 0;
						strcpy(sendBuf, "注册成功，已登陆\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						userNum++;
						strcpy(sendBuf, "获得3只初始宝可梦\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						break;
					}
					else if (result == 1)//注册失败，用户名重复
					{
						strcpy(sendBuf, "注册失败，");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						strcpy(sendBuf, "用户名重复\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
					}
				}
			}
			else if (strcmp("3", receiveBuf) == 0)//查看用户信息
			{
				strcpy(sendBuf, "用户信息如下：\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
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
					//cout << "用户：" << dataName << ", ";
					strcpy(sendBuf, "用户：");
					strcat(sendBuf, dataName);
					strcat(sendBuf, ", ");
					while (strcmp("#pokemon#", dataName) != 0)//定位宝可梦数据位置
					{
						userFile >> dataName;
					}
					userFile >> dataNum;
					//cout << "有" << dataNum << "只宝可梦：" << endl;
					itoa(dataNum, tmpStr, 10);
					strcat(sendBuf, "有");
					strcat(sendBuf, tmpStr);
					strcat(sendBuf, "只宝可梦：\n");
					memset(tmpStr, 0, sizeof(tmpStr));
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
					Sleep(10);
					for (int j = 0; j < dataNum; j++)
					{
						//cout << j + 1 << ".";
						userFile >> dataName; //cout << "宝可梦种族：" << dataName << ", ";
						strcpy(sendBuf, "宝可梦种族：");
						strcat(sendBuf, dataName);
						strcat(sendBuf, ", ");
						userFile >> bufNum; //cout << data[0] << endl; //元素 
						userFile >> bufNum;//类型
						userFile >> dataName; //cout << "宝可梦名字：" << dataName << ", ";
						strcat(sendBuf, "宝可梦名字：");
						strcat(sendBuf, dataName);
						strcat(sendBuf, ", ");
						userFile >> bufNum;//EXP
						userFile >> bufNum; //cout << "等级：" << bufNum << endl;//LV
						itoa(bufNum, tmpStr, 10);
						strcat(sendBuf, "等级：");
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
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
					}
					//cout << endl;
					userFile >> dataName;
					userFile.getline(dataName, 100);
				}
				Sleep(10);
				strcpy(sendBuf, "###end###");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				userFile.close();
				Sleep(10);
			}
			else if (strcmp("4", receiveBuf) == 0)//查看在线用户
			{
				//cout << "当前在线用户：" << endl;
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
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						//cout << thisName << endl;
						Sleep(10);
					}
					showData = showData->nextData;
				}
				Sleep(10);
				strcpy(sendBuf, "###end###");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else if (strcmp("5", receiveBuf) == 0)//退出
			{
				pmd->state = UNLOGIN;
				menuFlag = 0;
				break;
			}
			else
			{
				cout << "指令错误" << endl;
			}
		}
	}
	//system("pause");

	//退出主菜单，进入子菜单或结束进程
	int battleWith = 0;//与服务器对战的宝可梦编号
	Pokemon* servPokem;//给服务器新建宝可梦
	Pokemon* clntPokem;//给用户新建宝可梦
	if (pmd->state == LOGINED)//登陆成功
	{
		while (1)
		{
			strcpy(sendBuf, "功能选择：\n"
				"1.进行对战\n"
				"2.查看胜率\n"
				"3.查看徽章\n"
				"4.退出登陆并结束程序\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
			receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
			if (receiveLen < 0)
			{
				cout << "接收失败,客户机已断开" << endl;
				break;
			}
			else
			{
				if (strcmp("1", receiveBuf) == 0)//对战
				{
					//client->loadPokemon();
					//client->selectPokemon(clntSock);
					//system("pause");
					while (1)
					{
						char tmpName[32] = { 0 };
						int tmpStatus[7] = { 0 };
						int autoBattle = 0;//是否自动对战 0否1是
						int battleType = 0;//战斗类型 0升级1决斗

						strcpy(sendBuf, "选择比赛类型：\n"
							"1.升级赛\n"
							"2.决斗赛\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (receiveLen < 0) cout << "接收失败,客户机已断开" << endl;
						else
						{
							if (strcmp("1", receiveBuf) == 0)battleType = 0;
							else if (strcmp("2", receiveBuf) == 0)battleType = 1;
							else cout << "指令错误" << endl;
						}
						strcpy(sendBuf, "选择战斗模式：\n"
							"1.自动战斗(系统随机使用双方宝可梦的技能)\n"
							"2.手动战斗(用户自行选择双方宝可梦的技能)\n");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (receiveLen < 0)
						{
							cout << "接收失败,客户机已断开" << endl;
							break;
						}
						else
						{
							if (strcmp("1", receiveBuf) == 0)autoBattle = 1;
							else if (strcmp("2", receiveBuf) == 0)autoBattle = 0;
							else cout << "指令错误" << endl;
						}
						strcpy(sendBuf, "选择对战宝可梦：\n");
						strcat(sendBuf, virtualPokemonList);
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (receiveLen < 0)
						{
							cout << "接收失败,客户机已断开" << endl;
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

						client->loadPokemon();//载入宝可梦
						client->selectPokemon(clntSock);//选择出战宝可梦
						clntPokem = client->usingPokemon;//使用宝可梦

						while ((*clntPokem).getHP() > 0 && (*servPokem).getHP() > 0)//如果双方均可继续战斗
						{
							//竞速制
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

							/*回合制
							if ((*servPokem).getSPEED() <= (*clntPokem).getSPEED())//速度快的宝可梦先手，一样则服务器先手
							{
								cout << "服务器先手" << endl;
								(*servPokem).attack((*clntPokem));
								if ((*clntPokem).getHP() == 0) break;
								(*clntPokem).attack((*servPokem));
								cout << "回合结束，进入下一回合" << endl << endl;
							}
							else
							{
								cout << "客户端先手" << endl;
								(*clntPokem).attack((*servPokem));
								if ((*servPokem).getHP() == 0) break;
								(*servPokem).attack((*clntPokem));
								cout << "回合结束，进入下一回合" << endl << endl;
							}
							*/
						}
						strcpy(sendBuf, "#battleOver#");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						Sleep(10);
						//对战结束，收益计算
						if ((*clntPokem).getHP() == 0)//如果客户宝可梦无法战斗，则服务器胜利
						{
							client->allBattlePlus();
							if (battleType == 0)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "客户战败，" << tmpName << "获得了4点经验值" << endl;
								strcpy(sendBuf, "战斗失败，");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "获得了4点经验值\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 4);
							}
							else if (battleType == 1)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "客户战败，" << tmpName << "获得了4点经验值" << endl;
								strcpy(sendBuf, "战斗失败，");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "获得了4点经验值\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 4);
								client->lossPokemon(clntSock);
							}
						}
						else//客户胜利
						{
							client->allBattlePlus();
							client->winBattlePlus();
							(*servPokem).recover();
							if (battleType == 0)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "客户胜利，" << tmpName << "获得了15点经验值" << endl;
								strcpy(sendBuf, "战斗胜利，");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "获得了15点经验值\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 15);
							}
							else if (battleType == 1)
							{
								(*clntPokem).getStatus(tmpName, tmpStatus);
								cout << "客户胜利，" << tmpName << "获得了15点经验值" << endl;
								strcpy(sendBuf, "战斗胜利，");
								strcat(sendBuf, tmpName);
								strcat(sendBuf, "获得了15点经验值\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
								Sleep(10);
								(*clntPokem).levelUp(clntSock, 15);
								client->getPokemon(servPokem);
								strcpy(sendBuf, "已获得对战宝可梦\n");
								sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
								memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
								Sleep(10);
							}
						}
						//恢复宝可梦
						(*servPokem).recover();
						(*clntPokem).recover();
						client->saveAllToFile();
						strcpy(sendBuf, "继续下一场战斗？（Y/N）：");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						if (strcmp("N", receiveBuf) == 0 || strcmp("n", receiveBuf) == 0)
						{
							break;
						}
					}
				}
				else if (strcmp("2", receiveBuf) == 0)//查询胜率
				{
					while (1)
					{
						strcpy(sendBuf, "输入要查询胜率的用户名：");
						sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
						memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
						memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
						receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
						winRate = client->seeWinRate(receiveBuf);
						if (winRate != -1)
						{
							winRate = winRate * 100;
							char tmpRate[1024] = { 0 };
							strcpy(sendBuf, "#seeStart#");
							sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
							memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
							Sleep(10);
							ofstream tmpFile("./TMP/tmp.txt", ios::out);
							tmpFile << winRate;
							tmpFile.close();
							ifstream tmpFile1("./TMP/tmp.txt");
							tmpFile1.getline(tmpRate, sizeof(tmpRate));
							strcpy(sendBuf, "胜率是");
							strcat(sendBuf, tmpRate);
							strcat(sendBuf, "%\n");
							sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
							memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
							break;
						}
						else
						{
							strcpy(sendBuf, "查无此人，是否重新输入？（Y/N）：");
							sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
							memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
							memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
							receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
							if (strcmp("N", receiveBuf) == 0 || strcmp("n", receiveBuf) == 0)
							{
								break;
							}
						}
					}
				}
				else if (strcmp("3", receiveBuf) == 0)//查询徽章
				{
					switch(client->getquantityBadge())
					{
					case GOLD:
						strcpy(sendBuf, "拥有金质“宠物个数徽章”，");
						break;
					case SILVER:
						strcpy(sendBuf, "拥有银质“宠物个数徽章”，");
						break;
					case COPPER:
						strcpy(sendBuf, "拥有铜质“宠物个数徽章”，");
						break;
					default:
						strcpy(sendBuf, "没有“宠物个数徽章”，");
					}
					switch (client->getadvancedBadge())
					{
					case GOLD:
						strcat(sendBuf, "拥有金质“高级宠物徽章”\n");
						break;					   
					case SILVER:				   
						strcat(sendBuf, "拥有银质“高级宠物徽章”\n");
						break;					   
					case COPPER:				   
						strcat(sendBuf, "拥有铜质“高级宠物徽章”\n");
						break;
					default:
						strcat(sendBuf, "没有“高级宠物徽章”\n");
					}
					sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
					memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				}
				else if (strcmp("4", receiveBuf) == 0)//退出
				{
					break;
				}
			}
		}
	}
	else
	{
		cout << "用户未登录" << endl;
	}

	//善后工作，清除此客户
	CLIENT_DATA* tmpClientData = NULL;
	tmpClientData = pmd;
	if (pmd->prevData)//如果前面还有客户
		pmd->prevData->nextData = pmd->nextData;
	else
		allClients = pmd->nextData;
	if (pmd->nextData)//如果后面还有客户
		pmd->nextData->prevData = pmd->prevData;
	free(pmd);
	activeUserNum--;

	//输出当前活跃用户数
	cout << "activeUserNum:" << activeUserNum << endl;
	cout << "进程结束" << endl << endl;
	return 0;
}

//主函数
int main(int argc, char* argv[])
{
	cout << "System is Initializing..." << endl;

	CLIENT_DATA* preClient = NULL;//上一个操作的客户端
	CLIENT_DATA* nowClient = NULL;//当前操作的用户客户端

	//socket相关初始化
	int error;//错误警告位
	int sendLen;//成功发送长度
	int receiveLen;//成功接收长度
	char sendBuf[MAX_BUF_SIZE] = "s";//发送缓冲区
	char receiveBuf[MAX_BUF_SIZE] = { 0 };//接收缓冲区
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

	//初始化虚拟精灵列表
	virtualPokemonList = (char*)malloc(1000 * sizeof(char));
	for (int k = 0; k < 10; k++)
	{
		virtualPokemonName[k] = (char*)malloc(100 * sizeof(char));
		virtualPokemonData[k] = (int*)malloc(9 * sizeof(int));
	}
	strcpy(virtualPokemonList,	"1.Bulbasaur(妙蛙种子), LV=1, HP=12, ATK=2, DEF=1, SPEED=2.\n"
								"2.Charizard(喷火龙),	LV=1, HP=11, ATK=3, DEF=1, SPEED=2.\n"
								"3.Squirtle(杰尼龟), LV=1, HP=10, ATK=2, DEF=2, SPEED=2.\n"
								"4.Caterpie(绿毛虫), LV=1, HP=10, ATK=3, DEF=1, SPEED=2.\n"
								"5.Pidgeotto(比比鸟),	LV=1, HP=10, ATK=2, DEF=1, SPEED=1.\n"
								"6.Diglett(地鼠), LV=1, HP=13, ATK=2, DEF=1, SPEED=2.\n"
								"7.Pikachu(皮卡丘), LV=5, HP=30, ATK=12, DEF=5, SPEED=1.\n"
								"8.Snorunt(雪童子), LV=5, HP=27, ATK=15, DEF=3, SPEED=2.\n"
								"9.Dragonite(快龙), LV=10, HP=50, ATK=22, DEF=11, SPEED=2.\n"
								"10.Pikachu(皮卡丘), LV=15, HP=75, ATK=30, DEF=15, SPEED=1.\n");
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


	//初始化 DLL
	WSADATA wsaData;
	error = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (error != 0)
	{
		cout << "初始化套接字库失败" << endl;
		return 0;
	}

	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr(ip);  //本机
	sockAddr.sin_port = htons(port);  //端口
	if (bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		cout << "绑定套接字失败" << endl;
		closesocket(servSock);
		WSACleanup();
		return 0;
	}

	//进入监听状态
	if (listen(servSock, 100) < 0)
	{
		cout << "进入监听失败" << endl;
		closesocket(servSock);
		WSACleanup();
		return 0;
	}

	cout << "System startup is complete. Now, listening client" << endl;

	int tmpData[9] = { FIRE,POWER,0,1,2,10,1,2,2 };//初始化数据

	allClients = (CLIENT_DATA*)malloc(sizeof(CLIENT_DATA));
	while (1)
	{
		//循环接收客户端连接请求并创建服务线程
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
			cout << "接收连接请求失败" << endl;
			closesocket(*clntSock);
		}
		else
		{
			cout << endl << "一个客户端尝试连接到服务器，socket是：" << *clntSock << endl;
			CreateThread(NULL, 0, &ServerThread, nowClient, 0, NULL);
		}

		activeUserNum++;
		preClient = nowClient;
	}
	//关闭套接字
	closesocket(servSock);

	//终止 DLL 的使用
	WSACleanup();

	//释放申请的空间
	free(virtualPokemonList);
	for (int k = 0; k < 10; k++)
	{
		free(virtualPokemonName[k]);
		free(virtualPokemonData[k]);
	}

	return 0;
}