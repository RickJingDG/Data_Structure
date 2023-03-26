#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* �ļ����ƣ�Vecotor.h
* �ļ���ʶ��δ����
* ժ Ҫ��STL��׼ģ�����е�Vector�ĸ��˱�д��
*
* ��ǰ�汾��1.0
* �� �ߣ�RickJingDG
* �汾��Ҫ�����汾�ǻ����廪��ѧ�˿��Խ��ڵ����ݽṹ��C++���԰棩����д�ģ�������Щ���������ĺ�������ֻ�м򵥵Ķ��壬�����о������еĿ����ԡ�
* ������ڣ�2023��3��25��
*
*/

//#include<iostream> //���ļ����ú��ļ���Ϣ����һ��
// ���ñ�׼���ͷ�ļ�


//#include "myheader.h"// ���÷Ǳ�׼���ͷ�ļ�


//=============ȫ�ֱ������忪ʼ=======================
typedef int Rank;//�ȣ�RickJing˵����typedef�����ڼ򻯸��ӵ������Ͷ��壬���ߵ����ĸı������������ֶȣ��䱾���ǵ�Ч���
#define DEFAULT_CAPACITY 16//Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����
//=============ȫ�ֱ����������=======================

//=============�ṹ�嶨�忪ʼ=======================
/*
* �����Ľṹ�壺��
*/
//struct structType
//{
//	int intType;
//	char charType;
//};
//=============�ṹ�嶨�����=======================

//=============�ඨ�忪ʼ=======================

template <typename T>class Vector // ����ģ����
{
protected:
	Rank _size; int _capacity; T* _elem;//��ģ��������������
	void copyFrom(T const* A, Rank lo, Rank hi);//������������A[lo,hi)
	void expand();//�ռ䲻��ʱ����
	void shrink();//װ�����ӹ�Сʱ����
	bool bubble(Rank lo, Rank hi);//ɨ�轻��
	void bubbleSort(Rank lo, Rank hi);//���������㷨
	Rank max(Rank lo, Rank hi);//ѡȡ���Ԫ��
	void selectionSort(Rank lo, Rank hi);//ѡ�������㷨
	void merge(Rank lo, Rank mi, Rank hi);//�鲢�㷨
	void mergeSort(Rank lo, Rank hi);//�鲢�����㷨
	Rank partition(Rank lo, Rank hi);//��㹹���㷨
	void quickSort(Rank lo, Rank hi);//���������㷨
	void heapSort(Rank lo, Rank hi);//������
	void swap(T& a, T& b);//����
public:
	//���캯��
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)//����Ϊc����ģΪs������Ԫ�س�ʼΪv
	{
		_elem = new T[_capacity = c];//����һ���ռ�
		for (_size = 0; _size < s; _elem[_size++] = v);//��ʼ��ÿ��Ԫ��
	}//s<=c
	Vector(T const* A, Rank n)//��������帴��
	{
		copyFrom(A, 0, n);
	}
	Vector(T const* A, Rank lo, Rank hi)//��������临��
	{
		copyFrom(A, lo, hi);
	}
	Vector(Vector<T>const& V)//���������帴��
	{
		copyFrom(V._elem, 0, V.size);
	}
	Vector(Vector<T>const& V, Rank lo, Rank hi)//���������临��
	{
		copyFrom(V._elem, lo, hi);
	}
	//��������
	~Vector()//�ͷ��ڴ�ռ�
	{
		delete[]_elem;
	}

	//ֻ�����ʽӿ�
	Rank size() const { return _size; }//��ģ
	bool empty()const { return !_size; }//�п�
	int disordered()const;//�ж������Ƿ�������
	Rank find(T const& e)const { return find(e, 0, _size); }//���������������
	Rank find(T const& e, Rank lo, Rank hi)const;//���������������
	Rank search(T const& e)const//���������������
	{
		return(0 >= _size) ? -1 : search(e, 0, _size);//�ж�����������񣬴��ھ���
	}
	Rank search(T const& e, Rank lo, Rank hi)const;//���������������

	//��д���ʽӿ�
	T& operator[] (Rank r);//�����±������������������������ʽ���ø�Ԫ��
	const T& operator[] (Rank r) const; //����������ֵ�����ذ汾
	Vector<T>& operator= (Vector<T> const&);//���ظ�ֵ���������Ա�ֱ�ӿ�¡����
	T remove(Rank r);//ɾ����Ϊr��Ԫ��
	int remove(Rank lo, Rank hi);//ɾ����������[lo,hi)֮�ڵ�Ԫ��
	Rank insert(Rank r, T const& e);//����Ԫ��
	Rank insert(T const& e)//Ĭ����ΪĩԪ�ز���
	{
		return insert(_size, e);
	}
	void sort(Rank lo, Rank hi, int Case);//��[lo,hi)����
	void sort()//��������
	{
		sort(0, _size);
	}
	void unsort(Rank lo, Rank hi);//��[lo,hi)����
	void unsort()//��������
	{
		unsort(0, _size);
	}
	int deduplicate();//����ȥ��
	int uniquify();//����ȥ��
	//����
	void traverse(void(*visit)(T&));//������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
	template <typename VST> void traverse(VST&);//������ʹ�ú������󣬿�ȫ�����޸ģ�
};//Vector

#include "Vextor_fun.h"//����ʵ��

//=============�ඨ�����=======================

//=============����������ʼ=======================
//void Function1(); // ȫ�ֺ�����������

//=============������������=======================
