/************************************************************/
/* @�γ�����		C++�γ����	��Ŀ�� �û�ע����ƽ̨��¼	*/
/* @���ߣ�			л�2018211208��						*/
/* @��ʦ��			���鲨									*/
/* @����޸�ʱ�䣺	2020/08/21 20��09						*/
/* @�ļ�����		PokemonList.h							*/
/* @�ļ�˵����		������ֱ�������						*/
/*----------------------------------------------------------*/
/* @��ע��			��������ѭ�����ù�˾ϰ�����ʹ�á�����*/
/*					��(Pokemon)����ָ����С����				*/
/************************************************************/

#ifndef Pokemon_List_h
#define Pokemon_List_h

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<string.h>
#include"Skills.h"
#include"header.h"

using namespace std;

//���Զ���
#define POWER 0//������
#define BEARABLE 1//�����
#define DEDENSIVE 2//������
#define AGILE 3//������

//�ٶȶ���
//#define SUPER 0//����
#define QUICK 1//��
#define COMMON 2//һ��
#define SLOW 3//����

//��������
#define MAX_LEVEL 15//���ȼ�
#define MAX_EXP 4190//�����ֵ
#define MAX_SKILL 4//���ѧϰ������
#define MAX_TYPE 2//����������

//ͼ��
#define BLUBASAUR 1	//��������
#define CHARIZARD 2	//�����
#define SQUIRTLE 3	//�����
#define CATERPIE 4	//��ë��
#define PIDGEOTTO 5	//�ȱ���
#define DIGLETT 6	//����
#define PIKACHU 7	//Ƥ����
#define SNORUNT 8	//ѩͯ��
#define DRAGONITE 9	//����

//�ⲿ��������
extern int expNeeded[14];
extern double effectiveness[10][10];

class Pokemon//������
{
protected:
	int elem;//Ԫ������
	int type;//����������(4��)
	char name[32];//����������
	int EXP;//�����ξ���ֵ
	int LV;//�����εȼ�
	int ATK;//�����ι�������ֵ
	int HP;//��������������ֵ
	int DEF;//�����η�������ֵ
	int SPEED;//�������ٶȣ����ݣ�����ֵ
	Skill* skill[4];//ÿֻ������ͬʱֻ��ѧ���ĸ�����
	int skillNum;//��¼��ѧ��ļ�����
	int globalIndex;//ͼ��������
	int selectSkill(SOCKET* clntSock, int atkMode);//ѡ��ʹ�õļ���
	int deleteSkill(SOCKET* clntSock);//ѡ��ɾ���ļ���
	void showEffect(const double effect);//��ʾЧ��
private:
	int fullHP;//��������ֵ
public:
	Pokemon();//���캯��
	Pokemon(const char* newName, const int* data);//���캯��
	Pokemon(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	Pokemon(const Pokemon& p);//�������캯��
	~Pokemon();//��������
	int getElem() { return elem; };//��ȡԪ������
	int getType() { return type; };//��ȡ����
	int getExp() { return EXP; };//��ȡ����ֵ
	int getLevel() { return LV; };//��ȡ��ǰ�ȼ�
	int getATK() { return ATK; };//��ȡ��ǰ������
	int getHP() { return HP; };//��ȡ��ǰ����ֵ
	int getDEF() { return DEF; };//��ȡ��ǰ����ֵ
	int getSPEED() { return SPEED; };//��ȡ��ǰ�ٶ�ֵ
	void changeLevel(int d) { LV += d; };//�ȼ����d��
	void changeATK(int d) { ATK += d; };//�������d��
	void changeHP(int d) { HP += d; };//�������d��
	void changeDEF(int d) { DEF += d; };//�������d��
	void changeSPEED(int d) { SPEED += d; };//�ٶȱ��d��
	void getSkills(int& getNum, SKILL_DATA_ITEM* getskill);
	void getStatus(char* thisName, int* thisStatus);//��ȡ��������Ϣ
	void getAllInf(char* thisName, int* thisStatus);//��ȡ������ȫ����Ϣ
	virtual void attack(Pokemon& target, int atkMode, SOCKET* clntSock);//�������� (������Ŀ��)
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
	virtual void levelUp(SOCKET* clntSock, int getExp);//�������� (��������ȡ�ľ���ֵ)
	void recover();//�ָ�����
	void setName(char* newName);//���ñ������ǳƣ��»�õĳ���LV1��
};
Pokemon::Pokemon()
{
	elem = NORMAL;//Ĭ��Ϊ��ͨԪ������
	type = POWER;//Ĭ��Ϊ������
	strcpy(name, "noName");
	EXP = 0;
	LV = 1;
	ATK = 1;
	HP = 4;
	DEF = 0;
	SPEED = SLOW;
	fullHP = HP;
	skill[0] = NULL;
	skill[1] = NULL;
	skill[2] = NULL;
	skill[3] = NULL;
	skillNum = 0;//�������κμ���
	globalIndex = 0;
}
Pokemon::Pokemon(const char* newName, const int* data)
{
	elem = data[0];
	type = data[1];
	strcpy(name, newName);
	EXP = data[2];
	LV = data[3];
	ATK = data[4];
	HP = data[5];
	DEF = data[6];
	SPEED = data[7];
	fullHP = HP;
	skill[0] = new Skill(0, "�Ĵ�", 0);//�����ʼ���ܡ��Ĵ�
	skillNum = 1;
	globalIndex = data[8];
}
Pokemon::Pokemon(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
{
	elem = data[0];
	type = data[1];
	strcpy(name, newName);
	EXP = data[2];
	LV = data[3];
	ATK = data[4];
	HP = data[5];
	DEF = data[6];
	SPEED = data[7];
	globalIndex = data[8];
	fullHP = HP;
	skillNum = newSkillNum;
	for (int i = 0; i < skillNum; i++)
	{
		skill[i] = new Skill(skills[i].elem, skills[i].name, skills[i].ex);
	}
}
Pokemon::Pokemon(const Pokemon& p)
{
	elem = p.elem;
	type = p.type;
	strcpy(name, p.name);
	EXP = p.EXP;
	LV = p.LV;
	ATK = p.ATK;
	HP = p.HP;
	DEF = p.DEF;
	SPEED = p.SPEED;
	fullHP = HP;
	for (int i = 0; i < p.skillNum; i++)
	{
		skill[i] = new Skill();
		(*skill[i]) = *(p.skill[i]);
	}//��ȷ�Դ���֤
	skillNum = p.skillNum;
	globalIndex = p.globalIndex;
}
Pokemon::~Pokemon()
{
	for (int i = skillNum - 1; i >= 0; i--)
	{
		delete[] skill[i];
	}
}
int Pokemon::selectSkill(SOCKET* clntSock, int atkMode)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;

	if (atkMode == 0)
	{
		//cout << name << "��ʹ��" << skillNum << "�ּ��ܣ�";
		strcpy(sendBuf, name);
		strcat(sendBuf, "��ʹ��");
		itoa(skillNum, tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, "�ּ��ܣ�");
		for (int i = 0; i < skillNum; i++)
		{
			//cout << i + 1 << "." << skill[i]->getName() << " ";
			itoa(i + 1, tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, ".");
			strcat(sendBuf, skill[i]->getName());
			strcat(sendBuf, " ");
		}
		//cout << endl << "������Ҫʹ�õļ��ܱ�ţ�";
		strcat(sendBuf, "\n������Ҫʹ�õļ��ܱ�ţ�");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		while (1)
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
			receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
			skillIndex = atoi(receiveBuf);
			skillIndex--;
			if (skillIndex >= 0 && skillIndex < skillNum) break;//�����Χ��ȷ
			else
			{
				strcpy(sendBuf, "�������˴���ı�ţ����������룺");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}

			//�����ã����������룩
			/*
			cin >> skillIndex;
			skillIndex--;
			if (cin.good())//�������������
			{
				if (skillIndex >= 0 && skillIndex < skillNum)//�����Χ��ȷ
				{
					notAttackedFlag = 0;
				}
				else//�����Χ����ȷ
				{
					cout << "�������˴���ı�ţ����������룺";
				}
			}
			else//������벻������
			{
				cout << "���벻�����������������룺";
				cin.clear();//��������־
			}
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
			*/
		}
		strcpy(sendBuf, "#skillOver#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	}
	else
	{
		Sleep(3);
		//srand((int)time(0));
		skillIndex = rand() % skillNum;
	}
	return skillIndex;
}
int Pokemon::deleteSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillChange = 0;
	int flag = 1;
	//cout << name << "�����¼��ܣ�";
	strcpy(sendBuf, name);
	strcat(sendBuf, "�����¼��ܣ�");
	for (int i = 0; i < skillNum; i++)
	{
		//cout << i + 1 << "." << skill[i]->getName() << " ";
		itoa(i + 1, tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, ".");
		strcat(sendBuf, skill[i]->getName());
		strcat(sendBuf, " ");
	}
	//cout << endl << "������Ҫ���ǵļ��ܱ��(����0��������)��";
	strcat(sendBuf, "������Ҫ���ǵļ��ܱ��(����0��������)��"); 
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����

	while (flag)
	{
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		skillChange = atoi(receiveBuf);
		skillChange--;
		if (skillChange >= -1 && skillChange < skillNum)//�����Χ��ȷ
		{
			flag = 0;
		}
		else//�����Χ����ȷ
		{
			//cout << "�������˴���ı�ţ����������룺";
			strcpy(sendBuf, "�������˴���ı�ţ����������룺");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		}
		
	}
	return skillChange;
}
void Pokemon::showEffect(double effect)
{
	if (effect == 1)
	{
		//cout << endl;
	}
	else if (effect == 2)
	{
		//cout << "Ч����Ⱥ" << endl;
	}
	else if (effect == 0.5)
	{
		//cout << "Ч��һ��" << endl;
	}
}
void Pokemon::getSkills(int& getNum, SKILL_DATA_ITEM* getskill)
{
	getNum = skillNum;
	for (int j = 0; j < skillNum; j++)
	{
		strcpy(getskill[j].name, skill[j]->getName());
		getskill[j].elem = skill[j]->getElem();
		getskill[j].ex = skill[j]->getEx();
	}
}
void Pokemon::getStatus(char* thisName, int* thisStatus)
{
	strcpy(thisName, name);
	thisStatus[0] = type;
	thisStatus[1] = LV;
	thisStatus[2] = ATK;
	thisStatus[3] = HP;
	thisStatus[4] = DEF;
	thisStatus[5] = SPEED;
	thisStatus[6] = EXP;
}
void Pokemon::getAllInf(char* thisName, int* thisStatus)
{
	strcpy(thisName, name);
	thisStatus[0] = elem;
	thisStatus[1] = type;
	thisStatus[2] = EXP;
	thisStatus[3] = LV;
	thisStatus[4] = ATK;
	thisStatus[5] = HP;
	thisStatus[6] = DEF;
	thisStatus[7] = SPEED;
	thisStatus[8] = globalIndex;
}
void Pokemon::attack(Pokemon& target, int atkMode, SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = selectSkill(clntSock,atkMode);//ѡ����
	double effect = effectiveness[skill[skillIndex]->getElem()][target.getElem()];//Ч��

	int damage = (int)((ATK + skill[skillIndex]->getEx()) * effect - target.getDEF());//������ɵ��˺�ֵ

	Sleep(3);
	//srand(time(0));
	int dodge = rand() % 100;//����
	int crit = rand() % 100;//����

	if (damage <= 0)
	{
		damage = 0;
		//cout << "����Ч��" << endl; 
		strcpy(sendBuf, name);
		strcat(sendBuf, "ʹ��");
		strcat(sendBuf, skill[skillIndex]->getName());
		strcat(sendBuf, "�� ����Ч��\n");
	}
	else
	{
		if (dodge <= DODGE_RATE)//����
		{
			damage = 0;
			strcpy(sendBuf, name);
			strcat(sendBuf, "ʹ��");
			strcat(sendBuf, skill[skillIndex]->getName());
			strcat(sendBuf, "�������Է����ܶ�û�����У����0���˺�\n");
		}
		else
		{
			if (crit <= CRIT_RATE)//����
			{
				damage = damage * 2;
				strcpy(sendBuf, name);
				strcat(sendBuf, "ʹ��");
				strcat(sendBuf, skill[skillIndex]->getName());
				strcat(sendBuf, "�����ܱ��������������");
				itoa(damage, tmpStr, 10);
				strcat(sendBuf, tmpStr);
				memset(tmpStr, 0, sizeof(tmpStr));
				strcat(sendBuf, "���˺���");
			}
			else
			{
				strcpy(sendBuf, name);
				strcat(sendBuf, "ʹ��");
				strcat(sendBuf, skill[skillIndex]->getName());
				strcat(sendBuf, "�����������");
				itoa(damage, tmpStr, 10);
				strcat(sendBuf, tmpStr);
				memset(tmpStr, 0, sizeof(tmpStr));
				strcat(sendBuf, "���˺���");
			}
			if (effect == 1)
			{
				strcat(sendBuf, "\n");
			}
			else if (effect == 2)
			{
				strcat(sendBuf, "Ч����Ⱥ\n");
			}
			else if (effect == 0.5)
			{
				strcat(sendBuf, "Ч��һ��\n");
			}
		}
		//cout << name << "ʹ��" << skill[skillIndex]->getName() << "�����������" << damage << "���˺���";

		target.changeHP(-damage);
		showEffect(effect);
		

		if (target.getHP() > 0)
		{
			//cout << "����HPʣ��" << target.getHP() << endl;
			strcat(sendBuf, "����HPʣ��");
			itoa(target.getHP(), tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, "\n");
		}
		else
		{
			//cout << "�����ѵ���" << endl; 
			strcat(sendBuf, "�����ѵ���\n");
			target.changeHP(-target.getHP());//HP����
		}
	}
	//cout << endl;
	strcat(sendBuf, "\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
}
void Pokemon::learnSkill(SOCKET* clntSock)
{
	cout << "**����ѧϰ�����ඨ�壬�����޷�ѧϰ����**" << endl;
}
void Pokemon::levelUp(SOCKET* clntSock, int getExp)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int nextLevelExp = 0;
	int thisLevelExp = expNeeded[0];
	if (LV < MAX_LEVEL)//���δ����
	{
		strcpy(sendBuf, "�ɹ�������");
		for (int i = 0; i < LV; i++)//�����������辭��ֵ
		{
			nextLevelExp += expNeeded[i];
			thisLevelExp = expNeeded[i+1];
		}
		EXP += getExp;
		if (EXP > MAX_EXP)//��������������Ϊ���ֵ
		{
			EXP = MAX_EXP;
		}
		if (EXP >= nextLevelExp)//�����������
		{
			ATK += 2;
			HP += 5;
			DEF += 1;
			///cout << this->name << "������2�㹥����5��HP��1�������";
			strcat(sendBuf, this->name);
			strcat(sendBuf, "������2�㹥����5��HP��1�������");
			switch (type)
			{
			case POWER:
				ATK += 1;
				//cout << "��������1�㹥��" << endl;
				strcat(sendBuf, "��������1�㹥��\n");
				break;
			case BEARABLE:
				HP += 4;
				//cout << "��������4������" << endl;
				strcat(sendBuf, "��������4������\n");
				break;
			case DEDENSIVE:
				DEF += 1;
				//cout << "��������1�����" << endl;
				strcat(sendBuf, "��������1�����\n");
				break;
			default:
				//cout << "�޶�������" << endl;
				strcat(sendBuf, "�޶�������\n");
				break;
			}
			LV++;
			fullHP = HP;
			//cout << "�ȼ�������: LV " << LV << endl;
			strcat(sendBuf, "�ȼ�������: LV ");
			itoa(LV, tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, "\n");

			
			if (LV == MAX_LEVEL)
			{
				//cout << this->name << "������" << endl;
				strcat(sendBuf, "������\n");
			}
			else
			{
				//cout << "�����´���������" << nextLevelExp + thisLevelExp - EXP << "�㾭��ֵ" << endl;
				strcat(sendBuf, "�����´���������");
				itoa(nextLevelExp + thisLevelExp - EXP, tmpStr, 10);
				strcat(sendBuf, tmpStr);
				memset(tmpStr, 0, sizeof(tmpStr));
				strcat(sendBuf, "�㾭��ֵ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			if (LV % 3 == 0)
			{
				learnSkill(clntSock);
			}
		}
	}
	else
	{
		//cout << "�Ѵ�ȼ����ޣ��޷���������" << endl;
		strcpy(sendBuf, "�Ѵ�ȼ����ޣ��޷���������\n\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
	}
	//cout << endl;
}
void Pokemon::recover()
{
	HP = fullHP;
}
void Pokemon::setName(char* newName)
{
	strcpy(name, newName);
}

class Bulbasaur :public Pokemon//��������
{
protected:
public:
	Bulbasaur();//���캯��
	Bulbasaur(const char* newName, const int* data);//���캯��
	Bulbasaur(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Bulbasaur::Bulbasaur()
{
	globalIndex = BLUBASAUR;
	elem = GRASS;
	skillNum = 2;
	skill[1] = new Skill(GRASS, "��Ҷ�쵶", 0);
}
Bulbasaur::Bulbasaur(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = BLUBASAUR;
	elem = GRASS;
	skillNum = 2;
	skill[1] = new Skill(GRASS, "��Ҷ�쵶", 0);
}
Bulbasaur::Bulbasaur(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = BLUBASAUR;
	elem = GRASS;
}
void Bulbasaur::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(grassSkillDataBase[skillIndex].elem, grassSkillDataBase[skillIndex].name, grassSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << grassSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, grassSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#"); 
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << grassSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, grassSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		Sleep(10);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0|| strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << grassSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, grassSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(grassSkillDataBase[skillIndex].elem, grassSkillDataBase[skillIndex].name, grassSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Charizard :public Pokemon//�����
{
protected:
public:
	Charizard();//���캯��
	Charizard(const char* newName, const int* data);//���캯��
	Charizard(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Charizard::Charizard()
{
	globalIndex = CHARIZARD;
	elem = FIRE;
	skillNum = 2;
	skill[1] = new Skill(FIRE, "���", 0);
}
Charizard::Charizard(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = CHARIZARD;
	elem = FIRE;
	skillNum = 2;
	skill[1] = new Skill(FIRE, "���", 0);
}
Charizard::Charizard(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = CHARIZARD;
	elem = FIRE;
}
void Charizard::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(fireSkillDataBase[skillIndex].elem, fireSkillDataBase[skillIndex].name, fireSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << fireSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, fireSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << fireSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, fireSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << fireSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, fireSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(fireSkillDataBase[skillIndex].elem, fireSkillDataBase[skillIndex].name, fireSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Squirtle :public Pokemon//�����
{
protected:
public:
	Squirtle();//���캯��
	Squirtle(const char* newName, const int* data);//���캯��
	Squirtle(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Squirtle::Squirtle()
{
	globalIndex = SQUIRTLE;
	elem = WATER;
	skillNum = 2;
	skill[1] = new Skill(WATER, "��ˮ", 0);
}
Squirtle::Squirtle(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = SQUIRTLE;
	elem = WATER;
	skillNum = 2;
	skill[1] = new Skill(WATER, "��ˮ", 0);
}
Squirtle::Squirtle(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = SQUIRTLE;
	elem = WATER;
}

void Squirtle::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(waterSkillDataBase[skillIndex].elem, waterSkillDataBase[skillIndex].name, waterSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << waterSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, waterSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << waterSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, waterSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << waterSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, waterSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(waterSkillDataBase[skillIndex].elem, waterSkillDataBase[skillIndex].name, waterSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Caterpie :public Pokemon//��ë��
{
protected:
public:
	Caterpie();//���캯��
	Caterpie(const char* newName, const int* data);//���캯��
	Caterpie(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Caterpie::Caterpie()
{
	globalIndex = CATERPIE;
	elem = BUG;
	skillNum = 2;
	skill[1] = new Skill(BUG, "˺ҧ", 0);
}
Caterpie::Caterpie(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = CATERPIE;
	elem = BUG;
	skillNum = 2;
	skill[1] = new Skill(BUG, "˺ҧ", 0);
}
Caterpie::Caterpie(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = CATERPIE;
	elem = BUG;
}
void Caterpie::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(bugSkillDataBase[skillIndex].elem, bugSkillDataBase[skillIndex].name, bugSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << bugSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, bugSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << bugSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, bugSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << bugSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, bugSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(bugSkillDataBase[skillIndex].elem, bugSkillDataBase[skillIndex].name, bugSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Pidgeotto :public Pokemon//�ȱ���
{
protected:
public:
	Pidgeotto();//���캯��
	Pidgeotto(const char* newName, const int* data);//���캯��
	Pidgeotto(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Pidgeotto::Pidgeotto()
{
	globalIndex = PIDGEOTTO;
	elem = FLY;
	skillNum = 2;
	skill[1] = new Skill(FLY, "���", 0);
}
Pidgeotto::Pidgeotto(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = PIDGEOTTO;
	elem = FLY;
	skillNum = 2;
	skill[1] = new Skill(FLY, "���", 0);
}
Pidgeotto::Pidgeotto(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = PIDGEOTTO;
	elem = FLY;
}
void Pidgeotto::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(flySkillDataBase[skillIndex].elem, flySkillDataBase[skillIndex].name, flySkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << flySkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, flySkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << flySkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, flySkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << flySkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, flySkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(flySkillDataBase[skillIndex].elem, flySkillDataBase[skillIndex].name, flySkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Diglett :public Pokemon//����
{
protected:
public:
	Diglett();//���캯��
	Diglett(const char* newName, const int* data);//���캯��
	Diglett(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Diglett::Diglett()
{
	globalIndex = DIGLETT;
	elem = GROUND;
	skillNum = 2;
	skill[1] = new Skill(GROUND, "����", 0);
}
Diglett::Diglett(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = DIGLETT;
	elem = GROUND;
	skillNum = 2;
	skill[1] = new Skill(GROUND, "����", 0);
}
Diglett::Diglett(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = DIGLETT;
	elem = GROUND;
}
void Diglett::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(groundSkillDataBase[skillIndex].elem, groundSkillDataBase[skillIndex].name, groundSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << groundSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, groundSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << groundSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, groundSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << groundSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, groundSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(groundSkillDataBase[skillIndex].elem, groundSkillDataBase[skillIndex].name, groundSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Pikachu :public Pokemon//Ƥ����
{
protected:
public:
	Pikachu();//���캯��
	Pikachu(const char* newName, const int* data);//���캯��
	Pikachu(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Pikachu::Pikachu()
{
	globalIndex = PIKACHU;
	elem = ELECTRIC;
	skillNum = 2;
	skill[1] = new Skill(ELECTRIC, "���", 0);
}
Pikachu::Pikachu(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = PIKACHU;
	elem = ELECTRIC;
	skillNum = 2;
	skill[1] = new Skill(ELECTRIC, "���", 0);
}
Pikachu::Pikachu(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = PIKACHU;
	elem = ELECTRIC;
}
void Pikachu::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(electricSkillDataBase[skillIndex].elem, electricSkillDataBase[skillIndex].name, electricSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << electricSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, electricSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << electricSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, electricSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << electricSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, electricSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(electricSkillDataBase[skillIndex].elem, electricSkillDataBase[skillIndex].name, electricSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Snorunt :public Pokemon//ѩͯ��
{
protected:
public:
	Snorunt();//���캯��
	Snorunt(const char* newName, const int* data);//���캯��
	Snorunt(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Snorunt::Snorunt()
{
	globalIndex = SNORUNT;
	elem = ICE;
	skillNum = 2;
	skill[1] = new Skill(ICE, "�±�", 0);
}
Snorunt::Snorunt(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = SNORUNT;
	elem = ICE;
	skillNum = 2;
	skill[1] = new Skill(ICE, "�±�", 0);
}
Snorunt::Snorunt(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = SNORUNT;
	elem = ICE;
}
void Snorunt::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(iceSkillDataBase[skillIndex].elem, iceSkillDataBase[skillIndex].name, iceSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << iceSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, iceSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << iceSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, iceSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << iceSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, iceSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(iceSkillDataBase[skillIndex].elem, iceSkillDataBase[skillIndex].name, iceSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

class Dragonite :public Pokemon//����
{
protected:
public:
	Dragonite();//���캯��
	Dragonite(const char* newName, const int* data);//���캯��
	Dragonite(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//���캯��
	virtual void learnSkill(SOCKET* clntSock);//ѧϰ����
};
Dragonite::Dragonite()
{
	globalIndex = DRAGONITE;
	elem = DRAGON;
	skillNum = 2;
	skill[1] = new Skill(DRAGON, "��צ", 0);
}
Dragonite::Dragonite(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = DRAGONITE;
	elem = DRAGON;
	skillNum = 2;
	skill[1] = new Skill(DRAGON, "��צ", 0);
}
Dragonite::Dragonite(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills)
	:Pokemon(newName, data, newSkillNum, skills)
{
	globalIndex = DRAGONITE;
	elem = DRAGON;
}
void Dragonite::learnSkill(SOCKET* clntSock)
{
	int sendLen;
	int receiveLen;
	char sendBuf[MAX_BUF_SIZE] = { 0 };
	char receiveBuf[MAX_BUF_SIZE] = { 0 };
	char tmpStr[100];

	int skillIndex = 0;
	int skillChange = 0;
	char forget = 'N';
	int flag = 1;
	skillIndex = (LV / 3) % 5;
	//cout << "����ѧϰ�µļ����ˣ�" << endl;
	strcpy(sendBuf, "����ѧϰ�µļ����ˣ�\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(dragonSkillDataBase[skillIndex].elem, dragonSkillDataBase[skillIndex].name, dragonSkillDataBase[skillIndex].ex);
		//cout << "ѧ����" << dragonSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "ѧ����");
		strcat(sendBuf, dragonSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		skillNum++;
	}
	else//�ѻ�4�����ܣ���ѡ���Ƿ�����ĳ������
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		//cout << name << "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���" << dragonSkillDataBase[skillIndex].name << "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "�Ѿ�ѧ��4�������ˣ�Ҫѧϰ�¼���");
		strcat(sendBuf, dragonSkillDataBase[skillIndex].name);
		strcat(sendBuf, "��Ҫ����һ���ɼ��ܣ��Ƿ����ǣ�(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //��ջ�����
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//������뻺����
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "����ѧϰ" << endl;
				strcpy(sendBuf, "����ѧϰ\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
			}
			else
			{
				//cout << "�ɹ�����" << skill[skillChange]->getName() << "��ѧ����" << dragonSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "�ɹ�����");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "��ѧ����");
				strcat(sendBuf, dragonSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
				Sleep(10);
				skill[skillChange] = new Skill(dragonSkillDataBase[skillIndex].elem, dragonSkillDataBase[skillIndex].name, dragonSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
			//cout << "����ѧϰ�¼���" << endl;
			strcpy(sendBuf, "����ѧϰ�¼���\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //��ջ�����
			Sleep(10);
		}
	}
}

#endif
