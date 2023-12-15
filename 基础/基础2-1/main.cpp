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
	double distance(Point A,Point B);
};
Point::Point()
{
	cout << "调用了Point的无参数构造函数" << endl;
	X = 0;
	Y = 0;
}
Point::Point(double newX, double newY)
{
	cout << "调用了Point的有参数构造函数" << endl;
	X = newX;
	Y = newY;
}
Point::Point(const Point& p)
{
	cout << "调用了Point的拷贝构造函数" << endl;
	X = p.X;
	Y = p.Y;
}
Point::~Point()
{
	cout << "调用了Point的析构函数" << endl;
}
double Point::distance(Point A,Point B)
{
	double disSquare = 0;
	disSquare = (A.X - B.X) * (A.X - B.X) + (A.Y - B.Y) * (A.Y - B.Y);
	return sqrt(disSquare);
}

class Circle
{
private:
	Point center;
	double radius;
public:
	Circle();
	Circle(Point newCenter, double newRad);
	Circle(const Circle& c);
	~Circle();
	int isCross(Circle A,Circle B);
};
Circle::Circle()
	:center(0, 0)
{
	cout << "调用了Circle的无参数构造函数" << endl;
	radius = 0;
}
Circle::Circle(Point newCenter, double newRad)
	:center(newCenter)
{
	cout << "调用了Circle的有参数构造函数" << endl;
	radius = newRad;
}
Circle::Circle(const Circle& c)
	:center(c.center)
{
	cout << "调用了Circle的拷贝构造函数" << endl;
	radius = c.radius;
}
Circle::~Circle()
{
	cout << "调用了Circle的析构函数" << endl;
}
int Circle::isCross(Circle A, Circle B)
{
	Point tmp;
	double dis = tmp.distance(A.center, B.center);
	double radSum = A.radius + B.radius;
	if (dis < radSum) return 1;
	else if (dis == radSum) return 0;
	else return -1;
}
int main()
{
	int tmp;
	cout << endl << "初始化圆C1，圆心(0,0)，半径4" << endl << endl;
	Circle C1(Point(0, 0), 4);
	cout << endl << "初始化圆C2，圆心(4,3)，半径1" << endl << endl;
	Circle C2(Point(4, 3), 1);
	int flagCross = C1.isCross(C1, C2);
	switch (flagCross)
	{
	case 1 :
		cout << endl << "相交" << endl << endl;
		break;
	case 0 :
		cout << endl << "相切" << endl << endl;
		break;
	case -1 :
		cout << endl << "相离" << endl << endl;
		break;
	default :
		cout << endl << "ERROR in Judge!" << endl << endl;
	}

	return 0;
}