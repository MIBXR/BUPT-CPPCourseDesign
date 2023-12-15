/************************************************************/
/* @课程名：		C++课程设计	题目二 用户注册与平台登录	*/
/* @作者；			谢睿（2018211208）						*/
/* @教师：			王洪波									*/
/* @最后修改时间：	2020/08/21 20：09						*/
/* @文件名：		PokemonList.h							*/
/* @文件说明：		定义各种宝可梦类						*/
/*----------------------------------------------------------*/
/* @备注：			本程序遵循任天堂公司习惯用语，使用“宝可*/
/*					梦(Pokemon)”代指宠物小精灵				*/
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

//属性定义
#define POWER 0//力量型
#define BEARABLE 1//肉盾型
#define DEDENSIVE 2//防御型
#define AGILE 3//敏捷型

//速度定义
//#define SUPER 0//极快
#define QUICK 1//快
#define COMMON 2//一般
#define SLOW 3//缓慢

//常量定义
#define MAX_LEVEL 15//最大等级
#define MAX_EXP 4190//最大经验值
#define MAX_SKILL 4//最大学习技能数
#define MAX_TYPE 2//宝可梦种类

//图鉴
#define BLUBASAUR 1	//妙蛙种子
#define CHARIZARD 2	//喷火龙
#define SQUIRTLE 3	//杰尼龟
#define CATERPIE 4	//绿毛虫
#define PIDGEOTTO 5	//比比鸟
#define DIGLETT 6	//地鼠
#define PIKACHU 7	//皮卡丘
#define SNORUNT 8	//雪童子
#define DRAGONITE 9	//快龙

//外部变量定义
extern int expNeeded[14];
extern double effectiveness[10][10];

class Pokemon//宝可梦
{
protected:
	int elem;//元素属性
	int type;//宝可梦属性(4种)
	char name[32];//宝可梦名字
	int EXP;//宝可梦经验值
	int LV;//宝可梦等级
	int ATK;//宝可梦攻击属性值
	int HP;//宝可梦生命属性值
	int DEF;//宝可梦防御属性值
	int SPEED;//宝可梦速度（敏捷）属性值
	Skill* skill[4];//每只宝可梦同时只能学会四个技能
	int skillNum;//记录已学会的技能数
	int globalIndex;//图鉴索引号
	int selectSkill(SOCKET* clntSock, int atkMode);//选择使用的技能
	int deleteSkill(SOCKET* clntSock);//选择删除的技能
	void showEffect(const double effect);//显示效果
private:
	int fullHP;//满生命的值
public:
	Pokemon();//构造函数
	Pokemon(const char* newName, const int* data);//构造函数
	Pokemon(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	Pokemon(const Pokemon& p);//拷贝构造函数
	~Pokemon();//析构函数
	int getElem() { return elem; };//获取元素属性
	int getType() { return type; };//获取属性
	int getExp() { return EXP; };//获取经验值
	int getLevel() { return LV; };//获取当前等级
	int getATK() { return ATK; };//获取当前攻击力
	int getHP() { return HP; };//获取当前生命值
	int getDEF() { return DEF; };//获取当前防御值
	int getSPEED() { return SPEED; };//获取当前速度值
	void changeLevel(int d) { LV += d; };//等级变更d级
	void changeATK(int d) { ATK += d; };//攻击变更d点
	void changeHP(int d) { HP += d; };//生命变更d点
	void changeDEF(int d) { DEF += d; };//防御变更d点
	void changeSPEED(int d) { SPEED += d; };//速度变更d点
	void getSkills(int& getNum, SKILL_DATA_ITEM* getskill);
	void getStatus(char* thisName, int* thisStatus);//获取宝可梦信息
	void getAllInf(char* thisName, int* thisStatus);//获取宝可梦全部信息
	virtual void attack(Pokemon& target, int atkMode, SOCKET* clntSock);//攻击函数 (参数：目标)
	virtual void learnSkill(SOCKET* clntSock);//学习技能
	virtual void levelUp(SOCKET* clntSock, int getExp);//升级函数 (参数：获取的经验值)
	void recover();//恢复函数
	void setName(char* newName);//设置宝可梦昵称（新获得的初级LV1）
};
Pokemon::Pokemon()
{
	elem = NORMAL;//默认为普通元素属性
	type = POWER;//默认为力量型
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
	skillNum = 0;//不给予任何技能
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
	skill[0] = new Skill(0, "拍打", 0);//给予初始技能“拍打”
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
	}//正确性待验证
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
		//cout << name << "会使用" << skillNum << "种技能：";
		strcpy(sendBuf, name);
		strcat(sendBuf, "会使用");
		itoa(skillNum, tmpStr, 10);
		strcat(sendBuf, tmpStr);
		memset(tmpStr, 0, sizeof(tmpStr));
		strcat(sendBuf, "种技能：");
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
		//cout << endl << "请输入要使用的技能编号：";
		strcat(sendBuf, "\n请输入要使用的技能编号：");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		while (1)
		{
			memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
			receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
			skillIndex = atoi(receiveBuf);
			skillIndex--;
			if (skillIndex >= 0 && skillIndex < skillNum) break;//如果范围正确
			else
			{
				strcpy(sendBuf, "您输入了错误的编号，请重新输入：");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}

			//测试用（服务器输入）
			/*
			cin >> skillIndex;
			skillIndex--;
			if (cin.good())//如果输入是整数
			{
				if (skillIndex >= 0 && skillIndex < skillNum)//如果范围正确
				{
					notAttackedFlag = 0;
				}
				else//如果范围不正确
				{
					cout << "您输入了错误的编号，请重新输入：";
				}
			}
			else//如果输入不是整数
			{
				cout << "输入不是整数，请重新输入：";
				cin.clear();//清除错误标志
			}
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
			*/
		}
		strcpy(sendBuf, "#skillOver#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
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
	//cout << name << "会以下技能：";
	strcpy(sendBuf, name);
	strcat(sendBuf, "会以下技能：");
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
	//cout << endl << "请输入要忘记的技能编号(输入0放弃忘记)：";
	strcat(sendBuf, "请输入要忘记的技能编号(输入0放弃忘记)："); 
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区

	while (flag)
	{
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);
		skillChange = atoi(receiveBuf);
		skillChange--;
		if (skillChange >= -1 && skillChange < skillNum)//如果范围正确
		{
			flag = 0;
		}
		else//如果范围不正确
		{
			//cout << "您输入了错误的编号，请重新输入：";
			strcpy(sendBuf, "您输入了错误的编号，请重新输入：");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
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
		//cout << "效果拔群" << endl;
	}
	else if (effect == 0.5)
	{
		//cout << "效果一般" << endl;
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

	int skillIndex = selectSkill(clntSock,atkMode);//选择技能
	double effect = effectiveness[skill[skillIndex]->getElem()][target.getElem()];//效果

	int damage = (int)((ATK + skill[skillIndex]->getEx()) * effect - target.getDEF());//计算造成的伤害值

	Sleep(3);
	//srand(time(0));
	int dodge = rand() % 100;//闪避
	int crit = rand() % 100;//暴击

	if (damage <= 0)
	{
		damage = 0;
		//cout << "毫无效果" << endl; 
		strcpy(sendBuf, name);
		strcat(sendBuf, "使用");
		strcat(sendBuf, skill[skillIndex]->getName());
		strcat(sendBuf, "， 毫无效果\n");
	}
	else
	{
		if (dodge <= DODGE_RATE)//闪避
		{
			damage = 0;
			strcpy(sendBuf, name);
			strcat(sendBuf, "使用");
			strcat(sendBuf, skill[skillIndex]->getName());
			strcat(sendBuf, "，但被对方闪避而没有命中，造成0点伤害\n");
		}
		else
		{
			if (crit <= CRIT_RATE)//暴击
			{
				damage = damage * 2;
				strcpy(sendBuf, name);
				strcat(sendBuf, "使用");
				strcat(sendBuf, skill[skillIndex]->getName());
				strcat(sendBuf, "，技能暴击，给对手造成");
				itoa(damage, tmpStr, 10);
				strcat(sendBuf, tmpStr);
				memset(tmpStr, 0, sizeof(tmpStr));
				strcat(sendBuf, "点伤害，");
			}
			else
			{
				strcpy(sendBuf, name);
				strcat(sendBuf, "使用");
				strcat(sendBuf, skill[skillIndex]->getName());
				strcat(sendBuf, "，给对手造成");
				itoa(damage, tmpStr, 10);
				strcat(sendBuf, tmpStr);
				memset(tmpStr, 0, sizeof(tmpStr));
				strcat(sendBuf, "点伤害，");
			}
			if (effect == 1)
			{
				strcat(sendBuf, "\n");
			}
			else if (effect == 2)
			{
				strcat(sendBuf, "效果拔群\n");
			}
			else if (effect == 0.5)
			{
				strcat(sendBuf, "效果一般\n");
			}
		}
		//cout << name << "使用" << skill[skillIndex]->getName() << "，给对手造成" << damage << "点伤害，";

		target.changeHP(-damage);
		showEffect(effect);
		

		if (target.getHP() > 0)
		{
			//cout << "对手HP剩余" << target.getHP() << endl;
			strcat(sendBuf, "对手HP剩余");
			itoa(target.getHP(), tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, "\n");
		}
		else
		{
			//cout << "对手已倒下" << endl; 
			strcat(sendBuf, "对手已倒下\n");
			target.changeHP(-target.getHP());//HP置零
		}
	}
	//cout << endl;
	strcat(sendBuf, "\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
}
void Pokemon::learnSkill(SOCKET* clntSock)
{
	cout << "**技能学习由子类定义，基类无法学习技能**" << endl;
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
	if (LV < MAX_LEVEL)//如果未满级
	{
		strcpy(sendBuf, "成功升级！");
		for (int i = 0; i < LV; i++)//计算升级所需经验值
		{
			nextLevelExp += expNeeded[i];
			thisLevelExp = expNeeded[i+1];
		}
		EXP += getExp;
		if (EXP > MAX_EXP)//如果经验溢出则置为最大值
		{
			EXP = MAX_EXP;
		}
		if (EXP >= nextLevelExp)//如果可以升级
		{
			ATK += 2;
			HP += 5;
			DEF += 1;
			///cout << this->name << "提升了2点攻击，5点HP，1点防御。";
			strcat(sendBuf, this->name);
			strcat(sendBuf, "提升了2点攻击，5点HP，1点防御。");
			switch (type)
			{
			case POWER:
				ATK += 1;
				//cout << "额外提升1点攻击" << endl;
				strcat(sendBuf, "额外提升1点攻击\n");
				break;
			case BEARABLE:
				HP += 4;
				//cout << "额外提升4点生命" << endl;
				strcat(sendBuf, "额外提升4点生命\n");
				break;
			case DEDENSIVE:
				DEF += 1;
				//cout << "额外提升1点防御" << endl;
				strcat(sendBuf, "额外提升1点防御\n");
				break;
			default:
				//cout << "无额外提升" << endl;
				strcat(sendBuf, "无额外提升\n");
				break;
			}
			LV++;
			fullHP = HP;
			//cout << "等级提升至: LV " << LV << endl;
			strcat(sendBuf, "等级提升至: LV ");
			itoa(LV, tmpStr, 10);
			strcat(sendBuf, tmpStr);
			memset(tmpStr, 0, sizeof(tmpStr));
			strcat(sendBuf, "\n");

			
			if (LV == MAX_LEVEL)
			{
				//cout << this->name << "已满级" << endl;
				strcat(sendBuf, "已满级\n");
			}
			else
			{
				//cout << "距离下次升级还需" << nextLevelExp + thisLevelExp - EXP << "点经验值" << endl;
				strcat(sendBuf, "距离下次升级还需");
				itoa(nextLevelExp + thisLevelExp - EXP, tmpStr, 10);
				strcat(sendBuf, tmpStr);
				memset(tmpStr, 0, sizeof(tmpStr));
				strcat(sendBuf, "点经验值\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
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
		//cout << "已达等级上限，无法继续升级" << endl;
		strcpy(sendBuf, "已达等级上限，无法继续升级\n\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
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

class Bulbasaur :public Pokemon//妙蛙种子
{
protected:
public:
	Bulbasaur();//构造函数
	Bulbasaur(const char* newName, const int* data);//构造函数
	Bulbasaur(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Bulbasaur::Bulbasaur()
{
	globalIndex = BLUBASAUR;
	elem = GRASS;
	skillNum = 2;
	skill[1] = new Skill(GRASS, "飞叶快刀", 0);
}
Bulbasaur::Bulbasaur(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = BLUBASAUR;
	elem = GRASS;
	skillNum = 2;
	skill[1] = new Skill(GRASS, "飞叶快刀", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(grassSkillDataBase[skillIndex].elem, grassSkillDataBase[skillIndex].name, grassSkillDataBase[skillIndex].ex);
		//cout << "学会了" << grassSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, grassSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#"); 
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << grassSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, grassSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		Sleep(10);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0|| strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << grassSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, grassSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(grassSkillDataBase[skillIndex].elem, grassSkillDataBase[skillIndex].name, grassSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Charizard :public Pokemon//喷火龙
{
protected:
public:
	Charizard();//构造函数
	Charizard(const char* newName, const int* data);//构造函数
	Charizard(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Charizard::Charizard()
{
	globalIndex = CHARIZARD;
	elem = FIRE;
	skillNum = 2;
	skill[1] = new Skill(FIRE, "喷火", 0);
}
Charizard::Charizard(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = CHARIZARD;
	elem = FIRE;
	skillNum = 2;
	skill[1] = new Skill(FIRE, "喷火", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(fireSkillDataBase[skillIndex].elem, fireSkillDataBase[skillIndex].name, fireSkillDataBase[skillIndex].ex);
		//cout << "学会了" << fireSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, fireSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << fireSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, fireSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << fireSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, fireSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(fireSkillDataBase[skillIndex].elem, fireSkillDataBase[skillIndex].name, fireSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Squirtle :public Pokemon//杰尼龟
{
protected:
public:
	Squirtle();//构造函数
	Squirtle(const char* newName, const int* data);//构造函数
	Squirtle(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Squirtle::Squirtle()
{
	globalIndex = SQUIRTLE;
	elem = WATER;
	skillNum = 2;
	skill[1] = new Skill(WATER, "喷水", 0);
}
Squirtle::Squirtle(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = SQUIRTLE;
	elem = WATER;
	skillNum = 2;
	skill[1] = new Skill(WATER, "喷水", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(waterSkillDataBase[skillIndex].elem, waterSkillDataBase[skillIndex].name, waterSkillDataBase[skillIndex].ex);
		//cout << "学会了" << waterSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, waterSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << waterSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, waterSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << waterSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, waterSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(waterSkillDataBase[skillIndex].elem, waterSkillDataBase[skillIndex].name, waterSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Caterpie :public Pokemon//绿毛虫
{
protected:
public:
	Caterpie();//构造函数
	Caterpie(const char* newName, const int* data);//构造函数
	Caterpie(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Caterpie::Caterpie()
{
	globalIndex = CATERPIE;
	elem = BUG;
	skillNum = 2;
	skill[1] = new Skill(BUG, "撕咬", 0);
}
Caterpie::Caterpie(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = CATERPIE;
	elem = BUG;
	skillNum = 2;
	skill[1] = new Skill(BUG, "撕咬", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(bugSkillDataBase[skillIndex].elem, bugSkillDataBase[skillIndex].name, bugSkillDataBase[skillIndex].ex);
		//cout << "学会了" << bugSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, bugSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << bugSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, bugSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << bugSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, bugSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(bugSkillDataBase[skillIndex].elem, bugSkillDataBase[skillIndex].name, bugSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Pidgeotto :public Pokemon//比比鸟
{
protected:
public:
	Pidgeotto();//构造函数
	Pidgeotto(const char* newName, const int* data);//构造函数
	Pidgeotto(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Pidgeotto::Pidgeotto()
{
	globalIndex = PIDGEOTTO;
	elem = FLY;
	skillNum = 2;
	skill[1] = new Skill(FLY, "起风", 0);
}
Pidgeotto::Pidgeotto(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = PIDGEOTTO;
	elem = FLY;
	skillNum = 2;
	skill[1] = new Skill(FLY, "起风", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(flySkillDataBase[skillIndex].elem, flySkillDataBase[skillIndex].name, flySkillDataBase[skillIndex].ex);
		//cout << "学会了" << flySkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, flySkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << flySkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, flySkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << flySkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, flySkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(flySkillDataBase[skillIndex].elem, flySkillDataBase[skillIndex].name, flySkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Diglett :public Pokemon//地鼠
{
protected:
public:
	Diglett();//构造函数
	Diglett(const char* newName, const int* data);//构造函数
	Diglett(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Diglett::Diglett()
{
	globalIndex = DIGLETT;
	elem = GROUND;
	skillNum = 2;
	skill[1] = new Skill(GROUND, "击地", 0);
}
Diglett::Diglett(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = DIGLETT;
	elem = GROUND;
	skillNum = 2;
	skill[1] = new Skill(GROUND, "击地", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(groundSkillDataBase[skillIndex].elem, groundSkillDataBase[skillIndex].name, groundSkillDataBase[skillIndex].ex);
		//cout << "学会了" << groundSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, groundSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << groundSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, groundSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << groundSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, groundSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(groundSkillDataBase[skillIndex].elem, groundSkillDataBase[skillIndex].name, groundSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Pikachu :public Pokemon//皮卡丘
{
protected:
public:
	Pikachu();//构造函数
	Pikachu(const char* newName, const int* data);//构造函数
	Pikachu(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Pikachu::Pikachu()
{
	globalIndex = PIKACHU;
	elem = ELECTRIC;
	skillNum = 2;
	skill[1] = new Skill(ELECTRIC, "电击", 0);
}
Pikachu::Pikachu(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = PIKACHU;
	elem = ELECTRIC;
	skillNum = 2;
	skill[1] = new Skill(ELECTRIC, "电击", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(electricSkillDataBase[skillIndex].elem, electricSkillDataBase[skillIndex].name, electricSkillDataBase[skillIndex].ex);
		//cout << "学会了" << electricSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, electricSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << electricSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, electricSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << electricSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, electricSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(electricSkillDataBase[skillIndex].elem, electricSkillDataBase[skillIndex].name, electricSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Snorunt :public Pokemon//雪童子
{
protected:
public:
	Snorunt();//构造函数
	Snorunt(const char* newName, const int* data);//构造函数
	Snorunt(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Snorunt::Snorunt()
{
	globalIndex = SNORUNT;
	elem = ICE;
	skillNum = 2;
	skill[1] = new Skill(ICE, "吐冰", 0);
}
Snorunt::Snorunt(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = SNORUNT;
	elem = ICE;
	skillNum = 2;
	skill[1] = new Skill(ICE, "吐冰", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(iceSkillDataBase[skillIndex].elem, iceSkillDataBase[skillIndex].name, iceSkillDataBase[skillIndex].ex);
		//cout << "学会了" << iceSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, iceSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << iceSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, iceSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << iceSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, iceSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(iceSkillDataBase[skillIndex].elem, iceSkillDataBase[skillIndex].name, iceSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

class Dragonite :public Pokemon//快龙
{
protected:
public:
	Dragonite();//构造函数
	Dragonite(const char* newName, const int* data);//构造函数
	Dragonite(const char* newName, const int* data, int newSkillNum, const SKILL_DATA_ITEM* skills);//构造函数
	virtual void learnSkill(SOCKET* clntSock);//学习技能
};
Dragonite::Dragonite()
{
	globalIndex = DRAGONITE;
	elem = DRAGON;
	skillNum = 2;
	skill[1] = new Skill(DRAGON, "龙爪", 0);
}
Dragonite::Dragonite(const char* newName, const int* data)
	:Pokemon(newName, data)
{
	globalIndex = DRAGONITE;
	elem = DRAGON;
	skillNum = 2;
	skill[1] = new Skill(DRAGON, "龙爪", 0);
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
	//cout << "可以学习新的技能了！" << endl;
	strcpy(sendBuf, "可以学习新的技能了！\n");
	sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
	memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
	Sleep(10);
	if (skillNum < MAX_SKILL)
	{
		skill[skillNum] = new Skill(dragonSkillDataBase[skillIndex].elem, dragonSkillDataBase[skillIndex].name, dragonSkillDataBase[skillIndex].ex);
		//cout << "学会了" << dragonSkillDataBase[skillIndex].name << endl;
		strcpy(sendBuf, "学会了");
		strcat(sendBuf, dragonSkillDataBase[skillIndex].name);
		strcat(sendBuf, "\n");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		skillNum++;
	}
	else//已会4个技能，需选择是否遗忘某个技能
	{
		strcpy(sendBuf, "#forget#");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		//cout << name << "已经学会4个技能了，要学习新技能" << dragonSkillDataBase[skillIndex].name << "需要忘记一个旧技能，是否忘记？(Y/N) ";
		strcpy(sendBuf, name);
		strcat(sendBuf, "已经学会4个技能了，要学习新技能");
		strcat(sendBuf, dragonSkillDataBase[skillIndex].name);
		strcat(sendBuf, "需要忘记一个旧技能，是否忘记？(Y / N)");
		sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
		memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
		Sleep(10);
		memset(receiveBuf, 0, sizeof(receiveBuf));  //清空缓冲区
		receiveLen = recv(*clntSock, receiveBuf, sizeof(receiveBuf), NULL);

		//cin >> forget;
		//cin.ignore((numeric_limits<streamsize>::max)(), '\n');//清除输入缓冲区
		if (strcmp("Y", receiveBuf) == 0 || strcmp("y", receiveBuf) == 0)
		{
			skillChange = deleteSkill(clntSock);
			strcpy(sendBuf, "#learnEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			if (skillChange == -1)
			{
				//cout << "放弃学习" << endl;
				strcpy(sendBuf, "放弃学习\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
			}
			else
			{
				//cout << "成功忘记" << skill[skillChange]->getName() << "并学会了" << dragonSkillDataBase[skillIndex].name << endl;
				strcpy(sendBuf, "成功忘记");
				strcat(sendBuf, skill[skillChange]->getName());
				strcat(sendBuf, "并学会了");
				strcat(sendBuf, dragonSkillDataBase[skillIndex].name);
				strcat(sendBuf, "\n");
				sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
				memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
				Sleep(10);
				skill[skillChange] = new Skill(dragonSkillDataBase[skillIndex].elem, dragonSkillDataBase[skillIndex].name, dragonSkillDataBase[skillIndex].ex);
			}
		}
		else
		{
			strcpy(sendBuf, "#allEnd#");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
			//cout << "放弃学习新技能" << endl;
			strcpy(sendBuf, "放弃学习新技能\n");
			sendLen = send(*clntSock, sendBuf, strlen(sendBuf) + sizeof(char), NULL);
			memset(sendBuf, 0, sizeof(sendBuf));  //清空缓冲区
			Sleep(10);
		}
	}
}

#endif
