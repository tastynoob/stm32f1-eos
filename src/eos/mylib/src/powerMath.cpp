#include "powerMath.hpp"
#include "math.h"
Complex::Complex()
{
}
Complex::Complex(deci r, deci i)
{
    this->r = r;
    this->i = i;
}

Complex Complex::operator+(Complex &a)
{
    Complex c;
    c.r = this->r + a.r;
    c.i = this->i + a.i;
    return c;
}

Complex Complex::operator-(Complex &a)
{
    Complex c;
    c.r = this->r - a.r;
    c.i = this->i - a.i;
    return c;
}
Complex Complex::operator*(Complex &a)
{
    Complex c;
    c.r = this->r * a.r - this->i * a.i;
    c.i = a.r * this->i + this->r * a.i;
    return c;
}
Complex Complex::operator/(Complex &a)
{
    Complex c;
    deci p = a.r * a.r + a.i * a.i;
    c.r = (this->r * a.r + this->i * a.i) / p;
    c.i = (a.r * this->i - this->r * a.i) / p;
    return c;
}





Vector3::Vector3(deci x,deci y, deci z){
    this->x = x;
    this->y = y;
    this->z = z;
}
deci Vector3::Length(){
    return sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::operator+(const Vector3& a){
    Vector3 v(x+a.x,y+a.y,z+a.z);
    return v;
}

Vector3 Vector3::operator-(const Vector3& a){
    Vector3 v(x - a.x, y - a.y, z - a.z);
    return v;
}

Vector3 Vector3::operator*(deci a){
    Vector3 v(x * a, y * a, z * a);
    return v;
}


deci Vector3::operator*(const Vector3& a){
    return x * a.x + y * a.y + z * a.z;
}

Vector3 Vector3::operator^(const Vector3& a){
    Vector3 v(y * a.z - a.y * z, z * a.x - a.z * x, x * a.y - a.x * y);
    return v;
}

Vector3 Vector3::operator/(deci a){
    Vector3 v(x / a, y / a, z / a);
    return v;
}



Vector3 Vector3::SpinByVec(Vector3& axis, deci radian){
    Vector3 v  =
    *this * cos(radian) + axis * (axis * *this) * (1 - cos(radian)) + (axis ^ *this) * sin(radian);
    return v;
}

void Vector3::Normalized(){
    deci length = Length();
    x /= length;
    y /= length;
    z /= length;
}


Matrix::Matrix()
{
	h = 0;
	w = 0;
	v = 0;
}

Matrix::Matrix(int h, int w)
{
	this->h = h;
	this->w = w;
	v = new deci[(long long)h * w];
}

Matrix::Matrix(int h, int w, int cycs)
{
	this->h = h;
	this->w = w;
	v = new deci[(long long)h * w];
	cyc(h * w, k) {
		v[k] = (deci)cycs + k;
	}
}

Matrix::Matrix(int h, int w, deci fill)
{
	this->h = h;
	this->w = w;
	v = new deci[(long long)h * w];
	cyc(h * w, k) {
		v[k] = fill;
	}
}

Matrix::Matrix(int h, int w, deci* fs)
{
	this->h = h;
	this->w = w;
	v = new deci[(long long)h * w];
	cyc(h * w, k) {
		v[k] = fs[k];
	}
}

Matrix::~Matrix()
{
	delete[] v;
}

void Matrix::Init(int h, int w, deci fill)
{
	this->h = h;
	this->w = w;
	v = new deci[(long long)h * w];
	cyc(h, h0) {
		cyc(w, w0) {
			MatGetV(*this, h0, w0) = fill;
		}
	}
}

void Matrix::Mul(Matrix& B, Matrix& out)
{
	cyc(out.h, h0) {
		cyc(out.w, w0) {
			deci all = 0;
			cyc(this->w, w1) {
				all += MatGetV(*this, h0, w1) * B[w1][w0];
			}
			out[h0][w0] = all;
		}
	}
}

void Matrix::HdmMul(Matrix& B, Matrix& out)
{
	cyc(h, h0) {
		cyc(w, w0) {
			out[h0][w0] = MatGetV(*this, h0, w0) * B[h0][w0];
		}
	}
}

void Matrix::HMul(Matrix& B, Matrix& out)
{
	cyc(w, w0) {
		deci all = 0;
		cyc(h, h0) {
			all += MatGetV(*this, h0, w0) * B.v[h0];
		}
		out.v[w0] = all;
		//out[0][w0] = all;
	}

}

void Matrix::WMul(Matrix& B, Matrix& out)
{
	cyc(h, h0) {
		deci all = 0;
		cyc(w, w0) {
			all += MatGetV(*this, h0, w0) * B.v[w0];
		}
		out.v[h0] = all;
		//out[h0][0] = all;
	}
}

void Matrix::ScaMul(deci n, Matrix& out)
{
	cyc(w * h, k) {
		out.v[k] = v[k] * n;
	}
}

void Matrix::Add(Matrix& B, Matrix& out)
{
	cyc(h, h0) {
		cyc(w, w0) {
			out[h0][w0] = MatGetV(*this, h0, w0) + B[h0][w0];
		}
	}
}

void Matrix::Sub(Matrix& B, Matrix& out)
{
	cyc(h * w, i) {
		out.v[i] = v[i] - B.v[i];
	}
}
//卷积
void Matrix::Con(Matrix& kernel, int stride, Matrix& out)
{
	int outputH = (h - kernel.h) / stride + 1;//输出图像的高
	int outputW = (w - kernel.w) / stride + 1;//输出图像的宽
	Matrix im2col(kernel.h * kernel.w, outputH * outputW);
	//装值
	cyc(outputH, h0) {
		cyc(outputW, w0) {
			cyc(kernel.h, h1) {
				cyc(kernel.w, w1) {
					im2col[w1 + h1 * kernel.w][w0 + h0 * outputW] = MatGetV(*this, h0*stride+h1, w0*stride+w1);
				}
			}
		}
	}
	im2col.HMul(kernel, out);
}

deci Matrix::Sum()
{
	deci sum = 0;
	cyc(h, i) {
		cyc(w, j) {
			sum+=MatGetV(*this, i, j);
		}
	}
	return sum;
}

void Matrix::Fun(deci(*f)(deci x),Matrix& out)
{
	cyc(h, h0) {
		cyc(w, w0) {
 			out[h0][w0] = f(MatGetV(*this, h0, w0));
		}
	}
}

void Matrix::SwapHW()
{
	int a = h;
	h = w;
	w = a;
}


deci* Matrix::operator[](int i)
{
	return &v[i * w];
}
