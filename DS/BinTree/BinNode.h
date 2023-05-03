#pragma once
#define DSA_STACK_VECTOR//ʹ������������ջ

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* �ļ����ƣ�BinNode.h
* �ļ���ʶ��δ����
* ժ Ҫ��STL��׼ģ�����е�BinNode�ĸ��˱�д��
*
* ��ǰ�汾��1.0
* �� �ߣ�RickJingDG
* �汾��Ҫ�����汾�ǻ����廪��ѧ�˿��Խ��ڵ����ݽṹ��C++���԰棩����д��
* ������ڣ�2023��5��2��
*
*/

//#include<iostream> //���ļ����ú��ļ���Ϣ����һ��
// ���ñ�׼���ͷ�ļ�

#include "..\Queue\Queue.h" //�������
#include "..\Stack\Stack.h" //����ջ
// ���÷Ǳ�׼���ͷ�ļ�

//=============ȫ�ֱ������忪ʼ=======================
#if defined( DSA_REDBLACK ) //�ں������
#define stature( p ) ( ( p ) ? ( p )->height : 0 ) //�ⲿ�ڵ㣨�ڣ��߶�Ϊ0�����ϵ���
#else //����BST��
#define stature( p ) ( (int)( ( p ) ? ( p )->height : -1 ) ) //�ⲿ�ڵ�߶�Ϊ-1�����ϵ���
#endif

typedef enum { RB_RED, RB_BLACK } RBColor; //�ڵ���ɫ
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //�ڵ�λ��

//=============ȫ�ֱ����������=======================

//=============�ṹ�嶨�忪ʼ=======================

template <typename T> struct BinNode 
{ //�������ڵ�ģ��ṹ
	// ��Ա��Ϊ���������ͳһ����
	T data; //��ֵ
	BinNodePosi<T> parent, lc, rc; //���ڵ㼰���Һ���
	Rank height; //�߶ȣ�ͨ�ã�
	Rank npl; //Null Path Length����ʽ�ѣ�Ҳ��ֱ����height���棩
	RBColor color; //��ɫ���������
	// ���캯��
	BinNode() : 
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL,
		BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED):
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
	// �����ӿ�
	Rank size(); //ͳ�Ƶ�ǰ�ڵ����������༴����Ϊ���������Ĺ�ģ
	BinNodePosi<T> insertAsLC(T const&); //��Ϊ��ǰ�ڵ�����Ӳ����½ڵ�
	BinNodePosi<T> insertAsRC(T const&); //��Ϊ��ǰ�ڵ���Һ��Ӳ����½ڵ�
	BinNodePosi<T> succ(); //ȡ��ǰ�ڵ��ֱ�Ӻ��
	template <typename VST> void travLevel(VST&); //������α���
	template <typename VST> void travPre(VST&); //�����������
	template <typename VST> void travIn(VST&); //�����������
	template <typename VST> void travPost(VST&); //�����������
	// �Ƚ������е���
	bool operator< (BinNode const& bn) { return data < bn.data; } //С��
	bool operator<= (BinNode const& bn) { return data <= bn.data; } //С�ڵ���
	bool operator> (BinNode const& bn) { return data > bn.data; } //����
	bool operator>= (BinNode const& bn) { return data >= bn.data; } //���ڵ���
	bool operator== (BinNode const& bn) { return data == bn.data; } //����
	bool operator!= (BinNode const& bn) { return data != bn.data; } //������
};

#include "BinNode_fun.h"//����ʵ��

//=============�ṹ�嶨�����=======================

//=============�ඨ�忪ʼ=======================
//��
//=============�ඨ�����=======================

//=============ȫ�ֺ������忪ʼ=======================

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //����ӵ��һ������
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //ͬʱӵ����������
#define IsLeaf(x) ( ! HasChild(x) )
#define sibling( p ) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) /*�ֵ�*/
#define uncle( x ) ( sibling( (x)->parent ) ) /*����*/
#define FromParentTo( x ) /*���Ը��׵�����*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

//=============ȫ�ֺ����������=======================
