#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：Stack.h
* 文件标识：未定义
* 摘 要：STL标准模板类中的Stack的个人编写版
*
* 当前版本：1.0
* 作 者：RickJingDG
* 版本概要：本版本是基于清华大学邓俊辉教授的数据结构（C++语言版）来编写的。
* 完成日期：2023年4月16日
*
*/

//#include<iostream> //库文件引用和文件信息隔开一行
// 引用标准库的头文件


//#include "myheader.h"// 引用非标准库的头文件


//=============全局变量定义开始=======================
//无
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

#if defined(DSA_STACK_VECTOR)//由向量派生出的栈
#include "../Vector/Vector.h" //以向量为基类，派生出栈模板类
template <typename T> class Stack : public Vector<T>//将向量的首/末端作为栈底/顶
{
public: //原有接口一概沿用
	void push(T const& e) { Vector<T>::insert(e); } //入栈：等效于将新元素作为向量的末元素插入
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); } //出栈：等效于删除向量的末元素
	T& top() { return (*this)[Vector<T>::size() - 1]; } //取顶：直接返回向量的末元素
};
#elif defined(DSA_STACK_LIST)//由列表派生的栈
#include "../List/List.h" //以列表为基类，派生出栈模板类
template <typename T> class Stack : public List<T>//将列表的首/末端作为栈底/顶
{ 
public: //原有接口一概沿用
	void push(T const& e) { List<T>::insertAsLast(e); } //入栈：等效于将新元素作为列表的末元素插入
	T pop() { return List<T>::remove(List<T>::last()); } //出栈：等效于删除列表的末元素
	T& top() { return List<T>::last()->data; } //取顶：直接返回列表的末元素
}; 
#else
#endif

//=============类定义结束=======================

//=============函数声明开始=======================
//void Function1(); // 全局函数声明：无

//=============函数声明结束=======================

