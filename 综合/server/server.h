/************************************************************/
/* @�γ�����		C++�γ����	��Ŀ�� �û�ע����ƽ̨��¼	*/
/* @���ߣ�			л�2018211208��						*/
/* @��ʦ��			���鲨									*/
/* @����޸�ʱ�䣺	2020/08/23 17��07						*/
/* @�ļ�����		server.h								*/
/* @�ļ�˵����		�������˲���							*/
/*----------------------------------------------------------*/
/* @��ע��			��������ѭ�����ù�˾ϰ�����ʹ�á�����*/
/*					��(Pokemon)����ָ����С����				*/
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

extern int userNum;//�ⲿ����
extern int activeUserNum;//�ⲿ����

#define GOLD 1//��
#define SILVER 2//��
#define COPPER 3//ͭ



class User//�û�
{
private:
	char username[32];//�û���
	char password[32];//����
	Pokemon* pokemonOwned[32];//ӵ�еľ��飬�������32ֻ
	int pokemonNum;//ӵ�о�������
	int quantityBadge;//������������
	int advancedBadge;//�߼��������
	int winBattleNum;//ʤ����
	int allBattleNum;//�ܳ���
	void distributePokemon(int type, char* newName, int* data, int index, int newSkillNum, const SKILL_DATA_ITEM* skills);//������䱦����
	int sameUserJudge(const char* uName);//�������
	void saveData(const char* uName, const char* uPass);//�½��û����ݴ����ļ�
public:
	User();//����
	User(const char* uName, const char* uPass, int type, int& result);//����
	User(const User& u);//����
	~User();//����
	Pokemon* usingPokemon;//����ʹ�õı�����
	int login(const char* uName, const char* uPass);//��½����
	int loadPokemon();//���뱦����
	void showPokemon();//չʾ�����Σ������ã�
	void selectPokemon(SOCKET* clntSock);//ѡ���ս������
	void getUsername(char* thisName);//��ȡ�û���
	void lossPokemon(SOCKET* clntSock);//����������
	void getPokemon(Pokemon* aPokemon);//��ñ�����
	void winBattlePlus();//ʤ����һ
	void allBattlePlus();//�ܳ�����һ
	void saveAllToFile();//�û����ݴ���
	double seeWinRate(char* uName);//չʾʤ��
	int getquantityBadge();//��ȡ��������
	int getadvancedBadge();//��ȡ�߼�����
};

typedef struct clientData//�û�������Ϣ�ṹ
{
	User* clientUser;//User����ָ��
	SOCKET* clientSocket;//�׽���ָ��
	int state;//�ͻ�״̬ 0��1��2��δ��¼���ѵ�½����ս��
	clientData* prevData;//ָ����һ���ͻ���ָ��
	clientData* nextData;//ָ����һ���ͻ���ָ��
}CLIENT_DATA;

extern CLIENT_DATA* allClients;//���������û�������

void User::distributePokemon(int type, char* newName, int* data, int index, int newSkillNum, const SKILL_DATA_ITEM* skills)
{
	int tmpData[9] = { NORMAL,POWER,0,1,2,10,1,2,0 };//��ʼ������
	char tmpName[32] = { 0 };
	int tmpStatus[7] = { 0 };
	int typeIndex = 0;
	if (type == 0)//�������
	{
		typeIndex = *data;
	}
	else if (type == 1 || type == 2)//���������ݷ���
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
		cout << "��þ��飺" << tmpName << endl << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;

	}
	else if (type == 1)//���������ݷ���
	{
		cout << "���뾫�飺" << tmpName << endl << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;

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
		if (strcmp(uName, cmpName) == 0)//����
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
	rename("./DATA/newUserData.txt", "./DATA/userData.txt");//������
	//cout << endl << errno << endl;
}
User::User()
{
	strcpy(username, "user");
	char index[5];
	itoa(userNum, index, 10);
	strcat(username, index);
	strcpy(password, "123456");
	cout << "�����û���" << username << " ������Ϊ��" << password << endl;
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
	if (type == 0)//ע��
	{
		if (sameUserJudge(uName))
		{
			cout << "�û����ظ�" << endl;
			result = 1;//ע��ʧ��
		}
		else
		{
			strcpy(username, uName);
			strcpy(password, uPass);
			cout << "�����û���" << username << " ������Ϊ��" << password << endl;
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
			result = 0;//ע��ɹ�
		}
	}
	else if (type == 1)//��½
	{
		strcpy(username, uName);
		strcpy(password, uPass);
		cout << "��½�û���" << username << endl;
		pokemonNum = 0;
		result = login(uName, uPass);
	}
	
}
User::User(const User& u)
{
	cout << "����user�Ŀ������캯��" << endl;
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
		if (strcmp(uName, cmpName) == 0)//���ڴ��û�
		{
			userFile >> cmpPass;
			if (strcmp(uPass, cmpPass) == 0)//���������ȷ
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
					while (strcmp("#winRate#", cmpName) != 0)//��λ��������
					{
						userFile >> cmpName;
					}
					userFile >> winBattleNum;
					userFile >> allBattleNum; 
					while (strcmp("#badge#", cmpName) != 0)//��λ����
					{
						userFile >> cmpName;
					}
					userFile >> quantityBadge;
					userFile >> advancedBadge;
					//cout << "��½�ɹ�����ӭ������" << uName << endl;
					userFile.close();
					return 0;
				}
				else
				{
					cout << "�ظ���½" << endl;
					userFile.close();
					return 3;
				}
			}
			else
			{
				cout << "�������" << endl;
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
	cout << "�û�������" << endl;
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
		if (strcmp(username, cmpName) == 0)//Ѱ���û�����λ��
		{
			while (strcmp("#pokemon#", cmpName) != 0)//��λ����������λ��
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
		userFile >> data[0]; //cout << data[0] << endl; //Ԫ�� 
		userFile >> data[1];//����
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
		cout << "�����Σ�" << tmpName << endl << "LV = " << tmpStatus[1] << ", ATK = " << tmpStatus[2] << ", HP = " << tmpStatus[3] << ", DEF = " << tmpStatus[4] << endl;

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
	cout << "�û�ѡ�񱦿��Σ�\n";
	//cout << "�������±����Σ�" << endl;
	strcpy(sendBuf, "�������±����Σ�\n");
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
	//cout << "ѡ��һֻ�����ν��ж�ս��";
	strcat(sendBuf, "ѡ��һֻ�����ν��ж�ս��");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	while (flag)
	{
		//cin >> select;
		//select--;
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		select = atoi(receiveBuf);
		select--;
		if (select >= 0 && select < pokemonNum)
		{
			flag = 0;
		}
		else
		{
			//cout << "��Ŵ������������룺";
			strcat(sendBuf, "��Ŵ������������룺");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
	cout << "ѡ����" << select + 1 << "�ű�����" << endl;
	usingPokemon = pokemonOwned[select];
	strcat(sendBuf, "#selectEnd#");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
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
	//cout << "�������±����Σ�" << endl;
	
	strcpy(sendBuf, "#lossPokemon#");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);

	strcpy(sendBuf, "������±�������ѡһֻ�ͳ���\n");
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
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
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
			strcpy(sendBuf, "����������������룺");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
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
		strcpy(sendBuf, "���ı�������ȫ���ͳ���ϵͳ�Զ�����һֻ1�������Σ�\n");
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
		strcat(sendBuf, "�����������");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		pokemonOwned[0]->setName(receiveBuf);
	}
	strcpy(sendBuf, "#lossEnd#");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
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
			newFile << cmpData << endl;//�û���
			if (strcmp(username, cmpData) == 0)//�ҵ��û�����
			{
				userFile.getline(cmpData, sizeof(cmpData));
				newFile << cmpData << endl;//����
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
				for (int i = 0; i < pokemonNum; i++)//����15�������θ���
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
				for (int i = 0; i < pokemonNum; i++)//�洢ÿ��������
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
					newFile << tmpStatus[0]; //cout << data[0] << endl; //Ԫ�� 
					newFile << " ";
					newFile << tmpStatus[1];//����
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
	rename("./DATA/newUserData.txt", "./DATA/userData.txt");//������
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
		if (strcmp(uName, cmpName) == 0)//Ѱ���û�����λ��
		{
			findFlag = 1;
			while (strcmp("#winRate#", cmpName) != 0)//��λս������λ��
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