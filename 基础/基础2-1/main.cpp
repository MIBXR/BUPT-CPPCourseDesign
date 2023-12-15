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
	cout << "������Point���޲������캯��" << endl;
	X = 0;
	Y = 0;
}
Point::Point(double newX, double newY)
{
	cout << "������Point���в������캯��" << endl;
	X = newX;
	Y = newY;
}
Point::Point(const Point& p)
{
	cout << "������Point�Ŀ������캯��" << endl;
	X = p.X;
	Y = p.Y;
}
Point::~Point()
{
	cout << "������Point����������" << endl;
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
	cout << "������Circle���޲������캯��" << endl;
	radius = 0;
}
Circle::Circle(Point newCenter, double newRad)
	:center(newCenter)
{
	cout << "������Circle���в������캯��" << endl;
	radius = newRad;
}
Circle::Circle(const Circle& c)
	:center(c.center)
{
	cout << "������Circle�Ŀ������캯��" << endl;
	radius = c.radius;
}
Circle::~Circle()
{
	cout << "������Circle����������" << endl;
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
	cout << endl << "��ʼ��ԲC1��Բ��(0,0)���뾶4" << endl << endl;
	Circle C1(Point(0, 0), 4);
	cout << endl << "��ʼ��ԲC2��Բ��(4,3)���뾶1" << endl << endl;
	Circle C2(Point(4, 3), 1);
	int flagCross = C1.isCross(C1, C2);
	switch (flagCross)
	{
	case 1 :
		cout << endl << "�ཻ" << endl << endl;
		break;
	case 0 :
		cout << endl << "����" << endl << endl;
		break;
	case -1 :
		cout << endl << "����" << endl << endl;
		break;
	default :
		cout << endl << "ERROR in Judge!" << endl << endl;
	}

	return 0;
}