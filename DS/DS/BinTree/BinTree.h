#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* �ļ����ƣ�BinTree.h
* �ļ���ʶ��δ����
* ժ Ҫ��STL��׼ģ�����еĶ������ĸ��˱�д��
*
* ��ǰ�汾��1.0
* �� �ߣ�RickJingDG
* �汾��Ҫ�����汾�ǻ����廪��ѧ�˿��Խ��ڵ����ݽṹ��C++���԰棩����д�ġ�
* ������ڣ�2023��5��2��
*
*/

//#include<iostream> //���ļ����ú��ļ���Ϣ����һ��
// ���ñ�׼���ͷ�ļ�


#include "BinNode.h"//���ö������ڵ�ṹ
// ���÷Ǳ�׼���ͷ�ļ�


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

template <typename T> class BinTree//������ģ����
{
protected:
    Rank _size; BinNodePosi<T> _root; //��ģ�����ڵ�
    virtual Rank updateHeight(BinNodePosi<T> x); //���½ڵ�x�ĸ߶�
    void updateHeightAbove(BinNodePosi<T> x); //���½ڵ�x�������ȵĸ߶�
public:
    BinTree() : _size(0), _root(NULL) {} //���캯��
    ~BinTree() { if (0 < _size) remove(_root); } //��������
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_root; } //�п�
    BinNodePosi<T> root() const { return _root; } //����
    BinNodePosi<T> insertAsRoot(T const& e); //������ڵ�
    BinNodePosi<T> insertAsLC(BinNodePosi<T>x, T const& e); //e��Ϊx�����ӣ�ԭ�ޣ�����
    BinNodePosi<T> insertAsRC(BinNodePosi<T>x, T const& e); //e��Ϊx���Һ��ӣ�ԭ�ޣ�����
    BinNodePosi<T> attachAsLC(BinNodePosi<T>x, BinTree<T>*& T); //T��Ϊx����������
    BinNodePosi<T> attachAsRC(BinNodePosi<T>x, BinTree<T>*& T); //T��Ϊx����������
    Rank remove(BinNodePosi<T>x); //ɾ����λ��x���ڵ�Ϊ�������������ظ�����ԭ�ȵĹ�ģ
    BinTree<T>* secede(BinNodePosi<T>x); //������x�ӵ�ǰ����ժ����������ת��Ϊһ�ö�������
    template <typename VST> //������
    void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //��α���
    template <typename VST> //������
    void travPre(VST& visit) { if (_root) _root->travPre(visit); } //�������
    template <typename VST> //������
    void travIn(VST& visit) { if (_root) _root->travIn(visit); } //�������
    template <typename VST> //������
    void travPost(VST& visit) { if (_root) _root->travPost(visit); } //�������
    bool operator<(BinTree<T> const& t) //�Ƚ���
    {
        return _root && t._root && lt(_root, t._root);
    }
    bool operator<=(BinTree<T> const& t) //�Ƚ���
    {
        return _root && t._root && !(mt(_root, t._root));
    }
    bool operator>(BinTree<T> const& t) //�Ƚ���
    {
        return _root && t._root && mt(_root, t._root);
    }
    bool operator>=(BinTree<T> const& t) //�Ƚ���
    {
        return _root && t._root && !(lt(_root, t._root));
    }
    bool operator==(BinTree<T> const& t) //�е���
    {
        return _root && t._root && (_root == t._root);
    }
    bool operator!=(BinTree<T> const& t) //�е���
    {
        return _root && t._root && (_root != t._root);
    }
}; //BinTree

#include "BinTree_fun.h"//����ʵ��

//=============�ඨ�����=======================

//=============ȫ�ֺ������忪ʼ=======================
//��
//=============ȫ�ֺ����������=======================

