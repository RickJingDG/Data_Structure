#pragma once
#define DSA_STACK_VECTOR//使用向量派生的栈

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：BinNode.h
* 文件标识：未定义
* 摘 要：STL标准模板类中的BinNode的个人编写版
*
* 当前版本：1.0
* 作 者：RickJingDG
* 版本概要：本版本是基于清华大学邓俊辉教授的数据结构（C++语言版）来编写。
* 完成日期：2023年5月2日
*
*/

//#include<iostream> //库文件引用和文件信息隔开一行
// 引用标准库的头文件

#include "..\Queue\Queue.h" //引入队列
#include "..\Stack\Stack.h" //引入栈
// 引用非标准库的头文件

//=============全局变量定义开始=======================
#if defined( DSA_REDBLACK ) //在红黑树中
#define stature( p ) ( ( p ) ? ( p )->height : 0 ) //外部节点（黑）高度为0，以上递推
#else //其余BST中
#define stature( p ) ( (int)( ( p ) ? ( p )->height : -1 ) ) //外部节点高度为-1，以上递推
#endif

typedef enum { RB_RED, RB_BLACK } RBColor; //节点颜色
template <typename T> struct BinNode;
template <typename T> using BinNodePosi = BinNode<T>*; //节点位置

//=============全局变量定义结束=======================

//=============结构体定义开始=======================

template <typename T> struct BinNode 
{ //二叉树节点模板结构
	// 成员，为简化描述起见统一开放
	T data; //数值
	BinNodePosi<T> parent, lc, rc; //父节点及左、右孩子
	Rank height; //高度（通用）
	Rank npl; //Null Path Length（左式堆，也可直接用height代替）
	RBColor color; //颜色（红黑树）
	// 构造函数
	BinNode() : 
		parent(NULL), lc(NULL), rc(NULL), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi<T> p = NULL, BinNodePosi<T> lc = NULL,
		BinNodePosi<T> rc = NULL, int h = 0, int l = 1, RBColor c = RB_RED):
		data(e), parent(p), lc(lc), rc(rc), height(h), npl(l), color(c) {}
	// 操作接口
	Rank size(); //统计当前节点后代总数，亦即以其为根的子树的规模
	BinNodePosi<T> insertAsLC(T const&); //作为当前节点的左孩子插入新节点
	BinNodePosi<T> insertAsRC(T const&); //作为当前节点的右孩子插入新节点
	BinNodePosi<T> succ(); //取当前节点的直接后继
	template <typename VST> void travLevel(VST&); //子树层次遍历
	template <typename VST> void travPre(VST&); //子树先序遍历
	template <typename VST> void travIn(VST&); //子树中序遍历
	template <typename VST> void travPost(VST&); //子树后序遍历
	// 比较器、判等器
	bool operator< (BinNode const& bn) { return data < bn.data; } //小于
	bool operator<= (BinNode const& bn) { return data <= bn.data; } //小于等于
	bool operator> (BinNode const& bn) { return data > bn.data; } //大于
	bool operator>= (BinNode const& bn) { return data >= bn.data; } //大于等于
	bool operator== (BinNode const& bn) { return data == bn.data; } //等于
	bool operator!= (BinNode const& bn) { return data != bn.data; } //不等于
};

#include "BinNode_fun.h"//函数实现

//=============结构体定义结束=======================

//=============类定义开始=======================
//无
//=============类定义结束=======================

//=============全局函数定义开始=======================

#define IsRoot(x) ( ! ( (x).parent ) )
#define IsLChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->lc ) )
#define IsRChild(x) ( ! IsRoot(x) && ( & (x) == (x).parent->rc ) )
#define HasParent(x) ( ! IsRoot(x) )
#define HasLChild(x) ( (x).lc )
#define HasRChild(x) ( (x).rc )
#define HasChild(x) ( HasLChild(x) || HasRChild(x) ) //至少拥有一个孩子
#define HasBothChild(x) ( HasLChild(x) && HasRChild(x) ) //同时拥有两个孩子
#define IsLeaf(x) ( ! HasChild(x) )
#define sibling( p ) ( IsLChild( * (p) ) ? (p)->parent->rc : (p)->parent->lc ) /*兄弟*/
#define uncle( x ) ( sibling( (x)->parent ) ) /*叔叔*/
#define FromParentTo( x ) /*来自父亲的引用*/ \
   ( IsRoot(x) ? _root : ( IsLChild(x) ? (x).parent->lc : (x).parent->rc ) )

//=============全局函数定义结束=======================
