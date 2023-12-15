#include<iostream>
#define PI 3.1415//Բ���ʽ���ֵ
using namespace std;

class Shape
{
public:
	Shape() { cout << "[������Shape���޲������캯��]" << endl; }
	Shape(const Shape& p) { cout << "[������Shape�Ŀ������캯��]" << endl; }
	~Shape() { cout << "[������Shape����������]" << endl; }
	virtual double calculateArea() { cout << "�����޷��������" << endl; return -1; }
	virtual void outputArea();
};
void Shape::outputArea()
{
	cout << "[���û���outputArea()]" << endl;
	cout << "����ǣ�" << calculateArea() << endl << endl;
}

class Rectangle :public Shape
{
public:
	Rectangle();
	Rectangle(double a, double b);
	Rectangle(const Rectangle& p);
	~Rectangle() { cout << "[������Rectangle����������]" << endl; }
	virtual double calculateArea() { cout << "[����Rectangle��calculateArea]" << endl; return length * width; }
	void output() { cout << "���ǳ�" << length << "��" << width << "�ľ���" << endl; }
	void outputArea();
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
void Rectangle::outputArea()
{
	cout << "[����Rectangle��outputArea()]" << endl;
	cout << "����ǣ�" << calculateArea() << endl << endl;
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
	void outputArea();
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
void Circle::outputArea()
{
	cout << "[����Circle��outputArea()]" << endl;
	cout << "����ǣ�" << calculateArea() << endl << endl;
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
	void outputArea();
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
void Square::outputArea()
{
	cout << "[����Square��outputArea()]" << endl;
	cout << "����ǣ�" << calculateArea() << endl << endl;
}

int main()
{
	Rectangle* pR = new Rectangle(3, 2);
	Circle* pC = new Circle(2.5);
	Square* pS = new Square(4);
	Shape* p1 = pR;
	Shape* p2 = pC;
	Shape* p3 = pS;


	(*pR).output();
	(*p1).outputArea();
	(*pC).output();
	(*p2).outputArea();
	(*pS).output();
	(*p3).outputArea();

	delete pR;
	delete pC;
	delete pS;

	return 0;
}