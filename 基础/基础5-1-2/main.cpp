#include<iostream>
#define PI 3.1415//圆周率近似值
using namespace std;

class Shape
{
public:
	Shape() { cout << "[调用了Shape的无参数构造函数]" << endl; }
	Shape(const Shape& p) { cout << "[调用了Shape的拷贝构造函数]" << endl; }
	~Shape() { cout << "[调用了Shape的析构函数]" << endl; }
	virtual double calculateArea() = 0;//纯虚函数
};

class Rectangle :public Shape
{
public:
	Rectangle();
	Rectangle(double a, double b);
	Rectangle(const Rectangle& p);
	~Rectangle() { cout << "[调用了Rectangle的析构函数]" << endl; }
	double calculateArea() { cout << "[调用Rectangle的calculateArea]" << endl; return length * width; }
	void output() { cout << "这是长" << length << "宽" << width << "的矩形" << endl; }
private:
	double length;//长
	double width;//宽
};
Rectangle::Rectangle()
{
	length = 0;
	width = 0;
	cout << "[调用了Rectangle的无参数构造函数]" << endl;
}
Rectangle::Rectangle(double a, double b)
{
	length = a;
	width = b;
	cout << "[调用了Rectangle的有参数构造函数]" << endl;
}
Rectangle::Rectangle(const Rectangle& p)
{
	length = p.length;
	width = p.width;
	cout << "[调用了Rectangle的拷贝构造函数]" << endl;
}

class Circle :public Shape
{
public:
	Circle();
	Circle(double a);
	Circle(const Circle& p);
	~Circle() { cout << "[调用了Circle的析构函数]" << endl; }
	double calculateArea() { cout << "[调用Circle的calculateArea]" << endl; return PI * radius * radius; }
	void output() { cout << "这是半径" << radius << "的圆形" << endl; }
private:
	double radius;//半径
};
Circle::Circle(double a)
{
	radius = a;
	cout << "[调用了Circle的有参数构造函数]" << endl;
}
Circle::Circle()
{
	radius = 0;
	cout << "[调用了Circle的无参数构造函数]" << endl;
}
Circle::Circle(const Circle& p)
{
	radius = p.radius;
	cout << "[调用了Circle的拷贝构造函数]" << endl;
}

class Square :public Rectangle
{
public:
	Square();
	Square(double a);
	Square(const Square& p);
	~Square() { cout << "[调用了Square的析构函数]" << endl; }
	double calculateArea() { cout << "[调用Square的calculateArea]" << endl; return edge * edge; }
	void output() { cout << "这是边长" << edge << "的正方形" << endl; }
	Square& operator =(const Square& m)//赋值重载
	{
		if (this != &m)//自赋值判断
		{
			edge = m.edge;
		}
		return *this;
	}
private:
	double edge;//边长
};
Square::Square(double a)
{
	edge = a;
	cout << "[调用了Square的有参数构造函数]" << endl;
}
Square::Square()
{
	edge = 0;
	cout << "[调用了Square的无参数构造函数]" << endl;
}
Square::Square(const Square& p)
{
	edge = p.edge;
	cout << "[调用了Square的拷贝构造函数]" << endl;
}

int main()
{
	Rectangle* pR = new Rectangle(3, 2);
	Circle* pC = new Circle(2.5);
	Square* pS = new Square(4);
	//Shape* p = pS;

	cout << endl;
	(*pR).output();
	cout << "面积是：" << (*pR).calculateArea() << endl;
	cout << endl;
	cout << endl;
	(*pC).output();
	cout << "面积是：" << (*pC).calculateArea() << endl;
	cout << endl;
	cout << endl;
	(*pS).output();
	cout << "面积是：" << (*pS).calculateArea() << endl;
	cout << endl;

	delete pR;
	delete pC;
	delete pS;

	return 0;
}