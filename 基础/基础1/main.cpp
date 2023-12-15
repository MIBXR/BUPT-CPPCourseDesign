#include<iostream>
using namespace std;
//不用对象
void Madd(int** pA1, int** pA2, int** pA3)//pA1 + pA2 -> pA3
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			pA3[i][j] = pA1[i][j] + pA2[i][j];
		}
	}
}
void Msub(int** pA1, int** pA2, int** pA3)//pA1 - pA2 -> pA3
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			pA3[i][j] = pA1[i][j] - pA2[i][j];
		}
	}
}
void Mout(int** p)//输出矩阵
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cout << p[i][j] << "\t";
		}
		cout << endl;
	}
}
void Mfree(int** p)//释放矩阵
{
	for (int i = 0; i < 4; i++)
	{
		free(p[i]);
	}
	free(p);
}
int main()
{
	int** pA1 = new int* [4];
	int** pA2 = new int* [4];
	int** pA3 = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		pA1[i] = new int[5];
		pA2[i] = new int[5];
		pA3[i] = new int[5];
	}
	cout << "初始化A1，A2：" << endl;
	cout << "A1:" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> pA1[i][j];
		}
	}
	cout << "A2:" << endl;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			cin >> pA2[i][j];
		}
	}
	Madd(pA1, pA2, pA3);
	cout << "A3 = A1 + A2:" << endl;
	Mout(pA3);
	Msub(pA1, pA2, pA3);
	cout << "A3 = A1 - A2:" << endl;
	Mout(pA3);

	Mfree(pA1);
	Mfree(pA2);
	Mfree(pA3);

	return 0;
}