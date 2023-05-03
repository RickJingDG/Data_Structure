#pragma once
#include "BinNode.h"//����ģ����
template <typename T> Rank BinNode<T>::size() //ͳ�Ƶ�ǰ�ڵ���������������Ϊ����������ģ
{
	Rank s = 1; //���뱾��
	if (lc) s += lc->size(); //�ݹ������������ģ
	if (rc) s += rc->size(); //�ݹ������������ģ
	return s;
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsLC(T const& e)
{
	return lc = new BinNode(e, this); //��e��Ϊ��ǰ�ڵ�����Ӳ��������
}

template <typename T> BinNodePosi<T> BinNode<T>::insertAsRC(T const& e)
{
	return rc = new BinNode(e, this); //��e��Ϊ��ǰ�ڵ���Һ��Ӳ��������
}

template <typename T> BinNodePosi<T> BinNode<T>::succ() //��λ�ڵ�v��ֱ�Ӻ��
{ 
	BinNodePosi<T> s = this; //��¼��̵���ʱ����
	if (rc)//�����Һ��ӣ���ֱ�Ӻ�̱�����������
	{ //����ؾ���
		s = rc; //��������
		while (HasLChild(*s)) s = s->lc; //�����С���Ľڵ�
	}
	else //����ֱ�Ӻ��Ӧ�ǡ�����ǰ�ڵ���������������е�������ȡ�
	{ //����ؾ���
		while (IsRChild(*s)) s = s->parent; //������������֧�����ϳ����Ϸ��ƶ�
		s = s->parent; //����ٳ����Ϸ��ƶ�һ�������ִ�ֱ�Ӻ�̣�������ڣ�
	}
	return s;
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travLevel(VST& visit) //��������α����㷨
{ 
	Queue<BinNodePosi<T>> Q; Q.enqueue(this); //���븨�����У����ڵ����
	while (!Q.empty()) //�ڶ����ٴα��֮ǰ����������
	{
		BinNodePosi<T> x = Q.dequeue(); visit(x->data); //ȡ�����׽ڵ㲢����֮
		if (HasLChild(*x)) Q.enqueue(x->lc); //�������
		if (HasRChild(*x)) Q.enqueue(x->rc); //�Һ������
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travPre(VST& visit) //��������������㷨ͳһ���
{
	switch (2) //�˴�ֻѡ�������2��Ԥ��������1�͵ݹ�棬�Ա�δ������
	{ 
	case 1: travPre_I1(this, visit); break; //������#1
	case 2: travPre_I2(this, visit); break; //������#2
	default: travPre_R(this, visit); break; //�ݹ��
	}
}

//�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ㣻��;�ڵ���������������
template <typename T, typename VST> //Ԫ�����͡�������
static void visitAlongVine(BinNodePosi<T> x, VST& visit, Stack<BinNodePosi<T>>& S) 
{
	while (x) 
	{
		visit(x->data); //���ʵ�ǰ�ڵ�
		S.push(x->rc); //�Һ�����ջ�ݴ棨���Ż���ͨ���жϣ�����յ��Һ�����ջ��
		x = x->lc; //�����֧����һ��
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travPre_I2(BinNodePosi<T> x, VST& visit)//��������������㷨��������#2��
{ 
	Stack<BinNodePosi<T>> S; //����ջ
	while (true) 
	{
		visitAlongVine(x, visit, S); //�ӵ�ǰ�ڵ��������������
		if (S.empty()) break; //ֱ��ջ��
		x = S.pop(); //������һ�������
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode<T>::travIn(VST& visit) //��������������㷨ͳһ���
{ 
	switch (rand() % 3)  //�˴����ֵ����汾���ѡ��
	{
	case 1: travIn_I1(this, visit); break; //������#1
	case 2: travIn_I2(this, visit); break; //������#2
	case 3: travIn_I3(this, visit); break; //������#3
	default: travIn_R(this, visit); break; //�ݹ��
	}
}

template <typename T> //�ӵ�ǰ�ڵ�����������֧�������룬ֱ��û�����֧�Ľڵ�
static void goAlongVine(BinNodePosi<T> x, Stack<BinNodePosi<T>>& S) 
{
	while (x) { S.push(x); x = x->lc; } //��ǰ�ڵ���ջ���漴������֧���룬����ֱ��������
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I1(BinNodePosi<T> x, VST& visit) //��������������㷨��������#1��
{ 
	Stack<BinNodePosi<T>> S; //����ջ
	while (true)
	{
		goAlongVine(x, S); //�ӵ�ǰ�ڵ������������ջ
		if (S.empty()) break; //ֱ�����нڵ㴦�����
		x = S.pop(); visit(x->data); //����ջ���ڵ㲢����֮
		x = x->rc; //ת��������
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I2(BinNodePosi<T> x, VST& visit) //��������������㷨��������#2��
{ 
	Stack<BinNodePosi<T>> S; //����ջ
	while (true)
	{
		if (x)
		{
			S.push(x); //���ڵ��ջ
			x = x->lc; //�������������
		}
		else if (!S.empty())
		{
			x = S.pop(); //��δ���ʵ�������Ƚڵ���ջ
			visit(x->data); //���ʸ����Ƚڵ�
			x = x->rc; //�������ȵ�������
		}
		else
			break; //�������
	}
}

template <typename T, typename VST> //Ԫ�����͡�������
void travIn_I3(BinNodePosi<T> x, VST& visit)//��������������㷨��������#3�����踨��ջ��
{ 
	bool backtrack = false; //ǰһ���Ƿ�մ����������ݡ���ʡȥջ����O(1)�����ռ�
	while (true)
	{
		if (!backtrack && HasLChild(*x)) //�����������Ҳ��Ǹոջ��ݣ���
		{
			x = x->lc; //�������������
		}
		else //���򡪡�����������ոջ��ݣ��൱������������
		{
			visit(x->data); //���ʸýڵ�
			if (HasRChild(*x)) //�����������ǿգ���
			{
				x = x->rc; //������������������
				backtrack = false; //���رջ��ݱ�־
			}
			else //���������գ���
			{
				if (!(x = x->succ())) break; //���ݣ����ִ�ĩ�ڵ�ʱ���˳����أ�
				backtrack = true; //�����û��ݱ�־
			}
		}
	}
}

template <typename T> template <typename VST> //Ԫ�����͡�������
void BinNode <T>::travPost(VST& visit)//��������������㷨ͳһ���
{ 
	switch (1)  //�˴�ѡ������棬��Ԥ���ݹ��
	{
	case 1: travPost_I(this, visit); break; //������
	default: travPost_R(this, visit); break; //�ݹ��
	}
}

template <typename T> //����Sջ���ڵ�Ϊ���������У��ҵ�������ɼ�Ҷ�ڵ�
static void gotoLeftmostLeaf(Stack<BinNodePosi<T>>& S) //��;�����ڵ�������ջ
{
	while (BinNodePosi<T> x = S.top()) //�Զ����£�������鵱ǰ�ڵ㣨��ջ����
	{
		if (HasLChild(*x)) //����������
		{
			if (HasRChild(*x)) S.push(x->rc); //�����Һ��ӣ�������ջ
			S.push(x->lc); //Ȼ���ת������
		}
		else //ʵ������
		{
			S.push(x->rc); //������
		}
	}
	S.pop(); //����֮ǰ������ջ���Ŀսڵ�
}

template <typename T, typename VST>
void travPost_I(BinNodePosi<T> x, VST& visit) //�������ĺ�������������棩
{
	Stack<BinNodePosi<T>> S; //����ջ
	if (x) S.push(x); //���ڵ���ջ
	while (!S.empty())// xʼ��Ϊ��ǰ�ڵ�
	{
		if (S.top() != x->parent) ////��ջ����x֮������Ϊ���֣�
		{
			gotoLeftmostLeaf(S); //�����������������ҵ�HLVFL���൱�ڵݹ����룩
		}
		x = S.pop(); visit(x->data); //����ջ������ǰһ�ڵ�֮��̣���������֮
	}
}