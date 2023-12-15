#include<iostream>
#define PI 3.1415//Բ���ʽ���ֵ
using namespace std;

class Shape
{
public:
	Shape() { cout << "[������Shape���޲������캯��]" << endl; }
	Shape(const Shape& p) { cout << "[������Shape�Ŀ������캯��]" << endl; }
	~Shape() { cout << "[������Shape����������]" << endl; }
	virtual double calculateArea() = 0;//���麯��
};

class Rectangle :public Shape
{
public:
	Rectangle();
	Rectangle(double a, double b);
	Rectangle(const Rectangle& p);
	~Rectangle() { cout << "[������Rectangle����������]" << endl; }
	double calculateArea() { cout << "[����Rectangle��calculateArea]" << endl; return length * width; }
	void output() { cout << "���ǳ�" << length << "��" << width << "�ľ���" << endl; }
private:
	double length;//��
	double width;//��
};
Rectangle::Rectangle()
{
	length = 0;
	width = 0;
	cout << "[������Rectangle���޲������캯��]" << endl;
}
Rectangle::Rectangle(double a, double b)
{
	length = a;
	width = b;
	cout << "[������Rectangle���в������캯��]" << endl;
}
Rectangle::Rectangle(const Rectangle& p)
{
	length = p.length;
	width = p.width;
	cout << "[������Rectangle�Ŀ������캯��]" << endl;
}

class Circle :public Shape
{
public:
	Circle();
	Circle(double a);
	Circle(const Circle& p);
	~Circle() { cout << "[������Circle����������]" << endl; }
	double calculateArea() { cout << "[����Circle��calculateArea]" << endl; return PI * radius * radius; }
	void output() { cout << "���ǰ뾶" << radius << "��Բ��" << endl; }
private:
	double radius;//�뾶
};
Circle::Circle(double a)
{
	radius = a;
	cout << "[������Circle���в������캯��]" << endl;
}
Circle::Circle()
{
	radius = 0;
	cout << "[������Circle���޲������캯��]" << endl;
}
Circle::Circle(const Circle& p)
{
	radius = p.radius;
	cout << "[������Circle�Ŀ������캯��]" << endl;
}

class Square :public Rectangle
{
public:
	Square();
	Square(double a);
	Square(const Square& p);
	~Square() { cout << "[������Square����������]" << endl; }
	double calculateArea() { cout << "[����Square��calculateArea]" << endl; return edge * edge; }
	void output() { cout << "���Ǳ߳�" << edge << "��������" << endl; }
	Square& operator =(const Square& m)//��ֵ����
	{
		if (this != &m)//�Ը�ֵ�ж�
		{
			edge = m.edge;
		}
		return *this;
	}
private:
	double edge;//�߳�
};
Square::Square(double a)
{
	edge = a;
	cout << "[������Square���в������캯��]" << endl;
}
Square::Square()
{
	edge = 0;
	cout << "[������Square���޲������캯��]" << endl;
}
Square::Square(const Square& p)
{
	edge = p.edge;
	cout << "[������Square�Ŀ������캯��]" << endl;
}

int main()
{
	Rectangle* pR = new Rectangle(3, 2);
	Circle* pC = new Circle(2.5);
	Square* pS = new Square(4);
	//Shape* p = pS;

	cout << endl;
	(*pR).output();
	cout << "����ǣ�" << (*pR).calculateArea() << endl;
	cout << endl;
	cout << endl;
	(*pC).output();
	cout << "����ǣ�" << (*pC).calculateArea() << endl;
	cout << endl;
	cout << endl;
	(*pS).output();
	cout << "����ǣ�" << (*pS).calculateArea() << endl;
	cout << endl;

	delete pR;
	delete pC;
	delete pS;

	return 0;
}