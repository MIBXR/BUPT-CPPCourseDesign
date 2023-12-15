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
	cout << "我们有一件商品，请您猜测其价格（1-1000的整数）" << endl;
	cout << "请输入您猜测的价格：";
	while (continueFlag)
	{
		cin >> guess;
		if (cin.good())//如果输入是整数
		{
			if (guess >= 1 && guess <= 1000)//如果范围正确
			{
				if (guess < price) cout << "没有这么便宜哦,再试一次吧：";
				else if (guess == price)
				{
					cout << "恭喜！猜对啦~~" << endl;
					continueFlag = 0;
				}
				else if (guess > price) cout << "没有这么贵哦，再试一次吧：";
			}
			else//如果范围不正确
			{
				cout << "您输入的数超过商品价值范围了，请重新输入：";
			}
		}
		else//如果输入不是整数
		{
			cout << "输入不是整数，请重新输入：";
			cin.clear();//清除错误标志
		}
		cin.ignore(numeric_limits<streamsize>::max(), '\n');//清除输入缓冲区
	}

	return 0;
}