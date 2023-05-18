#pragma once
/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* �ļ����ƣ�Graph.h
* �ļ���ʶ��δ����
* ժ Ҫ��STL��׼ģ�����еĻ����ڽӾ���ʵ�ֵ�GraphMatrix�ĸ��˱�д��
*
* ��ǰ�汾��1.0
* �� �ߣ�RickJingDG
* �汾��Ҫ�����汾�ǻ����廪��ѧ�˿��Խ��ڵ����ݽṹ��C++���԰棩����д��
* ������ڣ�2023��5��16��
*
*/

//#include<iostream> //���ļ����ú��ļ���Ϣ����һ��
// ���ñ�׼���ͷ�ļ�


#include "../Vector/Vector.h"// ���÷Ǳ�׼���ͷ�ļ�
#include "Graph.h"

//=============ȫ�ֱ������忪ʼ=======================
// 
//=============ȫ�ֱ����������=======================

//=============�ṹ�嶨�忪ʼ=======================

template <typename Tv> struct Vertex//�������Ϊ���������δ�ϸ��װ��
{ 
    Tv data; int inDegree, outDegree; VStatus status; //���ݡ����������״̬
    Rank dTime, fTime; //ʱ���ǩ
    Rank parent; int priority; //�ڱ������еĸ��ڵ㡢���ȼ���
    Vertex(Tv const& d = (Tv)0) : //�����¶���
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1),
        fTime(-1), parent(-1), priority(INT_MAX) {} //�ݲ�����Ȩ�����
};

template <typename Te> struct Edge//�߶���Ϊ���������δ�ϸ��װ��
{ 
    Te data; int weight;
    EType type; //���ݡ�Ȩ�ء�����
    Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {} //����
};

template <typename Tv, typename Te> struct BfsPU //���BFS�㷨�Ķ������ȼ�������
{
    virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED) //����ukÿһ��δ�����ֵ��ڽӶ���v
        {
            if (g->priority(v) > g->priority(uk) + 1) //���䵽���ľ�����Ϊ���ȼ���
            {
                g->priority(v) = g->priority(uk) + 1; //�������ȼ�������
                g->parent(v) = uk; //���¸��ڵ�
            } //���Ч����ͬ�ڣ��ȱ�����������
        }
    }
};

template <typename Tv, typename Te> struct DfsPU //���DFS�㷨�Ķ������ȼ�������
{
    virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED) //����ukÿһ��δ�����ֵ��ڽӶ���v
        {
            if (g->priority(v) > g->priority(uk) - 1) //���䵽������ĸ�����Ϊ���ȼ���
            {
                g->priority(v) = g->priority(uk) - 1; //�������ȼ�������
                g->parent(v) = uk; //���¸��ڵ�
                return; //ע�⣺��BfsPU()��ͬ������ֻҪ��һ���ڽӶ���ɸ��£�������������
            }//���Ч����ͬ�ڣ��󱻷���������
        }
    }
};

template <typename Tv, typename Te> struct PrimPU //���Prim�㷨�Ķ������ȼ�������
{
    virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u)
    {
        if (UNDISCOVERED == g->status(u)) //����vÿһ��δ�����ֵ��ڽӶ���u
        {
            if (g->priority(u) > g->weight(v, u)) //��Prim�������ɳ�
            {
                g->priority(u) = g->weight(v, u); //�������ȼ�������
                g->parent(u) = v; //���¸��ڵ�
            }
        }
    }
};

template <typename Tv, typename Te> struct DijkPU//���Dijkstra�㷨�Ķ������ȼ�������
{
    virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u)
    {
        if (UNDISCOVERED == g->status(u)) //����vÿһ��δ�����ֵ��ڽӶ���u����Dijkstra����
        {
            if (g->priority(u) > g->priority(v) + g->weight(v, u)) //���ɳ�
            {
                g->priority(u) = g->priority(v) + g->weight(v, u); //�������ȼ�������
                g->parent(u) = v; //��ͬʱ���¸��ڵ�
            }
        }
    }
};

//=============�ṹ�嶨�����=======================

//=============�ඨ�忪ʼ=======================

template <typename Tv, typename Te> //�������͡�������
class GraphMatrix : public Graph<Tv, Te>  //�������������ڽӾ�����ʽʵ�ֵ�ͼ
{
private:
    Vector<Vertex<Tv>> V; //���㼯��������
    Vector<Vector<Edge<Te>*>> E; //�߼����ڽӾ���
public:
    GraphMatrix() { Graph<Tv, Te>::n = Graph<Tv, Te>::e = 0; } //����
    ~GraphMatrix() //����
    {
        for (Rank v = 0; v < Graph<Tv, Te>::n; v++) //���ж�̬������
        {
            for (Rank u = 0; u < Graph<Tv, Te>::n; u++) //�߼�¼
            {
                delete E[v][u]; //�������
            }
        }
    }
    // ����Ļ�����������ѯ��v�����㣨0 <= v < n��
    Tv& vertex(Rank v) { return V[v].data; } //����
    Rank inDegree(Rank v) { return V[v].inDegree; } //���
    Rank outDegree(Rank v) { return V[v].outDegree; } //����
    Rank firstNbr(Rank v) { return nextNbr(v, Graph<Tv, Te>::n); } //�׸��ڽӶ���
    Rank nextNbr(Rank v, Rank u) //����ڶ���u����һ�ڽӶ��㣨�����ڽӱ�Ч�ʸ��ߣ�
    {
        while ((-1 != --u) && !exists(v, u)); return u;//����������̽
    }
    VStatus& status(Rank v) { return V[v].status; } //״̬
    Rank& dTime(Rank v) { return V[v].dTime; } //ʱ���ǩdTime
    Rank& fTime(Rank v) { return V[v].fTime; } //ʱ���ǩfTime
    Rank& parent(Rank v) { return V[v].parent; } //�ڱ������еĸ���
    int& priority(Rank v) { return V[v].priority; } //�ڱ������е����ȼ���
    // ����Ķ�̬����
    Rank insert(Tv const& vertex) //���붥�㣬���ر��
    {
        for (Rank u = 0; u < Graph<Tv, Te>::n; u++)
        {
            E[u].insert(NULL);//������Ԥ��һ��Ǳ�ڵĹ�����
        }
        Graph<Tv, Te>::n++;
        E.insert(Vector<Edge<Te>*>(Graph<Tv, Te>::n, Graph<Tv, Te>::n, (Edge<Te>*)NULL)); //�����¶����Ӧ�ı�����
        return V.insert(Vertex<Tv>(vertex)); //������������һ������
    }
    Tv remove(Rank v) //ɾ����v�����㼰������ߣ�0 <= v < n��
    {
        for (Rank u = 0; u < Graph<Tv, Te>::n; u++) //����
        {
            if (exists(v, u)) //����
            {
                delete E[v][u]; V[u].inDegree--; Graph<Tv, Te>::e--;//����ɾ��
            }
        }
        E.remove(v); Graph<Tv, Te>::n--; //ɾ����v��
        Tv vBak = vertex(v); V.remove(v); //ɾ������v
        for (Rank u = 0; u < Graph<Tv, Te>::n; u++) //����
        {
            if (Edge<Te>* x = E[u].remove(v)) //���
            {
                delete x; V[u].outDegree--; Graph<Tv, Te>::e--;//����ɾ��
            }
        }
        return vBak; //���ر�ɾ���������Ϣ
    }
    // �ߵ�ȷ�ϲ���
    bool exists(Rank v, Rank u) //��(v, u)�Ƿ����
    {
        return (v < Graph<Tv, Te>::n) && (u < Graph<Tv, Te>::n) && (E[v][u] != NULL);
    }
    // �ߵĻ�����������ѯ����v��u֮������ߣ�0 <= v, u < n��exists(v, u)��
    EType& type(Rank v, Rank u) { return E[v][u]->type; } //��(v, u)������
    Te& edge(Rank v, Rank u) { return E[v][u]->data; } //��(v, u)������
    int& weight(Rank v, Rank u) { return E[v][u]->weight; } //��(v, u)��Ȩ��
    // �ߵĶ�̬����
    void insert(Te const& edge, int w, Rank v, Rank u)//����Ȩ��Ϊw�ı�(v, u)
    {
        if (exists(v, u)) return; //ȷ���ñ��в�����
        E[v][u] = new Edge<Te>(edge, w); //�����±�
        Graph<Tv, Te>::e++; V[v].outDegree++;
        V[u].inDegree++; //���±߼������������Ķ���
    }
    Te remove(Rank v, Rank u) //ɾ������v��u֮������ߣ�exists(v, u)��
    {
        Te eBak = edge(v, u); delete E[v][u];
        E[v][u] = NULL; //���ݺ�ɾ���߼�¼
        Graph<Tv, Te>::e--; V[v].outDegree--;
        V[u].inDegree--; //���±߼������������Ķ���
        return eBak; //���ر�ɾ���ߵ���Ϣ
    }
}; //GraphMatrix

//=============�ඨ�����=======================

//=============����������ʼ=======================
//void Function1(); // ȫ�ֺ�����������

//=============������������=======================

