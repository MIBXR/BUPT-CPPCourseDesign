/************************************************************/
/* @课程名：		C++课程设计	题目二 用户注册与平台登录	*/
/* @作者；			谢睿（2018211208）						*/
/* @教师：			王洪波									*/
/* @最后修改时间：	2020/08/22 17：52						*/
/* @文件名：		Skills.h								*/
/* @文件说明：		定义各种元素属性以及可学会的技能		*/
/*----------------------------------------------------------*/
/* @备注：			本程序遵循任天堂公司习惯用语，使用“宝可*/
/*					梦(Pokemon)”代指宠物小精灵				*/
/************************************************************/

#ifndef Skills_h
#define Skills_h

//元素定义
#define NORMAL 0//普通
#define FIRE 1//火
#define GRASS 2//草
#define WATER 3//水
#define BUG 4//虫
#define FLY 5//飞
#define GROUND 6//地
#define ELECTRIC 7//电
#define ICE 8//冰
#define DRAGON 9//龙

class Skill//技能
{
private:
	char name[32];//技能名
	int elem;//元素属性
	int ex;//额外伤害加成
public:
	Skill();//构造函数
	Skill(int type, const char* newName, int newEx);//构造函数
	Skill(const Skill& s);//拷贝构造函数
	~Skill() {}//析构函数
	Skill& operator =(const Skill& m)//赋值重载
	{
		if (this != &m)//自赋值判断
		{
			elem = m.elem;
			strcpy(name, m.name);
			ex = m.ex;
		}
		return *this;
	}
	int getElem() { return elem; };//获取元素属性
	char* getName() { return name; };//获取技能名
	int getEx() { return ex; };//获取额外伤害值
};
Skill::Skill()//默认招式为普通系攻击“拍打”,无攻击加成
{
	elem = 0;
	strcpy(name, "拍打");
	ex = 0;
}
Skill::Skill(int newType, const char* newName, int newEx)
{
	elem = newType;
	strcpy(name, newName);
	ex = newEx;
}
Skill::Skill(const Skill& s)
{
	elem = s.elem;
	strcpy(name, s.name);
	ex = s.ex;
}

typedef struct skillDataItem//结构体：记录构成一个技能的数据，便于传递
{
	char name[32];
	int elem;
	int ex;
}SKILL_DATA_ITEM;

SKILL_DATA_ITEM grassSkillDataBase[5] =//草系可学会的技能，初始是：飞叶快刀
{ {"藤鞭",GRASS,1},
{"吸取",GRASS,0},
{"日光",GRASS,2},
{"花瓣舞",GRASS,1},
{"种子机关枪",GRASS,4} };
SKILL_DATA_ITEM fireSkillDataBase[5] =//火系可学会的技能，初始是：喷火
{ {"火花",FIRE,1},
{"热风",FIRE,0},
{"喷射火焰",FIRE,2},
{"火焰漩涡",FIRE,1},
{"大字爆炎",FIRE,4} };
SKILL_DATA_ITEM waterSkillDataBase[5] =//水系可学会的技能，初始是：喷水
{ {"水枪",WATER,1},
{"潮漩",WATER,0},
{"冲浪",WATER,2},
{"泡沫",WATER,1},
{"高压水炮",WATER,4} };
SKILL_DATA_ITEM bugSkillDataBase[5] =//虫系可学会的技能，初始是：撕咬
{ {"双针",BUG,1},
{"飞弹针",BUG,0},
{"吸血",BUG,2},
{"连斩",BUG,1},
{"毒液喷射",BUG,4} };
SKILL_DATA_ITEM flySkillDataBase[5] =//飞行系可学会的技能，初始是：起风
{ {"展翅击",FLY,1},
{"啄击",FLY,0},
{"回旋击",FLY,2},
{"狂风",FLY,1},
{"神鸟喙",FLY,4} };
SKILL_DATA_ITEM groundSkillDataBase[5] =//地面系可学会的技能，初始是：击地
{ {"泼沙",GROUND,1},
{"地震",GROUND,0},
{"撒菱",GROUND,2},
{"掷泥",GROUND,1},
{"地裂",GROUND,4} };
SKILL_DATA_ITEM electricSkillDataBase[5] =//电系可学会的技能，初始是：电击
{ {"雷电拳",ELECTRIC,1},
{"电球",ELECTRIC,0},
{"打雷",ELECTRIC,2},
{"电磁波",ELECTRIC,1},
{"十万伏特",ELECTRIC,4} };
SKILL_DATA_ITEM iceSkillDataBase[5] =//冰系可学会的技能，初始是：吐冰
{ {"冰冻拳",ICE,1},
{"冰冻光束",ICE,0},
{"暴风雪",ICE,2},
{"极光束",ICE,1},
{"急冻光束",ICE,4} };
SKILL_DATA_ITEM dragonSkillDataBase[5] =//龙系可学会的技能，初始是：龙爪
{ {"吐息",DRAGON,1},
{"逆鳞",DRAGON,0},
{"龙之怒",DRAGON,2},
{"流星群",DRAGON,1},
{"龙之波动",DRAGON,4} };

#endif
