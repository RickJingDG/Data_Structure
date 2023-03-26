#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：Vecotor.h
* 文件标识：未定义
* 摘 要：STL标准模板类中的Vector的个人编写版
*
* 当前版本：1.0
* 作 者：RickJingDG
* 版本概要：本版本是基于清华大学邓俊辉教授的数据结构（C++语言版）来编写的，其中有些许声明过的函数仅仅只有简单的定义，不具有具体运行的可行性。
* 完成日期：2023年3月25日
*
*/

#include<iostream> //库文件引用和文件信息隔开一行
// 引用标准库的头文件


//#include "myheader.h"// 引用非标准库的头文件


//=============全局变量定义开始=======================
typedef int Rank;//秩；RickJing说明：typedef常用于简化复杂的声明和定义，或者单纯的改变名称增加区分度，其本质是等效替代
#define DEFAULT_CAPACITY 16//默认的初始容量（实际应用中可设置为更大）
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

template <typename T>class Vector // 向量模板类
{
protected:
	Rank _size; int _capacity; T* _elem;//规模、容量、数据区
	void copyFrom(T const* A, Rank lo, Rank hi);//复制数组区间A[lo,hi)
	void expand();//空间不足时扩容
	void shrink();//装填因子过小时缩容
	bool bubble(Rank lo, Rank hi);//扫描交换
	void bubbleSort(Rank lo, Rank hi);//起泡排序算法
	Rank max(Rank lo, Rank hi);//选取最大元素
	void selectionSort(Rank lo, Rank hi);//选择排序算法
	void merge(Rank lo, Rank mi, Rank hi);//归并算法
	void mergeSort(Rank lo, Rank hi);//归并排序算法
	Rank partition(Rank lo, Rank hi);//轴点构造算法
	void quickSort(Rank lo, Rank hi);//快速排序算法
	void heapSort(Rank lo, Rank hi);//堆排序
	void swap(T& a, T& b);//交换
public:
	//构造函数
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//容量为c、规模为s、所有元素初始为v
	{
		_elem = new T[_capacity = c];//分配一个空间
		for (_size = 0; _size < s; _elem[_size++] = v);//初始化每个元素
	}//s<=c
	Vector(T const* A, Rank n)//数组的整体复制
	{
		copyFrom(A, 0, n);
	}
	Vector(T const* A, Rank lo, Rank hi)//数组的区间复制
	{
		copyFrom(A, lo, hi);
	}
	Vector(Vector<T>const& V)//向量的整体复制
	{
		copyFrom(V._elem, 0, V.size);
	}
	Vector(Vector<T>const& V, Rank lo, Rank hi)//向量的区间复制
	{
		copyFrom(V._elem, lo, hi);
	}
	//析构函数
	~Vector()//释放内存空间
	{
		delete[]_elem;
	}

	//只读访问接口
	Rank size() const { return _size; }//规模
	bool empty()const { return !_size; }//判空
	int disordered()const;//判断向量是否已排序
	Rank find(T const& e)const { return find(e, 0, _size); }//无序向量整体查找
	Rank find(T const& e, Rank lo, Rank hi)const;//无序向量区间查找
	Rank search(T const& e)const//有序向量整体查找
	{
		return(0 >= _size) ? -1 : search(e, 0, _size);//判断向量存在与否，存在就找
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//有序向量区间查找

	//可写访问接口
	T& operator[] (Rank r);//重载下标操作符，可以类似于数组形式引用各元素
	const T& operator[] (Rank r) const; //仅限于做右值的重载版本
	Vector<T>& operator= (Vector<T> const&);//重载赋值操作符，以便直接克隆向量
	T remove(Rank r);//删除秩为r的元素
	int remove(Rank lo, Rank hi);//删除秩在区间[lo,hi)之内的元素
	Rank insert(Rank r, T const& e);//插入元素
	Rank insert(T const& e)//默认作为末元素插入
	{
		return insert(_size, e);
	}
	void sort(Rank lo, Rank hi, int Case);//对[lo,hi)排序
	void sort()//整体排序
	{
		sort(0, _size);
	}
	void unsort(Rank lo, Rank hi);//对[lo,hi)置乱
	void unsort()//整体置乱
	{
		unsort(0, _size);
	}
	int deduplicate();//无序去重
	int uniquify();//有序去重
	//遍历
	void traverse(void(*visit)(T&));//遍历（使用函数指针，只读或局部性修改）
	template <typename VST> void traverse(VST&);//遍历（使用函数对象，可全局性修改）
};//Vector

#include "Vextor_fun.h"//函数实现

//=============类定义结束=======================

//=============函数声明开始=======================
//void Function1(); // 全局函数声明：无

//=============函数声明结束=======================

