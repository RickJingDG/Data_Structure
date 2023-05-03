#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：计算器.h
* 文件标识：未定义
* 摘 要：计算器相关头文件
*
* 当前版本：1.0
* 版本概要：主要为栈方法建立了运算符比较表
* 作 者：RickJingDG
* 完成日期：2023年4月17日
*
*/

#include <iostream> //库文件引用和文件信息隔开一行
#include <cmath>// 引用标准库的头文件

#include"../../Stack/Stack.h"// 引用非标准库的头文件
#include "../HW1/Complex.h"
using namespace std;

//=============全局变量定义开始=======================
constexpr auto N_OPTR = 9; //运算符总数;
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator; //运算符集合
//加、减、乘、除、乘方、阶乘、左括号、右括号、起始符与终止符

const char pri[N_OPTR][N_OPTR] = 
{ //运算符优先等级 [栈顶] [当前]
	/*              |-------------------- 当 前 运 算 符 --------------------| */
	/*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};
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
//无
//=============类定义结束=======================

//=============全局函数声明开始=======================

char* removeSpace(char* s);
long long facI(int n);
double calcu(double a, char op, double b);
double calcu(char op, double b);
Complex calcu(Complex a, char op, Complex b);//复数类计算器
Complex calcu(char op, Complex b);
void readNumber(char*&, Stack<double>&);
Operator optr2rank(char);
char priority(char, char);
//double evaluate(char* expr);
Complex evaluate(char* expr);

//=============全局函数声明结束=======================