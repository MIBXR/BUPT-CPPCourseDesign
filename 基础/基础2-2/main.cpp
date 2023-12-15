#include<iostream>
using namespace std;

class Matrix
{
public:
	Matrix();
	Matrix(int r, int c);
	Matrix(const Matrix& m);
	~Matrix();
	Matrix& operator =(const Matrix& m)//��ֵ����
	{
		if (this != &m)//�Ը�ֵ�ж�
		{
			this->~Matrix();//���ͷ�ԭ�ռ�
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
	void Minit();//���뺯��
	void Mshow();//�������
	Matrix Madd(Matrix m1, Matrix m2, Matrix& m3);//m1 + m2 -> m3
	Matrix Msub(Matrix m1, Matrix m2, Matrix& m3);//m1 - m2 -> m3
private:
	int row, col;
	int** data;
};
Matrix::Matrix()
{
	row = 4;
	col = 5;//Ĭ��4*5
	data = new  int* [row];
	for (int i = 0; i < row; i++)
	{
		data[i] = new int [col];
		for (int j = 0; j < col; j++)
		{
			data[i][j] = 0;//Ĭ�ϳ�ʼ��Ϊ�����
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
			data[i][j] = 0;//Ĭ�ϳ�ʼ��Ϊ�����
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
	cout << "����������ʼ��ֵ����С" << row << "*" << col << "�����ո�ָ����س����У�" << endl;
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
	cout << "����Ϊ��" << endl;
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
		m3.~Matrix();//���m3ԭ���ݲ�ʹ��m3��С���ϼ���Ҫ��
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
		cout << "��ӵ��������С��ͬ���޷�����" << endl;
	}
	return m3;
}
Matrix Matrix::Msub(Matrix m1, Matrix m2, Matrix& m3)
{
	if(m1.row == m2.row && m1.col == m2.col)
	{
		m3.~Matrix();//���m3ԭ���ݲ�ʹ��m3��С���ϼ���Ҫ��
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
	cout << "������������С��ͬ���޷�����" << endl;
	}
	return m3;
}

int main()
{
	int A1row, A1col, A2row, A2col;
	cout << "���������A1��С,��ʽ\"���� �ո� ����\"��" << endl;
	cin >> A1row >> A1col;
	cout << "���������A2��С,��ʽ\"���� �ո� ����\"��" << endl;
	cin >> A2row >> A2col;

	//��ͨ������
	Matrix A1(A1row,A1col), A2(A2row,A2col), A3;
	cout << "�Ѳ�����ͨ����������������A1��A2���Լ�Ĭ�ϴ�С�ľ���A3����������A1��A2���о����ʼ��" << endl;
	A1.Minit();
	A2.Minit();
	cout << "���� A3 = A1 + A2: " << endl;
	A3 = A3.Madd(A1, A2, A3);
	A3.Mshow();
	cout << "���� A3 = A1 - A2: " << endl;
	A3 = A3.Msub(A1, A2, A3);
	A3.Mshow();
	//������������new�����ڶ����ڣ�����ϵͳ���Զ���������������������ʽ���ͷſռ�

	//��new������
	Matrix* pA1 = new Matrix(A1row, A1col);
	Matrix* pA2 = new Matrix(A2row, A2col);
	Matrix* pA3 = new Matrix;
	cout << "����new����������������pA1��pA2���Լ�Ĭ�ϴ�С�ľ���pA3����������pA1��pA2���о����ʼ��" << endl;
	(*pA1).Minit();
	(*pA2).Minit();
	(*pA3) = (*pA3).Madd(*pA1, *pA2, *pA3);
	cout << "���� pA3 = pA1 + pA2: " << endl;
	(*pA3).Mshow();
	(*pA3) = (*pA3).Msub(*pA1, *pA2, *pA3);
	cout << "���� pA3 = pA1 - pA2: " << endl;
	(*pA3).Mshow();
	delete pA1;
	delete pA2;
	delete pA3;
	//�����������ڶ����⻹��new������������Ҫ��ʽ���ͷſռ�
	
	return  0;
}