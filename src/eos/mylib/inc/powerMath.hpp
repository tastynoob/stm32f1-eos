#pragma once

typedef float deci;

#define PI 3.1415926
//角度转弧度
#define radian(x) ((x) * (PI/180)) 

class Complex {
public:
    deci r;
    deci i;
    Complex();
    Complex(deci r, deci i);

    Complex operator+(Complex& a);
    Complex operator-(Complex& a);
    Complex operator*(Complex& a);
    Complex operator/(Complex& a);
};




class Vector3 {
public:
    Vector3(deci x, deci y, deci z);
    deci x, y, z; 
    deci Length();
    Vector3 operator+(const Vector3& a);
    Vector3 operator-(const Vector3& a);
    //向量内积
    deci operator*(const Vector3& a);
    Vector3 operator*(deci a);
    //向量外积
    Vector3 operator^(const Vector3& a);
    Vector3 operator/(deci a);
    //围绕某一向量旋转
    Vector3 SpinByVec(Vector3& axis, deci radian);
    //归一化
    void Normalized();
};




#define cyc(n, name) for(int name = 0 ; name < (n) ; name++)
#define cyck(s,n,name) for(int name = (s) ; name < (n) ; name++)

class Matrix {
#define MatGetV(mat,h0,w0) (mat).v[(w0) + (h0)*(mat).w]
public:
	int h;
	int w;
    deci* v;
	Matrix();
	Matrix(int h, int w);
	Matrix(int h, int w, int cycs);
    Matrix(int h, int w, deci fill);
    Matrix(int h, int w, deci* fs);
	~Matrix();
	void Init(int h, int w, deci fill);
	//矩阵乘法
	void Mul(Matrix& B, Matrix& out);
	//矩阵哈达玛积
	void HdmMul(Matrix& B, Matrix& out); 
	//矩阵列乘法,每列乘以B竖形矩阵，B矩阵必须只有一行或一列
	void HMul(Matrix& B,Matrix& out);   
	//矩阵行乘法,B矩阵必须只有一行或一列
	void WMul(Matrix& B, Matrix& out);
	//矩阵数乘
	void ScaMul(float n, Matrix& out);
	//矩阵加法
	void Add(Matrix& B, Matrix& out);
	//矩阵减法
	void Sub(Matrix& B, Matrix& out);
	// 卷积运算
	void Con(Matrix& kernel,int stride, Matrix& out);
	//对矩阵元素求和
	float Sum();
	//矩阵函数计算
	void Fun(deci (*f)(deci x),Matrix& out);
	//交换行列，不改变数据
	void SwapHW();

	//索引
	float* operator[](int i);
};