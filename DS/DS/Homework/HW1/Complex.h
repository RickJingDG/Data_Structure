#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：Complex.h
* 文件标识：未定义
* 摘 要：复数类，包含复数的实部、虚部、模长、辐角，和一些基本运算。
*
* 当前版本：1.2
* 版本概要：改进了复数的写入模式，增加了复数的指数运算，调小了误差Eplsion的数量级，最重要的是增加了仅用double型通过指数运算得到复数的方法。
* 作 者：RickJingDG
* 完成日期：2023年4月17日
*
* 取代版本：1.1
* 版本概要：添加了辐角，补充复数与实数的基本四则运算和复数与实数的比较，针对双精度浮点数重写了“==”的判断方法，初步的规范了代码格式。
* 作 者：RickJingDG
* 完成日期：2023年3月25日
*
*/

#include <iostream> //库文件引用和文件信息隔开一行
#include <cmath>// 引用标准库的头文件

//#include "myheader.h"// 引用非标准库的头文件

using namespace std;

//=============全局变量定义开始=======================
const double Epslion = 1e-10;//用于双精度浮点数比较大小
//=============全局变量定义结束=======================

//=============结构体定义开始=======================
/*
* 基础的结构体：无
*/
//struct structType
//{
//	int intType;
//	char charType;
//};
//=============结构体定义结束=======================

//=============类定义开始=======================

//复数类
class Complex 
{
public:
    //构造函数
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag),m_modulus(sqrt(imag* imag + real * real)),m_arg(atan2(imag, real)/*/ 180 * acos(-1.0)转换成角度制*/ )
    { }
    //运算符重载
    //以全局函数的形式重载
    friend Complex pow(const Complex& c1, const Complex& c2);
    friend Complex pow(const Complex& c1, const double m);
    friend Complex pow(const double m, const Complex& c2);
    friend Complex pow(const double m, const double n,bool judge);
    friend Complex operator+(const Complex& c1, const Complex& c2);//友元函数可以访问对象的私有成员
    friend Complex operator+(const Complex& c1, const double m);//由于数字数据类型太多，这里就写个与实数的关系
    friend Complex operator+(const double m, const Complex& c2);
    friend Complex operator-(const Complex& c1, const Complex& c2);
    friend Complex operator-(const Complex& c1, const double m);
    friend Complex operator-(const double m, const Complex& c2);
    friend Complex operator*(const Complex& c1, const Complex& c2);
    friend Complex operator*(const Complex& c1, const double m);
    friend Complex operator*(const double m, const Complex& c2);
    friend Complex operator/(const Complex& c1, const Complex& c2);
    friend Complex operator/(const Complex& c1, const double m);
    friend Complex operator/(const double m, const Complex& c2);
    friend bool operator==(const Complex& c1, const Complex& c2);
    friend bool operator==(const Complex& c1, const double m);
    friend bool operator==(const double m, const Complex& c1);
    friend bool operator!=(const Complex& c1, const Complex& c2);
    friend bool operator!=(const Complex& c1, const double m);
    friend bool operator!=(const double m, const Complex& c2);
    friend bool operator> (const Complex& c1, const Complex& c2);
    friend bool operator>(const Complex& c1, const double m);
    friend bool operator>(const double m, const Complex& c1);
    friend bool operator>= (const Complex& c1, const Complex& c2);
    friend bool operator>= (const Complex& c1, const double m);
    friend bool operator>= (const double m, const Complex& c2);
    friend bool operator< (const Complex& c1, const Complex& c2);
    friend bool operator<(const Complex& c1, const double m);
    friend bool operator<(const double m, const Complex& c1);
    friend bool operator<= (const Complex& c1, const Complex& c2);
    friend bool operator<= (const Complex& c1, const double m);
    friend bool operator<= (const double m, const Complex& c2);
    //以成员函数的形式重载
    Complex& operator+=(const Complex& c);//增赋值
    Complex& operator-=(const Complex& c);//减赋值
    Complex& operator*=(const Complex& c);//乘赋值
    Complex& operator/=(const Complex& c);//除赋值
    operator double() { return m_real; }  //重载强制类型转换运算符 double
    void display();
    void write_Complex(double r,double i);//写入函数
    double real() const { return m_real; }//读取函数
    double imag() const { return m_imag; }
    double modulus() const { return m_modulus; }
    double arg() const { return m_arg; }
private:
    double m_real;  //实部
    double m_imag;  //虚部
    double m_modulus;  //模长 
    double m_arg;  //辐角主值，单位度。
    void write_Real(double r);//写入函数
    void write_Imaginary(double i);
    void write_modulus();
    void write_arg();
};

//=============类定义结束=======================

//=============全局函数声明开始=======================

//重载pow()函数
inline Complex pow(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    double m = c2.real() * log(c1.modulus()) - c2.imag() * c1.arg();
    double n = c2.real() * c1.arg() + c2.imag() * log(c1.modulus());
    c.m_real = (abs(cos(n)) > Epslion ? exp(m) * cos(n) : 0);
    c.m_imag = (abs(sin(n)) > Epslion ? exp(m) * sin(n) : 0);
    return c;
}
inline Complex pow(const Complex& c1, const double m)
{
    Complex c2,c;
    c2.write_Complex(m, 0.0);
    c = pow(c1, c2);
    return c;
}
inline Complex pow(const double m, const Complex& c2)
{
    Complex c1,c;
    c1.write_Complex(m, 0.0);
    c = pow(c1, c2);
    return c;
}
inline Complex pow(const double m, const double n, bool judge)
{
    Complex c1, c2,c;
    c1 = (Complex)m;
    c2 = (Complex)n;
    c = pow(c1, c2);
    return c;
}

//重载+运算符
inline Complex operator+(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = c1.m_real + c2.m_real;
    c.m_imag = c1.m_imag + c2.m_imag;
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator+(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real + m;
    c.m_imag = c1.m_imag;
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator+(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = c2.m_real + m;
    c.m_imag = c2.m_imag;
    c.write_modulus();
    c.write_arg();
    return c;
}

//重载-运算符
inline Complex operator-(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = c1.m_real - c2.m_real;
    c.m_imag = c1.m_imag - c2.m_imag;
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator-(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real - m;
    c.m_imag = c1.m_imag;
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator-(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = c2.m_real - m;
    c.m_imag = c2.m_imag;
    c.write_modulus();
    c.write_arg();
    return c;
}

//重载*运算符  (a+bi) * (c+di) = (ac-bd) + (bc+ad)i
inline Complex operator*(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
    c.m_imag = c1.m_imag * c2.m_real + c1.m_real * c2.m_imag;
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator*(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real * m;
    c.m_imag = c1.m_imag * m;
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator*(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = c2.m_real * m;
    c.m_imag = c2.m_imag * m;
    c.write_modulus();
    c.write_arg();
    return c;
}

//重载/运算符  (a+bi) / (c+di) = [(ac+bd) / (c2+d2)] + [(bc-ad) / (c2+d2)]i
inline Complex operator/(const Complex& c1, const Complex& c2)
{
    Complex c(0);
    c.m_real = (c1.m_real * c2.m_real + c1.m_imag * c2.m_imag) / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.m_imag = (c1.m_imag * c2.m_real - c1.m_real * c2.m_imag) / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator/(const Complex& c1, const double m)
{
    Complex c(0);
    c.m_real = c1.m_real / m;
    c.m_imag = c1.m_imag / m;
    c.write_modulus();
    c.write_arg();
    return c;
}
inline Complex operator/(const double m, const Complex& c2)
{
    Complex c(0);
    c.m_real = m * c2.m_real / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.m_imag = -m * c2.m_imag / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.write_modulus();
    c.write_arg();
    return c;
}

//重载==运算符
inline bool operator==(const Complex& c1, const Complex& c2)
{
    if ((abs(c1.m_real - c2.m_real) < Epslion) && (abs(c1.m_imag - c2.m_imag) < Epslion))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator==(const Complex& c1, const double m)
{
    if ((abs(c1.m_modulus - m * m) < Epslion) && (abs(c1.m_imag) < Epslion))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator==(const double m, const Complex& c2)
{
    if ((abs(c2.m_modulus - m * m) < Epslion) && (abs(c2.m_imag) < Epslion))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//重载!=运算符
inline bool operator!=(const Complex& c1, const Complex& c2)
{
    if (c1 == c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator!=(const Complex& c1, const double m)
{
    if (c1 == m)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator!=(const double m, const Complex& c2)
{
    if (c2 == m)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//重载>运算符
inline bool operator>(const Complex& c1, const Complex& c2)
{
    if ((c1.m_modulus > c2.m_modulus) || ((abs(c1.m_modulus - c2.m_modulus) < Epslion) && (c1.m_real > c2.m_real)))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>(const Complex& c1, const double m)
{
    if (c1.m_modulus > m * m)
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>(const double m, const Complex& c2)
{
    if ((m * m > c2.m_modulus) || ((abs(m - c2.m_modulus) < Epslion) && (abs(c2.m_imag) > Epslion)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//重载>=运算符
inline bool operator>=(const Complex& c1, const Complex& c2)
{
    if ((c1 > c2) || (c1 == c2))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>=(const Complex& c1, const double m)
{
    if ((c1 > m) || (c1 == m))
    {
        return true;
    }
    else
    {
        return false;
    }
}
inline bool operator>=(const double m, const Complex& c2)
{
    if ((m > c2) || (m == c2))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//重载<运算符
inline bool operator<(const Complex& c1, const Complex& c2)
{
    if (c1 >= c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<(const Complex& c1, const double m)
{
    if (c1 >= m)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<(const double m, const Complex& c2)
{
    if (m >= c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//重载<=运算符
inline bool operator<=(const Complex& c1, const Complex& c2)
{
    if (c1 > c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<=(const Complex& c1, const double m)
{
    if (c1 > m)
    {
        return false;
    }
    else
    {
        return true;
    }
}
inline bool operator<=(const double m, const Complex& c2)
{
    if (m > c2)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//=============全局函数声明结束=======================