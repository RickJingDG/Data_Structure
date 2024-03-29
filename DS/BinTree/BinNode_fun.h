#pragma once
#include "BinNode.h"//引用模板类
template <typename T> Rank BinNode<T>::size() //统计当前节点后代总数，即以其为根的子树规模
{
	Rank s = 1; //计入本身
	if (lc) s += lc->size(); //递归计入左子树规模
	if (rc) s += rc->size(); //递归计入右子树规模
	return s;
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this); //将e作为当前节点的左孩子插入二叉树
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this); //将e作为当前节点的右孩子插入二叉树
}

template <typename T> BinNodePosi<T> BinNode<T>::succ() //定位节点v的直接后继
{ 
	BinNodePosi<T> s = this; //记录后继的临时变量
	if (rc)//若有右孩子，则直接后继必在右子树中
	{ //具体地就是
		s = rc; //右子树中
		while (HasLChild(*s)) s = s->lc; //最靠左（最小）的节点
	}
	else //否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”
	{ //具体地就是
		while (IsRChild(*s)) s = s->parent; //逆向地沿右向分支，不断朝左上方移动
		s = s->parent; //最后再朝右上方移动一步，即抵达直接后继（如果存在）
	}
	return s;
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode <T>::travLevel(VST& visit) //二叉树层次遍历算法
{ 
	Queue<BinNodePosi<T>> Q; Q.enqueue(this); //引入辅助队列，根节点入队
	while (!Q.empty()) //在队列再次变空之前，反复迭代
	{
		BinNodePosi<T> x = Q.dequeue(); visit(x->data); //取出队首节点并访问之
		if (HasLChild(*x)) Q.enqueue(x->lc); //左孩子入队
		if (HasRChild(*x)) Q.enqueue(x->rc); //右孩子入队
	}
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode <T>::travPre(VST& visit) //二叉树先序遍历算法统一入口
{
	switch (2) //此处只选择迭代版2，预留迭代版1和递归版，以便未来补充
	{ 
	case 1: travPre_I1(this, visit); break; //迭代版#1
	case 2: travPre_I2(this, visit); break; //迭代版#2
	default: travPre_R(this, visit); break; //递归版
	}
}

//从当前节点出发，沿左分支不断深入，直至没有左分支的节点；沿途节点遇到后立即访问
template <typename T, typename VST> //元素类型、操作器
static void visitAlongVine(BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>>& S) 
{
	while (x) 
	{
		visit(x->data); //访问当前节点
		S.push(x->rc); //右孩子入栈暂存（可优化：通过判断，避免空的右孩子入栈）
		x = x->lc; //沿左分支深入一层
	}
}

template <typename T, typename VST> //元素类型、操作器
void travPre_I2(BinNodePosi<T> x, VST& visit)//二叉树先序遍历算法（迭代版#2）
{ 
	Stack<BinNodePosi<T>> S; //辅助栈
	while (true) 
	{
		visitAlongVine(x, visit, S); //从当前节点出发，逐批访问
		if (S.empty()) break; //直到栈空
		x = S.pop(); //弹出下一批的起点
	}
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travIn(VST& visit) //二叉树中序遍历算法统一入口
{ 
	switch (rand() % 3)  //此处三种迭代版本随机选择
	{
	case 1: travIn_I1(this, visit); break; //迭代版#1
	case 2: travIn_I2(this, visit); break; //迭代版#2
	case 3: travIn_I3(this, visit); break; //迭代版#3
	default: travIn_R(this, visit); break; //递归版
	}
}

template <typename T> //从当前节点出发，沿左分支不断深入，直至没有左分支的节点
static void goAlongVine(BinNodePosi<T> x, Stack<BinNodePosi<T>>& S) 
{
	while (x) { S.push(x); x = x->lc; } //当前节点入栈后随即向左侧分支深入，迭代直到无左孩子
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I1(BinNodePosi<T> x, VST& visit) //二叉树中序遍历算法（迭代版#1）
{ 
	Stack<BinNodePosi<T>> S; //辅助栈
	while (true)
	{
		goAlongVine(x, S); //从当前节点出发，逐批入栈
		if (S.empty()) break; //直至所有节点处理完毕
		x = S.pop(); visit(x->data); //弹出栈顶节点并访问之
		x = x->rc; //转向右子树
	}
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I2(BinNodePosi<T> x, VST& visit) //二叉树中序遍历算法（迭代版#2）
{ 
	Stack<BinNodePosi<T>> S; //辅助栈
	while (true)
	{
		if (x)
		{
			S.push(x); //根节点进栈
			x = x->lc; //深入遍历左子树
		}
		else if (!S.empty())
		{
			x = S.pop(); //尚未访问的最低祖先节点退栈
			visit(x->data); //访问该祖先节点
			x = x->rc; //遍历祖先的右子树
		}
		else
			break; //遍历完成
	}
}

template <typename T, typename VST> //元素类型、操作器
void travIn_I3(BinNodePosi<T> x, VST& visit)//二叉树中序遍历算法（迭代版#3，无需辅助栈）
{ 
	bool backtrack = false; //前一步是否刚从左子树回溯——省去栈，仅O(1)辅助空间
	while (true)
	{
		if (!backtrack && HasLChild(*x)) //若有左子树且不是刚刚回溯，则
		{
			x = x->lc; //深入遍历左子树
		}
		else //否则——无左子树或刚刚回溯（相当于无左子树）
		{
			visit(x->data); //访问该节点
			if (HasRChild(*x)) //若其右子树非空，则
			{
				x = x->rc; //深入右子树继续遍历
				backtrack = false; //并关闭回溯标志
			}
			else //若右子树空，则
			{
				if (!(x = x->succ())) break; //回溯（含抵达末节点时的退出返回）
				backtrack = true; //并设置回溯标志
			}
		}
	}
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode <T>::travPost(VST& visit)//二叉树后序遍历算法统一入口
{ 
	switch (1)  //此处选择迭代版，并预留递归版
	{
	case 1: travPost_I(this, visit); break; //迭代版
	default: travPost_R(this, visit); break; //递归版
	}
}

template <typename T> //在以S栈顶节点为根的子树中，找到最高左侧可见叶节点
static void gotoLeftmostLeaf(Stack<BinNodePosi<T>>& S) //沿途所遇节点依次入栈
{
	while (BinNodePosi<T> x = S.top()) //自顶而下，反复检查当前节点（即栈顶）
	{
		if (HasLChild(*x)) //尽可能向左
		{
			if (HasRChild(*x)) S.push(x->rc); //若有右孩子，优先入栈
			S.push(x->lc); //然后才转至左孩子
		}
		else //实不得已
		{
			S.push(x->rc); //才向右
		}
	}
	S.pop(); //返回之前，弹出栈顶的空节点
}

template <typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST& visit) //二叉树的后序遍历（迭代版）
{
	Stack<BinNodePosi<T>> S; //辅助栈
	if (x) S.push(x); //根节点入栈
	while (!S.empty())// x始终为当前节点
	{
		if (S.top() != x->parent) ////若栈顶非x之父（而为右兄）
		{
			gotoLeftmostLeaf(S); //则在其右兄子树中找到HLVFL（相当于递归深入）
		}
		x = S.pop(); visit(x->data); //弹出栈顶（即前一节点之后继），并访问之
	}
}