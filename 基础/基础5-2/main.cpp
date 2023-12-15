#include<iostream>
#include<math.h>
using namespace std;

class Point
{
private:
	double X;
	double Y;
public:
	Point();
	Point(double newX, double newY);
	Point(const Point& p);
	~Point();
	Point& operator --()//--p重载
	{
		X--;
		Y--;
		return *this;
	}
	Point& operator ++()//++p重载
	{
		X++;
		Y++;
		return *this;
	}
	Point operator --(int)//p--重载
	{
		Point tmp(X, Y);
		X--;
		Y--;
		return tmp;
	}Point operator ++(int)//p++重载
	{
		Point tmp(X, Y);
		X++;
		Y++;
		return tmp;
	}
	void show();
};
Point::Point()
{
	//cout << "调用了Point的无参数构造函数" << endl;
	X = 0;
	Y = 0;
}
Point::Point(double newX, double newY)
{
	//cout << "调用了Point的有参数构造函数" << endl;
	X = newX;
	Y = newY;
}
Point::Point(const Point& p)
{
	//cout << "调用了Point的拷贝构造函数" << endl;
	X = p.X;
	Y = p.Y;
}
Point::~Point()
{
	//cout << "调用了Point的析构函数" << endl;
}
void Point::show()
{
	cout << "Point is at (" << X << "," << Y << ")." << endl << endl;
}

int main()
{
	Point p(0, 1);
	cout << "At first,";
	p.show();
	p--;
	cout << "Then \"p--\",";
	p.show();
	p++;
	cout << "Then \"p++\",";
	p.show();
	--p;
	cout << "Then \"--p\",";
	p.show();
	++p;
	cout << "Then \"++p\",";
	p.show();
}