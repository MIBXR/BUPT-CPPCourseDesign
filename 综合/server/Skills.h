/************************************************************/
/* @�γ�����		C++�γ����	��Ŀ�� �û�ע����ƽ̨��¼	*/
/* @���ߣ�			л�2018211208��						*/
/* @��ʦ��			���鲨									*/
/* @����޸�ʱ�䣺	2020/08/22 17��52						*/
/* @�ļ�����		Skills.h								*/
/* @�ļ�˵����		�������Ԫ�������Լ���ѧ��ļ���		*/
/*----------------------------------------------------------*/
/* @��ע��			��������ѭ�����ù�˾ϰ�����ʹ�á�����*/
/*					��(Pokemon)����ָ����С����				*/
/************************************************************/

#ifndef Skills_h
#define Skills_h

//Ԫ�ض���
#define NORMAL 0//��ͨ
#define FIRE 1//��
#define GRASS 2//��
#define WATER 3//ˮ
#define BUG 4//��
#define FLY 5//��
#define GROUND 6//��
#define ELECTRIC 7//��
#define ICE 8//��
#define DRAGON 9//��

class Skill//����
{
private:
	char name[32];//������
	int elem;//Ԫ������
	int ex;//�����˺��ӳ�
public:
	Skill();//���캯��
	Skill(int type, const char* newName, int newEx);//���캯��
	Skill(const Skill& s);//�������캯��
	~Skill() {}//��������
	Skill& operator =(const Skill& m)//��ֵ����
	{
		if (this != &m)//�Ը�ֵ�ж�
		{
			elem = m.elem;
			strcpy(name, m.name);
			ex = m.ex;
		}
		return *this;
	}
	int getElem() { return elem; };//��ȡԪ������
	char* getName() { return name; };//��ȡ������
	int getEx() { return ex; };//��ȡ�����˺�ֵ
};
Skill::Skill()//Ĭ����ʽΪ��ͨϵ�������Ĵ�,�޹����ӳ�
{
	elem = 0;
	strcpy(name, "�Ĵ�");
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

typedef struct skillDataItem//�ṹ�壺��¼����һ�����ܵ����ݣ����ڴ���
{
	char name[32];
	int elem;
	int ex;
}SKILL_DATA_ITEM;

SKILL_DATA_ITEM grassSkillDataBase[5] =//��ϵ��ѧ��ļ��ܣ���ʼ�ǣ���Ҷ�쵶
{ {"�ٱ�",GRASS,1},
{"��ȡ",GRASS,0},
{"�չ�",GRASS,2},
{"������",GRASS,1},
{"���ӻ���ǹ",GRASS,4} };
SKILL_DATA_ITEM fireSkillDataBase[5] =//��ϵ��ѧ��ļ��ܣ���ʼ�ǣ����
{ {"��",FIRE,1},
{"�ȷ�",FIRE,0},
{"�������",FIRE,2},
{"��������",FIRE,1},
{"���ֱ���",FIRE,4} };
SKILL_DATA_ITEM waterSkillDataBase[5] =//ˮϵ��ѧ��ļ��ܣ���ʼ�ǣ���ˮ
{ {"ˮǹ",WATER,1},
{"����",WATER,0},
{"����",WATER,2},
{"��ĭ",WATER,1},
{"��ѹˮ��",WATER,4} };
SKILL_DATA_ITEM bugSkillDataBase[5] =//��ϵ��ѧ��ļ��ܣ���ʼ�ǣ�˺ҧ
{ {"˫��",BUG,1},
{"�ɵ���",BUG,0},
{"��Ѫ",BUG,2},
{"��ն",BUG,1},
{"��Һ����",BUG,4} };
SKILL_DATA_ITEM flySkillDataBase[5] =//����ϵ��ѧ��ļ��ܣ���ʼ�ǣ����
{ {"չ���",FLY,1},
{"�Ļ�",FLY,0},
{"������",FLY,2},
{"���",FLY,1},
{"�����",FLY,4} };
SKILL_DATA_ITEM groundSkillDataBase[5] =//����ϵ��ѧ��ļ��ܣ���ʼ�ǣ�����
{ {"��ɳ",GROUND,1},
{"����",GROUND,0},
{"����",GROUND,2},
{"����",GROUND,1},
{"����",GROUND,4} };
SKILL_DATA_ITEM electricSkillDataBase[5] =//��ϵ��ѧ��ļ��ܣ���ʼ�ǣ����
{ {"�׵�ȭ",ELECTRIC,1},
{"����",ELECTRIC,0},
{"����",ELECTRIC,2},
{"��Ų�",ELECTRIC,1},
{"ʮ�����",ELECTRIC,4} };
SKILL_DATA_ITEM iceSkillDataBase[5] =//��ϵ��ѧ��ļ��ܣ���ʼ�ǣ��±�
{ {"����ȭ",ICE,1},
{"��������",ICE,0},
{"����ѩ",ICE,2},
{"������",ICE,1},
{"��������",ICE,4} };
SKILL_DATA_ITEM dragonSkillDataBase[5] =//��ϵ��ѧ��ļ��ܣ���ʼ�ǣ���צ
{ {"��Ϣ",DRAGON,1},
{"����",DRAGON,0},
{"��֮ŭ",DRAGON,2},
{"����Ⱥ",DRAGON,1},
{"��֮����",DRAGON,4} };

#endif
