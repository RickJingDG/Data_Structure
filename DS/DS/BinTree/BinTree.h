#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：BinTree.h
* 文件标识：未定义
* 摘 要：STL标准模板类中的二叉树的个人编写版
*
* 当前版本：1.0
* 作 者：RickJingDG
* 版本概要：本版本是基于清华大学邓俊辉教授的数据结构（C++语言版）来编写的。
* 完成日期：2023年5月2日
*
*/

//#include<iostream> //库文件引用和文件信息隔开一行
// 引用标准库的头文件


#include "BinNode.h"//引用二叉树节点结构
// 引用非标准库的头文件


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

template <typename T> class BinTree//二叉树模板类
{
protected:
    Rank _size; BinNodePosi<T> _root; //规模、根节点
    virtual Rank updateHeight(BinNodePosi<T> x); //更新节点x的高度
    void updateHeightAbove(BinNodePosi<T> x); //更新节点x及其祖先的高度
public:
    BinTree() : _size(0), _root(NULL) {} //构造函数
    ~BinTree() { if (0 < _size) remove(_root); } //析构函数
    Rank size() const { return _size; } //规模
    bool empty() const { return !_root; } //判空
    BinNodePosi<T> root() const { return _root; } //树根
    BinNodePosi<T> insertAsRoot(T const& e); //插入根节点
    BinNodePosi<T> insertAsLC(BinNodePosi<T>x, T const& e); //e作为x的左孩子（原无）插入
    BinNodePosi<T> insertAsRC(BinNodePosi<T>x, T const& e); //e作为x的右孩子（原无）插入
    BinNodePosi<T> attachAsLC(BinNodePosi<T>x, BinTree<T>*& T); //T作为x左子树接入
    BinNodePosi<T> attachAsRC(BinNodePosi<T>x, BinTree<T>*& T); //T作为x右子树接入
    Rank remove(BinNodePosi<T>x); //删除以位置x处节点为根的子树，返回该子树原先的规模
    BinTree<T>* secede(BinNodePosi<T>x); //将子树x从当前树中摘除，并将其转换为一棵独立子树
    template <typename VST> //操作器
    void travLevel(VST& visit) { if (_root) _root->travLevel(visit); } //层次遍历
    template <typename VST> //操作器
    void travPre(VST& visit) { if (_root) _root->travPre(visit); } //先序遍历
    template <typename VST> //操作器
    void travIn(VST& visit) { if (_root) _root->travIn(visit); } //中序遍历
    template <typename VST> //操作器
    void travPost(VST& visit) { if (_root) _root->travPost(visit); } //后序遍历
    bool operator<(BinTree<T> const& t) //比较器
    {
        return _root && t._root && lt(_root, t._root);
    }
    bool operator<=(BinTree<T> const& t) //比较器
    {
        return _root && t._root && !(mt(_root, t._root));
    }
    bool operator>(BinTree<T> const& t) //比较器
    {
        return _root && t._root && mt(_root, t._root);
    }
    bool operator>=(BinTree<T> const& t) //比较器
    {
        return _root && t._root && !(lt(_root, t._root));
    }
    bool operator==(BinTree<T> const& t) //判等器
    {
        return _root && t._root && (_root == t._root);
    }
    bool operator!=(BinTree<T> const& t) //判等器
    {
        return _root && t._root && (_root != t._root);
    }
}; //BinTree

#include "BinTree_fun.h"//函数实现

//=============类定义结束=======================

//=============全局函数定义开始=======================
//无
//=============全局函数定义结束=======================

