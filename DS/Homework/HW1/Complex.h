#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：Complex.h
* 文件标识：未定义
* 摘 要：复数类，包含复数的实部、虚部、模长、辐角，和一些基本运算。
*
* 当前版本：1.1
* 版本概要：添加了辐角，补充复数与实数的基本四则运算和复数与实数的比较，针对双精度浮点数重写了“==”的判断方法，初步的规范了代码格式。
* 作 者：RickJingDG
* 完成日期：2023年3月25日
*
* 取代版本：1.0
* 版本概要：简单的搭建起了复数类的基本框架，定义了实部，虚部，模长，和一些复数间的四则运算以及复数间的比较。
* 作 者：yyhgdx（钱同学）
* 完成日期：2023年3月22日
*
*/

#include <iostream> //库文件引用和文件信息隔开一行
#include <cmath>// 引用标准库的头文件

//#include "myheader.h"// 引用非标准库的头文件

using namespace std;

//=============全局变量定义开始=======================
const double Epslion = 1e-8;//用于双精度浮点数比较大小
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
class Complex {
public:
    //构造函数
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag),m_modulus(sqrt(imag* imag + real * real)),m_arg(atan2(imag, real) / 180 * acos(-1.0))
    { }
    //运算符重载
        //以全局函数的形式重载
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
    void display();
    void write_Real(double r);//写入函数
    void write_Imaginary(double i);
    void write_modulus();
    void write_arg();
    double real() const { return m_real; }//读取函数
    double imag() const { return m_imag; }
    double modulus() const { return m_modulus; }
    double arg() const { return m_arg; }
private:
    double m_real;  //实部
    double m_imag;  //虚部
    double m_modulus;  //模长 
    double m_arg;  //辐角主值，单位度。
};

//=============类定义结束=======================

//=============全局函数声明开始=======================

//重载+运算符
inline Complex operator+(const Complex& c1, const Complex& c2)
{
    Complex c;
    c.m_real = c1.m_real + c2.m_real;
    c.m_imag = c1.m_imag + c2.m_imag;
    return c;
}
inline Complex operator+(const Complex& c1, const double m)
{
    Complex c;
    c.m_real = c1.m_real + m;
    c.m_imag = c1.m_imag;
    return c;
}
inline Complex operator+(const double m, const Complex& c2)
{
    Complex c;
    c.m_real = c2.m_real + m;
    c.m_imag = c2.m_imag;
    return c;
}

//重载-运算符
inline Complex operator-(const Complex& c1, const Complex& c2)
{
    Complex c;
    c.m_real = c1.m_real - c2.m_real;
    c.m_imag = c1.m_imag - c2.m_imag;
    return c;
}
inline Complex operator-(const Complex& c1, const double m)
{
    Complex c;
    c.m_real = c1.m_real - m;
    c.m_imag = c1.m_imag;
    return c;
}
inline Complex operator-(const double m, const Complex& c2)
{
    Complex c;
    c.m_real = c2.m_real - m;
    c.m_imag = c2.m_imag;
    return c;
}

//重载*运算符  (a+bi) * (c+di) = (ac-bd) + (bc+ad)i
inline Complex operator*(const Complex& c1, const Complex& c2)
{
    Complex c;
    c.m_real = c1.m_real * c2.m_real - c1.m_imag * c2.m_imag;
    c.m_imag = c1.m_imag * c2.m_real + c1.m_real * c2.m_imag;
    return c;
}
inline Complex operator*(const Complex& c1, const double m)
{
    Complex c;
    c.m_real = c1.m_real * m;
    c.m_imag = c1.m_imag * m;
    return c;
}
inline Complex operator*(const double m, const Complex& c2)
{
    Complex c;
    c.m_real = c2.m_real * m;
    c.m_imag = c2.m_imag * m;
    return c;
}

//重载/运算符  (a+bi) / (c+di) = [(ac+bd) / (c2+d2)] + [(bc-ad) / (c2+d2)]i
inline Complex operator/(const Complex& c1, const Complex& c2)
{
    Complex c;
    c.m_real = (c1.m_real * c2.m_real + c1.m_imag * c2.m_imag) / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.m_imag = (c1.m_imag * c2.m_real - c1.m_real * c2.m_imag) / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    return c;
}
inline Complex operator/(const Complex& c1, const double m)
{
    Complex c;
    c.m_real = c1.m_real / m;
    c.m_imag = c1.m_imag / m;
    return c;
}
inline Complex operator/(const double m, const Complex& c2)
{
    Complex c;
    c.m_real = m * c2.m_real / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
    c.m_imag = -m * c2.m_imag / (c2.m_real * c2.m_real + c2.m_imag * c2.m_imag);
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