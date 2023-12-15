/************************************************************/
/* @课程名：		C++课程设计	题目二 用户注册与平台登录	*/
/* @作者；			谢睿（2018211208）						*/
/* @教师：			王洪波									*/
/* @最后修改时间：	2020/08/23 17：07						*/
/* @文件名：		server.h								*/
/* @文件说明：		定义服务端操作							*/
/*----------------------------------------------------------*/
/* @备注：			本程序遵循任天堂公司习惯用语，使用“宝可*/
/*					梦(Pokemon)”代指宠物小精灵				*/
/************************************************************/

#ifndef Server_h
#define Server_h

#include"PokemonList.h"
#include"header.h"
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<stdio.h>
#include<string.h>
using namespace std;

extern int userNum;//外部变量
extern int activeUserNum;//外部变量

#define GOLD 1//金
#define SILVER 2//银
#define COPPER 3//铜



class User//用户
{
private:
	char username[32];//用户名
	char password[32];//密码
	Pokemon* pokemonOwned[32];//拥有的精灵，背包最多32只
	int pokemonNum;//拥有精灵数量
	int quantityBadge;//精灵数量徽章
	int advancedBadge;//高级精灵徽章
	int winBattleNum;//胜场数
	int allBattleNum;//总场数
	void distributePokemon(int type, char* newName, int* data, int index, int newSkillNum, const SKILL_DATA_ITEM* skills);//随机分配宝可梦
	int sameUserJudge(const char* uName);//重名检测
	void saveData(const char* uName, const char* uPass);//新建用户数据存入文件
public:
	User();//构造
	User(const char* uName, const char* uPass, int type, int& result);//构造
	User(const User& u);//构造
	~User();//析构
	Pokemon* usingPokemon;//正在使用的宝可梦
	int login(const char* uName, const char* uPass);//登陆函数
	int loadPokemon();//载入宝可梦
	void showPokemon();//展示宝可梦（测试用）
	void selectPokemon(SOCKET* clntSock);//选择出战宝可梦
	void getUsername(char* thisName);//获取用户名
	void lossPokemon(SOCKET* clntSock);//丢弃宝可梦
	void getPokemon(Pokemon* aPokemon);//获得宝可梦
	void winBattlePlus();//胜场加一
	void allBattlePlus();//总场数加一
	void saveAllToFile();//用户数据储存
	double seeWinRate(char* uName);//展示胜率
	int getquantityBadge();//获取数量徽章
	int getadvancedBadge();//获取高级徽章
};

typedef struct clientData//用户简略信息结构
{
	User* clientUser;//User对象指针
	SOCKET* clientSocket;//套接字指针
	int state;//客户状态 0，1，2：未登录，已登陆，对战中
	clientData* prevData;//指向上一个客户的指针
	clientData* nextData;//指向下一个客户的指针
}CLIENT_DATA;

extern CLIENT_DATA* allClients;//所有在线用户的链表

void User::distributePokemon(int type, char* newName, int* data, int index, int newSkillNum, const SKILL_DATA_ITEM* skills)
{
	int tmpData[9] = { NORMAL,POWER,0,1,2,10,1,2,0 };//初始化数据
	char tmpName[32] = { 0 };
	int tmpStatus[7] = { 0 };
	int typeIndex = 0;
	if (type == 0)//随机分配
	{
		typeIndex = *data;
	}
	else if (type == 1 || type == 2)//按输入数据分配
	{
		typeIndex = data[8];
		strcpy(tmpName, newName);
		for (int i = 0; i < 9; i++)
		{
			tmpData[i] = data[i];
		}
	}
	
	switch (typeIndex)
	{
	case 1:
		tmpData[8] = BLUBASAUR;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "bulbasaur");
			pokemonOwned[index] = new Bulbasaur(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Bulbasaur(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 2:
		tmpData[8] = CHARIZARD;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "charizard");
			pokemonOwned[index] = new Charizard(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Charizard(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 3:
		tmpData[8] = SQUIRTLE;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "squirtle");
			pokemonOwned[index] = new Squirtle(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Squirtle(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 4:
		tmpData[8] = CATERPIE;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "caterpie");
			pokemonOwned[index] = new Caterpie(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Caterpie(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 5:
		tmpData[8] = PIDGEOTTO;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "pidgeotto");
			pokemonOwned[index] = new Pidgeotto(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Pidgeotto(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 6:
		tmpData[8] = DIGLETT;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "diglett");
			pokemonOwned[index] = new Diglett(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Diglett(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 7:
		tmpData[8] = PIKACHU;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "pikachu");
			pokemonOwned[index] = new Pikachu(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Pikachu(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 8:
		tmpData[8] = SNORUNT;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "snorunt");
			pokemonOwned[index] = new Snorunt(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Snorunt(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	case 9:
		tmpData[8] = DRAGONITE;
		if (type == 0 || type == 2)
		{
			strcpy(tmpName, "dragonite");
			pokemonOwned[index] = new Dragonite(tmpName, tmpData);
		}
		else if (type == 1)
		{
			pokemonOwned[index] = new Dragonite(tmpName, tmpData, newSkillNum, skills);
		}
		break;
	default:
		break;
	}
	pokemonOwned[index]->getStatus(tmpName, tmpStatus);
	if (type == 0 || type == 2)
	{
		cout << "获得精灵：" << tmpName << endl << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;

	}
	else if (type == 1)//按输入数据分配
	{
		cout << "载入精灵：" << tmpName << endl << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;

	}
}
int User::sameUserJudge(const char* uName)
{
	char cmpName[32] = { 0 };
	ifstream userFile("./DATA/userData.txt");
	userFile.getline(cmpName, 31);
	userFile.getline(cmpName, 31);
	for (int i = 0; i < userNum ; i++)
	{
		userFile >> cmpName;
		//cout << cmpName << endl;
		if (strcmp(uName, cmpName) == 0)//重名
		{
			userFile.close();
			return 1;
		}
		userFile >> cmpName;
		while (strcmp("##end##", cmpName) != 0) 
		{
			userFile >> cmpName;
			//cout << cmpName << endl;
		}
	}
	userFile.close();
	return 0;
}
void User::saveData(const char* uName, const char* uPass)
{
	ofstream destFile("./DATA/userData.txt", ios::app);
	destFile << uName << endl;
	destFile << uPass << endl;
	destFile << "#winRate#" << endl;
	destFile << "0 0" << endl;
	destFile << "#badge#" << endl;
	destFile << "0 0" << endl;
	destFile << "#pokemon#" << endl;
	destFile << "0" << endl;
	destFile << "##end##" << endl;
	destFile.close();

	ifstream userFile("./DATA/userData.txt");
	ofstream newFile("./DATA/newUserData.txt", ios::out);
	char cmpData[1024];
	int oldNum = 0;
	userFile >> cmpData;
	userFile >> oldNum;
	newFile << "userNum ";
	newFile << oldNum + 1;
	while (userFile.getline(cmpData, sizeof(cmpData)))
	{
		newFile << cmpData << endl;
	}
	userFile.close();
	newFile.close();
	remove("./DATA/userData.txt");
	//cout << endl << errno << endl;
	rename("./DATA/newUserData.txt", "./DATA/userData.txt");//重命名
	//cout << endl << errno << endl;
}
User::User()
{
	strcpy(username, "user");
	char index[5];
	itoa(userNum, index, 10);
	strcat(username, index);
	strcpy(password, "123456");
	cout << "创建用户：" << username << " ，密码为：" << password << endl;
	winBattleNum = 0;
	allBattleNum = 0;
	pokemonNum = 0;
	//srand((int)time(0));
	int randPokemon;
	for (int i = 0; i < 3; i++)
	{
		randPokemon = rand() % 9 + 1;
		distributePokemon(0, NULL, &randPokemon, i, 0, NULL);
	}
}
User::User(const char* uName, const char* uPass, int type, int& result)
{
	if (type == 0)//注册
	{
		if (sameUserJudge(uName))
		{
			cout << "用户名重复" << endl;
			result = 1;//注册失败
		}
		else
		{
			strcpy(username, uName);
			strcpy(password, uPass);
			cout << "创建用户：" << username << " ，密码为：" << password << endl;
			winBattleNum = 0;
			allBattleNum = 0;
			saveData(username, password);
			pokemonNum = 0;
			quantityBadge = 0;
			advancedBadge = 0;
			//srand((int)time(0));
			int randPokemon;
			for (int i = 0; i < 3; i++)
			{
				randPokemon = rand() % 9 + 1;
				distributePokemon(0, NULL, &randPokemon, i, 0, NULL);
				pokemonNum++;
			}
			saveAllToFile();
			result = 0;//注册成功
		}
	}
	else if (type == 1)//登陆
	{
		strcpy(username, uName);
		strcpy(password, uPass);
		cout << "登陆用户：" << username << endl;
		pokemonNum = 0;
		result = login(uName, uPass);
	}
	
}
User::User(const User& u)
{
	cout << "调用user的拷贝构造函数" << endl;
	system("pause");
	
	strcpy(username, u.username);
	strcpy(password, u.password);
	pokemonNum = u.pokemonNum;
}
User::~User()
{
	for (int i = 0; i < pokemonNum; i++)
	{
//		delete[] pokemonOwned[i];
	}
}
int User::login(const char* uName, const char* uPass)
{
	char cmpName[500] = { 0 };
	char cmpPass[32] = { 0 };
	int multiLoginFlag = 0;
	ifstream userFile("./DATA/userData.txt");
	userFile.getline(cmpName, 500);
	userFile.getline(cmpName, 500);
	for (int i = 0; i < userNum; i++)
	{
		userFile >> cmpName;
		if (strcmp(uName, cmpName) == 0)//存在此用户
		{
			userFile >> cmpPass;
			if (strcmp(uPass, cmpPass) == 0)//如果密码正确
			{
				CLIENT_DATA* showData = allClients;
				char thisName[32] = { 0 };
				while (showData)
				{
					if (showData->state == LOGINED)
					{
						showData->clientUser->getUsername(thisName);
						if (strcmp(thisName, uName) == 0)
						{
							multiLoginFlag = 1;
							break;
						}
					}
					showData = showData->nextData;
				}
				if (multiLoginFlag == 0)
				{
					userFile >> cmpName;
					while (strcmp("#winRate#", cmpName) != 0)//定位比赛场数
					{
						userFile >> cmpName;
					}
					userFile >> winBattleNum;
					userFile >> allBattleNum; 
					while (strcmp("#badge#", cmpName) != 0)//定位徽章
					{
						userFile >> cmpName;
					}
					userFile >> quantityBadge;
					userFile >> advancedBadge;
					//cout << "登陆成功！欢迎回来：" << uName << endl;
					userFile.close();
					return 0;
				}
				else
				{
					cout << "重复登陆" << endl;
					userFile.close();
					return 3;
				}
			}
			else
			{
				cout << "密码错误" << endl;
				userFile.close();
				return 2;
			}
		}
		userFile >> cmpName;
		while (strcmp("##end##", cmpName) != 0)
		{
			userFile >> cmpName;
		}
	}
	cout << "用户不存在" << endl;
	userFile.close();
	return 1;
}
int User::loadPokemon()
{
	char cmpName[32] = { 0 };
	char pokeName[32] = { 0 };
	int data[9] = { 0 };
	SKILL_DATA_ITEM skills[4] = { 0 };
	int skillNum = 0;
	char skillName[32] = { 0 };
	ifstream userFile("./DATA/userData.txt");
	userFile.getline(cmpName, 31);
	userFile.getline(cmpName, 31);
	for (int i = 0; i < userNum; i++)
	{
		userFile >> cmpName;
		//cout << cmpName << endl;
		if (strcmp(username, cmpName) == 0)//寻找用户数据位置
		{
			while (strcmp("#pokemon#", cmpName) != 0)//定位宝可梦数据位置
			{
				userFile >> cmpName;
			}
			break;
		}
		while (strcmp("##end##", cmpName) != 0)
		{
			userFile >> cmpName;
		}
	}
	userFile >> pokemonNum; //cout << pokemonNum << endl;
	for (int i = 0; i < pokemonNum; i++)
	{
		userFile >> pokeName; //cout << pokeName << endl;
		userFile >> data[0]; //cout << data[0] << endl; //元素 
		userFile >> data[1];//类型
		userFile >> pokeName; //cout << pokeName << endl;
		userFile >> data[2];//EXP
		userFile >> data[3];//LV
		userFile >> data[4];//ATK
		userFile >> data[5];//HP
		userFile >> data[6];//DEF
		userFile >> data[7];//SPEED
		userFile >> data[8];//Index

		userFile >> skillNum;
		for (int j = 0; j < skillNum; j++)
		{
			userFile >> skillName;// cout << skillName << endl;
			strcpy(skills[j].name, skillName);
			userFile >> skills[j].elem;
			userFile >> skills[j].ex;
		}
		distributePokemon(1, pokeName, data, i, skillNum, skills);
	}
	userFile.close();
	return 0;
}
void User::showPokemon()
{
	char tmpName[32] = { 0 };
	int tmpStatus[7] = { 0 };
	for (int i = 0; i < pokemonNum; i++)
	{
		pokemonOwned[i]->getStatus(tmpName, tmpStatus);
		cout << "宝可梦：" << tmpName << endl << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;

	}
}
void User::selectPokemon(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	char tmpName[32] = { 0 };
	int tmpStatus[7] = { 0 };
	int select = 0;
	int flag = 1;
	cout << "用户选择宝可梦：\n";
	//cout << "您有以下宝可梦：" << endl;
	strcpy(sendBuf, "您有以下宝可梦：\n");
	for (int i = 0; i < pokemonNum; i++)
	{
		pokemonOwned[i]->getStatus(tmpName, tmpStatus);
		//cout << i+1 << ". " << tmpName << " " << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;
		itoa(i + 1, tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ". ");
		strcat(sendBuf, tmpName);
		strcat(sendBuf, " LV= ");
		itoa(tmpStatus[1], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ", ATK = ");
		itoa(tmpStatus[2], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ", HP = ");
		itoa(tmpStatus[3], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ", DEF = ");
		itoa(tmpStatus[4], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, "\n");
	}
	//cout << "选择一只宝可梦进行对战：";
	strcat(sendBuf, "选择一只宝可梦进行对战：");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	while (flag)
	{
		//cin >> select;
		//select--;
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		select = atoi(receiveBuf);
		select--;
		if (select >= 0 && select < pokemonNum)
		{
			flag = 0;
		}
		else
		{
			//cout << "编号错误，请重新输入：";
			strcat(sendBuf, "编号错误，请重新输入：");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
	cout << "选择了" << select + 1 << "号宝可梦" << endl;
	usingPokemon = pokemonOwned[select];
	strcat(sendBuf, "#selectEnd#");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
}

void User::getUsername(char* thisName)
{
	strcpy(thisName, username);
}

void User::lossPokemon(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	char tmpName[32] = { 0 };
	int tmpStatus[7] = { 0 };
	int select = 0;
	int flag = 1;
	int decided = -1;
	int sendOutNum = 0;
	//cout << "您有以下宝可梦：" << endl;
	
	strcpy(sendBuf, "#lossPokemon#");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);

	strcpy(sendBuf, "请从以下宝可梦中选一只送出：\n");
	int sendOut[3] = { -1,-1,-1 };
	if (pokemonNum >= 3)
	{
		sendOutNum = 3;
		//srand((int)time(0));
		for (int j = 0; j < 3; j++)
		{
			flag = 1;
			while (flag)
			{
				flag = 0;
				sendOut[j] = rand() % pokemonNum;
				for (int k = 0; k < j; k++)
				{
					if (sendOut[j] == sendOut[k]) flag = 1;
				}
			}
		}
	}
	else if (pokemonNum == 2)
	{
		sendOutNum = 2;
		sendOut[0] = 0;
		sendOut[1] = 1;
	}
	else if (pokemonNum == 1)
	{
		sendOutNum = 1;
		sendOut[0] = 0;
	}
	for (int i = 0; (i < 3 && (sendOut[i] != -1)); i++)
	{
		pokemonOwned[sendOut[i]]->getStatus(tmpName, tmpStatus);
		itoa(i + 1, tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ". ");
		strcat(sendBuf, tmpName);
		strcat(sendBuf, " LV= ");
		itoa(tmpStatus[1], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ", ATK = ");
		itoa(tmpStatus[2], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ", HP = ");
		itoa(tmpStatus[3], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ", DEF = ");
		itoa(tmpStatus[4], tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, "\n");
	}
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
	receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
	decided = atoi(receiveBuf);
	decided--;
	while (1)
	{
		if (decided >= 0 && decided < sendOutNum)
		{
			break;
		}
		else
		{
			strcpy(sendBuf, "输入错误，请重新输入：");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
			receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
			decided = atoi(receiveBuf);
		}
	}
	//delete pokemonOwned[sendOut[decided]];
	for (int j = sendOut[decided]; j < pokemonNum; j++)
	{
		pokemonOwned[j] = pokemonOwned[j + 1];
	}
	pokemonOwned[pokemonNum - 1] = NULL;
	pokemonNum--;
	if (pokemonNum == 0)
	{
		pokemonNum++;
		//srand((int)time(0));
		int randPokemon= rand() % 9 + 1;
		distributePokemon(0, NULL, &randPokemon, 0, 0, NULL);
		strcpy(sendBuf, "您的宝可梦已全部送出，系统自动分配一只1级宝可梦：\n");
		for (int i = 0; i < pokemonNum; i++)
		{
			pokemonOwned[i]->getStatus(tmpName, tmpStatus);
			//cout << i + 1 << ". " << tmpName << " " << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;
			itoa(i + 1, tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, ". ");
			strcat(sendBuf, tmpName);
			strcat(sendBuf, " LV= ");
			itoa(tmpStatus[1], tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, ", ATK = ");
			itoa(tmpStatus[2], tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, ", HP = ");
			itoa(tmpStatus[3], tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, ", DEF = ");
			itoa(tmpStatus[4], tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, "\n");
		}
		strcat(sendBuf, "请给其起名：");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		pokemonOwned[0]->setName(receiveBuf);
	}
	strcpy(sendBuf, "#lossEnd#");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
}
void User::getPokemon(Pokemon* aPokemon)
{
	char tmpName[32] = { 0 };
	int tmpStatus[9] = { 0 };
	aPokemon->getAllInf(tmpName, tmpStatus);
	distributePokemon(2, tmpName, tmpStatus, pokemonNum, 0, NULL);
	pokemonNum++;
}

void User::winBattlePlus()
{
	winBattleNum++;
}
void User::allBattlePlus()
{
	allBattleNum++;
}
void User::saveAllToFile()
{
	ifstream userFile("./DATA/userData.txt");
	ofstream newFile("./DATA/newUserData.txt", ios::out);
	char cmpData[1024];
	int finded = 0;
	int lv15Num = 0;
	char tmpName[32] = { 0 };
	int tmpStatus[9] = { 0 };
	int tmpInt;
	SKILL_DATA_ITEM skills[4] = { 0 };
	while (userFile.getline(cmpData, sizeof(cmpData)))
	{
		newFile << cmpData << endl;
		if (strcmp("##end##", cmpData) == 0)
		{
			userFile.getline(cmpData, sizeof(cmpData));
			newFile << cmpData << endl;//用户名
			if (strcmp(username, cmpData) == 0)//找到用户数据
			{
				userFile.getline(cmpData, sizeof(cmpData));
				newFile << cmpData << endl;//密码
				newFile << "#winRate#" << endl;
				newFile << winBattleNum << " " << allBattleNum << endl;
				newFile << "#badge#" << endl;
				if (pokemonNum >= 0 && pokemonNum < 5)
				{
					newFile << "0" << " ";
				}
				else if (pokemonNum >= 5 && pokemonNum < 10)
				{
					newFile << "3" << " ";
				}
				else if (pokemonNum >= 10 && pokemonNum < 20)
				{
					newFile << "2" << " ";
				}
				else if (pokemonNum >= 20)
				{
					newFile << "1" << " ";
				}
				for (int i = 0; i < pokemonNum; i++)//计算15级宝可梦个数
				{
					pokemonOwned[i]->getStatus(tmpName, tmpStatus);
					if (tmpStatus[1] == 15) lv15Num++;
				}
				if (lv15Num >= 0 && lv15Num < 5)
				{
					newFile << "0" << endl;
				}
				else if (lv15Num >= 5 && lv15Num < 10)
				{
					newFile << "3" << endl;
				}
				else if (lv15Num >= 10 && lv15Num < 20)
				{
					newFile << "2" << endl;
				}
				else if (lv15Num >= 20)
				{
					newFile << "1" << endl;
				}
				newFile << "#pokemon#" << endl;
				newFile << pokemonNum << endl;
				for (int i = 0; i < pokemonNum; i++)//存储每个宝可梦
				{
					pokemonOwned[i]->getAllInf(tmpName, tmpStatus);
					switch (tmpStatus[8])
					{
					case  BLUBASAUR:
						newFile << "blubasaur ";
						break;
					case CHARIZARD:
						newFile << "charizard ";
						break;
					case SQUIRTLE:
						newFile << "squirtle ";
						break;
					case CATERPIE:
						newFile << "caterpie ";
						break;
					case PIDGEOTTO:
						newFile << "pidgeotto ";
						break;
					case DIGLETT:
						newFile << "diglett ";
						break;
					case PIKACHU:
						newFile << "pikachu ";
						break;
					case SNORUNT:
						newFile << "snorunt ";
						break;
					case DRAGONITE:
						newFile << "dragonite ";
						break;
					dafault:
						break;
					}
					newFile << tmpStatus[0]; //cout << data[0] << endl; //元素 
					newFile << " ";
					newFile << tmpStatus[1];//类型
					newFile << " ";
					newFile << tmpName; //cout << pokeName << endl;
					newFile << " ";
					newFile << tmpStatus[2];//EXP
					newFile << " ";
					newFile << tmpStatus[3];//LV
					newFile << " ";
					newFile << tmpStatus[4];//ATK
					newFile << " ";
					newFile << tmpStatus[5];//HP
					newFile << " ";
					newFile << tmpStatus[6];//DEF
					newFile << " ";
					newFile << tmpStatus[7];//SPEED
					newFile << " ";
					newFile << tmpStatus[8];//Index
					newFile << "\n";

					pokemonOwned[i]->getSkills(tmpInt, skills);
					newFile << tmpInt << " ";
					for (int j = 0; j < tmpInt; j++)
					{
						newFile << skills[j].name << " ";
						newFile << skills[j].elem << " ";
						newFile << skills[j].ex << " ";
					}
					newFile << "\n";
				}
				newFile << "##end##" << endl;
				userFile.getline(cmpData, sizeof(cmpData));
				while (strcmp("##end##", cmpData) != 0)
				{
					userFile.getline(cmpData, sizeof(cmpData));
				}
			}
		}
	}
	userFile.close();
	newFile.close();
	remove("./DATA/userData.txt");
	//cout << endl << errno << endl;
	rename("./DATA/newUserData.txt", "./DATA/userData.txt");//重命名
	//cout << endl << errno << endl;
}

double User::seeWinRate(char* uName)
{
	char cmpName[32] = { 0 };
	ifstream userFile("./DATA/userData.txt");
	userFile.getline(cmpName, 31);
	userFile.getline(cmpName, 31);
	int winNum = 0;
	int allNum = 0;
	int findFlag = 0;
	double rate = 0;
	for (int i = 0; i < userNum; i++)
	{
		userFile >> cmpName;
		if (strcmp(uName, cmpName) == 0)//寻找用户数据位置
		{
			findFlag = 1;
			while (strcmp("#winRate#", cmpName) != 0)//定位战斗数据位置
			{
				userFile >> cmpName;
			}
			break;
		}
		while (strcmp("##end##", cmpName) != 0)
		{
			userFile >> cmpName;
		}
	}
	if (findFlag == 1)
	{
		userFile >> winNum;
		userFile >> allNum;
		if (allNum == 0)
		{
			return 0;
		}
		else
		{
			rate = (double)winNum / (double)allNum;
			return rate;
		}
	}
	else
	{
		return -1;
	}
}
int  User::getquantityBadge()
{
	return quantityBadge;
}
int  User::getadvancedBadge()
{
	return advancedBadge;
}

#endif