#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：Vecotor.h
* 文件标识：未定义
* 摘 要：STL标准模板类中的Vector的个人编写版
*
* 当前版本：1.1
* 作 者：RickJingDG
* 版本概要：本版本补充了完善了一些排序的内容。
* 完成日期：2023年5月18日
*
* 取代版本：1.0
* 作 者：RickJingDG
* 版本概要：本版本是基于清华大学邓俊辉教授的数据结构（C++语言版）来编写的，其中有些许声明过的函数仅仅只有简单的定义，不具有具体运行的可行性。
* 完成日期：2023年3月25日
*
*/

//#include<iostream> //库文件引用和文件信息隔开一行
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
	void heapSort(Rank lo, Rank hi);//堆排序算法
	void shellSort(Rank lo, Rank hi); //希尔排序算法
	void insertionSort(Rank lo, Rank hi);//插入排序算法（很慢）
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
		copyFrom(V._elem, 0, V._size);
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
		return(0 >= _size) ? -1 : search(_elem, e, 0, _size);//判断向量存在与否，存在就找
	}
	Rank search(T* S, T const& e, Rank lo, Rank hi)const;//有序向量区间查找

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

//=============类定义结束=======================

//=============函数声明开始=======================

template <typename T>
inline void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

//堆相关函数
template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } // less than
template <typename T> static bool lt(T& a, T& b) { return a < b; } // less than
#define  Parent(i)         ( ( ( i ) - 1 ) >> 1 ) //PQ[i]的父节点（floor((i-1)/2)，i无论正负）
#define  LChild(i)         ( 1 + ( ( i ) << 1 ) ) //PQ[i]的左孩子
#define  RChild(i)         ( ( 1 + ( i ) ) << 1 ) //PQ[i]的右孩子
#define  InHeap(n, i)      ( ( ( -1 ) != ( i ) ) && ( ( i ) < ( n ) ) ) //判断PQ[i]是否合法
#define  LChildValid(n, i) InHeap( n, LChild( i ) ) //判断PQ[i]是否有一个（左）孩子
#define  RChildValid(n, i) InHeap( n, RChild( i ) ) //判断PQ[i]是否有两个孩子
#define  Bigger(PQ, i, j)  ( lt( PQ[i], PQ[j] ) ? j : i ) //取大者（等时前者优先）
#define  ProperParent(PQ, n, i) /*父子（至多）三者中的大者*/ \
            ( RChildValid(n, i) ? Bigger( PQ, Bigger( PQ, i, LChild(i) ), RChild(i) ) : \
            ( LChildValid(n, i) ? Bigger( PQ, i, LChild(i) ) : i \
            ) \
            ) //相等时父节点优先，如此可避免不必要的交换


//对向量前n个词条中的第i个实施下滤，i < n
template <typename T> Rank percolateDown(T* A, Rank n, Rank i)
{
	Rank j; // i及其（至多两个）孩子中，堪为父者
	while (i != (j = ProperParent(A, n, i))) //只要i非j，则
	{
		swap(A[i], A[j]), i = j; //二者换位，并继续考查下降后的i
	}
	return i; //返回下滤抵达的位置（亦i亦j）
}

template <typename T> void heapify(T* A, const Rank n) //Floyd建堆算法，O(n)时间
{
	for (Rank i = n / 2 - 1; -1 != i; i--) //自底而上，依次
	{
		percolateDown(A, n, i); //经下滤合并子堆
	}
}

//=============函数声明结束=======================

#include "Vextor_fun.h"//函数实现
