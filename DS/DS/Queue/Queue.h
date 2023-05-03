#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：Queue.h
* 文件标识：未定义
* 摘 要：STL标准模板类中的Queue的个人编写版
*
* 当前版本：1.0
* 作 者：RickJingDG
* 版本概要：本版本是基于清华大学邓俊辉教授的数据结构（C++语言版）来编写的。
* 完成日期：2023年4月18日
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

#include "../List/List.h" //以List为基类派生出的
template <typename T> class Queue : public List<T> //队列模板类
{
public: //原有接口一概沿用
	void enqueue(T const& e) { List<T>::insertAsLast(e); } //入队：尾部插入
	T dequeue() { return List<T>::remove(List<T>::first()); } //出队：首部删除
	T& front() { return List<T>::first()->data; } //队首
};

//=============类定义结束=======================

//=============函数声明开始=======================
//void Function1(); // 全局函数声明：无

//=============函数声明结束=======================

