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
	Point& operator --()//--p����
	{
		X--;
		Y--;
		return *this;
	}
	Point& operator ++()//++p����
	{
		X++;
		Y++;
		return *this;
	}
	Point operator --(int)//p--����
	{
		Point tmp(X, Y);
		X--;
		Y--;
		return tmp;
	}Point operator ++(int)//p++����
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
	//cout << "������Point���޲������캯��" << endl;
	X = 0;
	Y = 0;
}
Point::Point(double newX, double newY)
{
	//cout << "������Point���в������캯��" << endl;
	X = newX;
	Y = newY;
}
Point::Point(const Point& p)
{
	//cout << "������Point�Ŀ������캯��" << endl;
	X = p.X;
	Y = p.Y;
}
Point::~Point()
{
	//cout << "������Point����������" << endl;
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