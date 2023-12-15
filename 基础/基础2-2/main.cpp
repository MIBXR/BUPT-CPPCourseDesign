#include<iostream>
using namespace std;

class Matrix
{
public:
	Matrix();
	Matrix(int r, int c);
	Matrix(const Matrix& m);
	~Matrix();
	Matrix& operator =(const Matrix& m)//赋值重载
	{
		if (this != &m)//自赋值判断
		{
			this->~Matrix();//先释放原空间
			row = m.row;
			col = m.col;
			data = new  int* [row];
			for (int i = 0; i < row; i++)
			{
				data[i] = new int[col];
				for (int j = 0; j < col; j++)
				{
					data[i][j] = m.data[i][j];
				}
			}
		}
		return *this;
	}
	void Minit();//输入函数
	void Mshow();//输出函数
	Matrix Madd(Matrix m1, Matrix m2, Matrix& m3);//m1 + m2 -> m3
	Matrix Msub(Matrix m1, Matrix m2, Matrix& m3);//m1 - m2 -> m3
private:
	int row, col;
	int** data;
};
Matrix::Matrix()
{
	row = 4;
	col = 5;//默认4*5
	data = new  int* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new int [col];
		for (int j = 0; j < col; j++)
		{
			data[i][j] = 0;//默认初始化为零矩阵
		}
	}
}
Matrix::Matrix(int r, int c)
{
	row = r;
	col = c;
	data = new  int* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			data[i][j] = 0;//默认初始化为零矩阵
		}
	}
}
Matrix::Matrix(const Matrix& m)
{
	row = m.row;
	col = m.col;
	data = new  int* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new int[col];
		for (int j = 0; j < col; j++)
		{
			data[i][j] = m.data[i][j];
		}
	}
}
Matrix::~Matrix()
{
	for (int i = 0; i < row; i++)
	{
		delete[] data[i];
	}
	delete[] data;
}
void Matrix::Minit()
{
	cout << "请输入矩阵初始化值（大小" << row << "*" << col << "）。空格分隔，回车换行：" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cin >> data[i][j];
		}
	}
}
void Matrix::Mshow()
{
	cout << "矩阵为：" << endl;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			cout << data[i][j] << "\t";
		}
		cout << endl;
	}
}
Matrix Matrix::Madd(Matrix m1, Matrix m2, Matrix& m3)
{
	if (m1.row == m2.row && m1.col == m2.col)
	{
		m3.~Matrix();//清除m3原数据并使得m3大小符合计算要求
		m3.row = m1.row;
		m3.col = m1.col;
		m3.data = new  int* [row];
		for (int i = 0; i < row; i++)
		{
			m3.data[i] = new int[col];
			for (int j = 0; j < col; j++)
			{
				m3.data[i][j] = m1.data[i][j] + m2.data[i][j];
			}
		}
		//m3.Mshow();
	}
	else
	{
		cout << "相加的两矩阵大小不同，无法运算" << endl;
	}
	return m3;
}
Matrix Matrix::Msub(Matrix m1, Matrix m2, Matrix& m3)
{
	if(m1.row == m2.row && m1.col == m2.col)
	{
		m3.~Matrix();//清除m3原数据并使得m3大小符合计算要求
		m3.row = m1.row;
		m3.col = m1.col;
		m3.data = new  int* [row];
		for (int i = 0; i < row; i++)
		{
			m3.data[i] = new int[col];
			for (int j = 0; j < col; j++)
			{
				m3.data[i][j] = m1.data[i][j] - m2.data[i][j];
			}
		}
		//m3.Mshow();
	}
	else
	{
	cout << "相减的两矩阵大小不同，无法运算" << endl;
	}
	return m3;
}

int main()
{
	int A1row, A1col, A2row, A2col;
	cout << "请输入矩阵A1大小,格式\"行数 空格 列数\"：" << endl;
	cin >> A1row >> A1col;
	cout << "请输入矩阵A2大小,格式\"行数 空格 列数\"：" << endl;
	cin >> A2row >> A2col;

	//普通声明：
	Matrix A1(A1row,A1col), A2(A2row,A2col), A3;
	cout << "已采用普通声明建立两个矩阵A1，A2；以及默认大小的矩阵A3。接下来对A1和A2进行矩阵初始化" << endl;
	A1.Minit();
	A2.Minit();
	cout << "计算 A3 = A1 + A2: " << endl;
	A3 = A3.Madd(A1, A2, A3);
	A3.Mshow();
	cout << "计算 A3 = A1 - A2: " << endl;
	A3 = A3.Msub(A1, A2, A3);
	A3.Mshow();
	//此种声明由于new操作在对象内，所以系统会自动调用析构函数，无需显式地释放空间

	//用new声明：
	Matrix* pA1 = new Matrix(A1row, A1col);
	Matrix* pA2 = new Matrix(A2row, A2col);
	Matrix* pA3 = new Matrix;
	cout << "已用new声明建立两个矩阵pA1，pA2；以及默认大小的矩阵pA3。接下来对pA1和pA2进行矩阵初始化" << endl;
	(*pA1).Minit();
	(*pA2).Minit();
	(*pA3) = (*pA3).Madd(*pA1, *pA2, *pA3);
	cout << "计算 pA3 = pA1 + pA2: " << endl;
	(*pA3).Mshow();
	(*pA3) = (*pA3).Msub(*pA1, *pA2, *pA3);
	cout << "计算 pA3 = pA1 - pA2: " << endl;
	(*pA3).Mshow();
	delete pA1;
	delete pA2;
	delete pA3;
	//此种声明由于对象外还有new操作，所以需要显式地释放空间
	
	return  0;
}