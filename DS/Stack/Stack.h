#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* �ļ����ƣ�Stack.h
* �ļ���ʶ��δ����
* ժ Ҫ��STL��׼ģ�����е�Stack�ĸ��˱�д��
*
* ��ǰ�汾��1.0
* �� �ߣ�RickJingDG
* �汾��Ҫ�����汾�ǻ����廪��ѧ�˿��Խ��ڵ����ݽṹ��C++���԰棩����д�ġ�
* ������ڣ�2023��4��16��
*
*/

//#include<iostream> //���ļ����ú��ļ���Ϣ����һ��
// ���ñ�׼���ͷ�ļ�


//#include "myheader.h"// ���÷Ǳ�׼���ͷ�ļ�


//=============ȫ�ֱ������忪ʼ=======================
//��
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

#if defined(DSA_STACK_VECTOR)//��������������ջ
#include "../Vector/Vector.h" //������Ϊ���࣬������ջģ����
template <typename T> class Stack : public Vector<T>//����������/ĩ����Ϊջ��/��
{
public: //ԭ�нӿ�һ������
	void push(T const& e) { Vector<T>::insert(e); } //��ջ����Ч�ڽ���Ԫ����Ϊ������ĩԪ�ز���
	T pop() { return Vector<T>::remove(Vector<T>::size() - 1); } //��ջ����Ч��ɾ��������ĩԪ��
	T& top() { return (*this)[Vector<T>::size() - 1]; } //ȡ����ֱ�ӷ���������ĩԪ��
};
#elif defined(DSA_STACK_LIST)//���б�������ջ
#include "../List/List.h" //���б�Ϊ���࣬������ջģ����
template <typename T> class Stack : public List<T>//���б����/ĩ����Ϊջ��/��
{ 
public: //ԭ�нӿ�һ������
	void push(T const& e) { List<T>::insertAsLast(e); } //��ջ����Ч�ڽ���Ԫ����Ϊ�б��ĩԪ�ز���
	T pop() { return List<T>::remove(List<T>::last()); } //��ջ����Ч��ɾ���б��ĩԪ��
	T& top() { return List<T>::last()->data; } //ȡ����ֱ�ӷ����б��ĩԪ��
}; 
#else
#endif

//=============�ඨ�����=======================

//=============����������ʼ=======================
//void Function1(); // ȫ�ֺ�����������

//=============������������=======================

