#include<iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main()
{
	int continueFlag = 1;
	srand((int)time(0));
	int price = rand() % 1001 + 1;
	int guess;
	cout << price << endl;
	cout << "������һ����Ʒ�������²���۸�1-1000��������" << endl;
	cout << "���������²�ļ۸�";
	while (continueFlag)
	{
		cin >> guess;
		if (cin.good())//�������������
		{
			if (guess >= 1 && guess <= 1000)//�����Χ��ȷ
			{
				if (guess < price) cout << "û����ô����Ŷ,����һ�ΰɣ�";
				else if (guess == price)
				{
					cout << "��ϲ���¶���~~" << endl;
					continueFlag = 0;
				}
				else if (guess > price) cout << "û����ô��Ŷ������һ�ΰɣ�";
			}
			else//�����Χ����ȷ
			{
				cout << "���������������Ʒ��ֵ��Χ�ˣ����������룺";
			}
		}
		else//������벻������
		{
			cout << "���벻�����������������룺";
			cin.clear();//��������־
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');//������뻺����
	}

	return 0;
}