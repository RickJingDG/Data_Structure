#pragma once
#include "BinNode.h"//����ģ����
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))

template <typename T> Rank BinTree<T>::updateHeight(BinNodePosi<T> x) //���½ڵ�x�߶�
{
	return x->height = 1 + max(stature(x->lc), stature(x->rc));//���������������
} 

template <typename T> void BinTree<T>::updateHeightAbove(BinNodePosi<T> x) //���¸߶�
{
	while (x) { updateHeight(x); x = x->parent; }//��x�����������������ȡ����Ż�
} 

template <typename T> BinNodePosi<T> BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1; return _root = new BinNode<T>(e);//��e�������ڵ����յĶ�����
} 

template <typename T> BinNodePosi<T> BinTree<T>::insertAsLC(BinNodePosi<T>x, T const& e)
{
	_size++; x->insertAsLC(e); updateHeightAbove(x); return x->lc;// e����Ϊx������
} 

template <typename T> BinNodePosi<T> BinTree<T>::insertAsRC(BinNodePosi<T>x, T const& e)
{
	_size++; x->insertAsRC(e); updateHeightAbove(x); return x->rc;// e����Ϊx���Һ���
} 

template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi<T> BinTree<T>::attachAsLC(BinNodePosi<T>x, BinTree<T>*& S)  // x->lc == NULL
{
	if (x->lc = S->_root) x->lc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //��S�����ڵ�x�������������������S�����ÿ�
BinNodePosi<T> BinTree<T>::attachAsRC(BinNodePosi<T>x, BinTree<T>*& S)// x->rc == NULL
{
	if (x->rc = S->_root) x->rc->parent = x; //����
	_size += S->_size; updateHeightAbove(x); //����ȫ����ģ��x�������ȵĸ߶�
	S->_root = NULL; S->_size = 0; release(S); S = NULL; return x; //�ͷ�ԭ�������ؽ���λ��
}

template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
Rank BinTree<T>::remove(BinNodePosi<T> x)// assert: xΪ�������еĺϷ�λ��
{ 
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //�������ȸ߶�
	Rank n = removeAt(x); _size -= n; return n; //ɾ������x�����¹�ģ������ɾ���ڵ�����
}
template <typename T> //ɾ����������λ��x���Ľڵ㼰���������ر�ɾ���ڵ����ֵ
static Rank removeAt(BinNodePosi<T> x) // assert: xΪ�������еĺϷ�λ��
{ 
	if (!x) return 0; //�ݹ��������
	Rank n = 1 + removeAt(x->lc) + removeAt(x->rc); //�ݹ��ͷ���������
	release(x->data); release(x); return n; //�ͷű�ժ���ڵ㣬������ɾ���ڵ�����
} // release()�����ͷŸ��ӽṹ�����㷨��ֱ�ӹ�ϵ������ʵ������

template <typename T> struct Cleaner
{
	static void clean(T x) {} //�൱�ڵݹ��
};

template <typename T> struct Cleaner<T*>
{
	static void clean(T* x)
	{
		if (x) { delete x; } //������а���ָ�룬�ݹ��ͷ�
	}
};

template <typename T> void release(T x) { Cleaner<T>::clean(x); }

template <typename T> //���������������㷨��������x�ӵ�ǰ����ժ���������װΪһ�ö�����������
BinTree<T>* BinTree<T>::secede(BinNodePosi<T> x)// assert: xΪ�������еĺϷ�λ��
{ 
	FromParentTo(*x) = NULL; //�ж����Ը��ڵ��ָ��
	updateHeightAbove(x->parent); //����ԭ�����������ȵĸ߶�
	BinTree<T>* S = new BinTree<T>; S->_root = x; x->parent = NULL; //������xΪ��
	S->_size = x->size(); _size -= S->_size; return S; //���¹�ģ�����ط������������
}

template <typename T> static bool lt(T* a, T* b) { return lt(*a, *b); } // less than
template <typename T> static bool lt(T& a, T& b) { return a < b; } // less than
template <typename T> static bool mt(T* a, T* b) { return mt(*a, *b); } // more than
template <typename T> static bool mt(T& a, T& b) { return a > b; } // more than
template <typename T> static bool eq(T* a, T* b) { return eq(*a, *b); } // equal
template <typename T> static bool eq(T& a, T& b) { return a == b; } // equal
