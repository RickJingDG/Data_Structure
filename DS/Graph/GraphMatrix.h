#pragma once
/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* 文件名称：Graph.h
* 文件标识：未定义
* 摘 要：STL标准模板类中的基于邻接矩阵实现的GraphMatrix的个人编写版
*
* 当前版本：1.0
* 作 者：RickJingDG
* 版本概要：本版本是基于清华大学邓俊辉教授的数据结构（C++语言版）来编写。
* 完成日期：2023年5月16日
*
*/

//#include<iostream> //库文件引用和文件信息隔开一行
// 引用标准库的头文件


#include "../Vector/Vector.h"// 引用非标准库的头文件
#include "Graph.h"

//=============全局变量定义开始=======================
// 
//=============全局变量定义结束=======================

//=============结构体定义开始=======================

template <typename Tv> struct Vertex//顶点对象（为简化起见，并未严格封装）
{ 
    Tv data; int inDegree, outDegree; VStatus status; //数据、出入度数、状态
    Rank dTime, fTime; //时间标签
    Rank parent; int priority; //在遍历树中的父节点、优先级数
    Vertex(Tv const& d = (Tv)0) : //构造新顶点
        data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), dTime(-1),
        fTime(-1), parent(-1), priority(INT_MAX) {} //暂不考虑权重溢出
};

template <typename Te> struct Edge//边对象（为简化起见，并未严格封装）
{ 
    Te data; int weight;
    EType type; //数据、权重、类型
    Edge(Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) {} //构造
};

template <typename Tv, typename Te> struct BfsPU //针对BFS算法的顶点优先级更新器
{
    virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED) //对于uk每一尚未被发现的邻接顶点v
        {
            if (g->priority(v) > g->priority(uk) + 1) //将其到起点的距离作为优先级数
            {
                g->priority(v) = g->priority(uk) + 1; //更新优先级（数）
                g->parent(v) = uk; //更新父节点
            } //如此效果等同于，先被发现者优先
        }
    }
};

template <typename Tv, typename Te> struct DfsPU //针对DFS算法的顶点优先级更新器
{
    virtual void operator()(Graph<Tv, Te>* g, int uk, int v)
    {
        if (g->status(v) == UNDISCOVERED) //对于uk每一尚未被发现的邻接顶点v
        {
            if (g->priority(v) > g->priority(uk) - 1) //将其到起点距离的负数作为优先级数
            {
                g->priority(v) = g->priority(uk) - 1; //更新优先级（数）
                g->parent(v) = uk; //更新父节点
                return; //注意：与BfsPU()不同，这里只要有一个邻接顶点可更新，即可立即返回
            }//如此效果等同于，后被发现者优先
        }
    }
};

template <typename Tv, typename Te> struct PrimPU //针对Prim算法的顶点优先级更新器
{
    virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u)
    {
        if (UNDISCOVERED == g->status(u)) //对于v每一尚未被发现的邻接顶点u
        {
            if (g->priority(u) > g->weight(v, u)) //按Prim策略做松弛
            {
                g->priority(u) = g->weight(v, u); //更新优先级（数）
                g->parent(u) = v; //更新父节点
            }
        }
    }
};

template <typename Tv, typename Te> struct DijkPU//针对Dijkstra算法的顶点优先级更新器
{
    virtual void operator()(Graph<Tv, Te>* g, Rank v, Rank u)
    {
        if (UNDISCOVERED == g->status(u)) //对于v每一尚未被发现的邻接顶点u，按Dijkstra策略
        {
            if (g->priority(u) > g->priority(v) + g->weight(v, u)) //做松弛
            {
                g->priority(u) = g->priority(v) + g->weight(v, u); //更新优先级（数）
                g->parent(u) = v; //并同时更新父节点
            }
        }
    }
};

//=============结构体定义结束=======================

//=============类定义开始=======================

template <typename Tv, typename Te> //顶点类型、边类型
class GraphMatrix : public Graph<Tv, Te>  //基于向量，以邻接矩阵形式实现的图
{
private:
    Vector<Vertex<Tv>> V; //顶点集（向量）
    Vector<Vector<Edge<Te>*>> E; //边集（邻接矩阵）
public:
    GraphMatrix() { Graph<Tv, Te>::n = Graph<Tv, Te>::e = 0; } //构造
    ~GraphMatrix() //析构
    {
        for (Rank v = 0; v < Graph<Tv, Te>::n; v++) //所有动态创建的
        {
            for (Rank u = 0; u < Graph<Tv, Te>::n; u++) //边记录
            {
                delete E[v][u]; //逐条清除
            }
        }
    }
    // 顶点的基本操作：查询第v个顶点（0 <= v < n）
    Tv& vertex(Rank v) { return V[v].data; } //数据
    Rank inDegree(Rank v) { return V[v].inDegree; } //入度
    Rank outDegree(Rank v) { return V[v].outDegree; } //出度
    Rank firstNbr(Rank v) { return nextNbr(v, Graph<Tv, Te>::n); } //首个邻接顶点
    Rank nextNbr(Rank v, Rank u) //相对于顶点u的下一邻接顶点（改用邻接表效率更高）
    {
        while ((-1 != --u) && !exists(v, u)); return u;//逆向线性试探
    }
    VStatus& status(Rank v) { return V[v].status; } //状态
    Rank& dTime(Rank v) { return V[v].dTime; } //时间标签dTime
    Rank& fTime(Rank v) { return V[v].fTime; } //时间标签fTime
    Rank& parent(Rank v) { return V[v].parent; } //在遍历树中的父亲
    int& priority(Rank v) { return V[v].priority; } //在遍历树中的优先级数
    // 顶点的动态操作
    Rank insert(Tv const& vertex) //插入顶点，返回编号
    {
        for (Rank u = 0; u < Graph<Tv, Te>::n; u++)
        {
            E[u].insert(NULL);//各顶点预留一条潜在的关联边
        }
        Graph<Tv, Te>::n++;
        E.insert(Vector<Edge<Te>*>(Graph<Tv, Te>::n, Graph<Tv, Te>::n, (Edge<Te>*)NULL)); //创建新顶点对应的边向量
        return V.insert(Vertex<Tv>(vertex)); //顶点向量增加一个顶点
    }
    Tv remove(Rank v) //删除第v个顶点及其关联边（0 <= v < n）
    {
        for (Rank u = 0; u < Graph<Tv, Te>::n; u++) //所有
        {
            if (exists(v, u)) //出边
            {
                delete E[v][u]; V[u].inDegree--; Graph<Tv, Te>::e--;//逐条删除
            }
        }
        E.remove(v); Graph<Tv, Te>::n--; //删除第v行
        Tv vBak = vertex(v); V.remove(v); //删除顶点v
        for (Rank u = 0; u < Graph<Tv, Te>::n; u++) //所有
        {
            if (Edge<Te>* x = E[u].remove(v)) //入边
            {
                delete x; V[u].outDegree--; Graph<Tv, Te>::e--;//逐条删除
            }
        }
        return vBak; //返回被删除顶点的信息
    }
    // 边的确认操作
    bool exists(Rank v, Rank u) //边(v, u)是否存在
    {
        return (v < Graph<Tv, Te>::n) && (u < Graph<Tv, Te>::n) && (E[v][u] != NULL);
    }
    // 边的基本操作：查询顶点v与u之间的联边（0 <= v, u < n且exists(v, u)）
    EType& type(Rank v, Rank u) { return E[v][u]->type; } //边(v, u)的类型
    Te& edge(Rank v, Rank u) { return E[v][u]->data; } //边(v, u)的数据
    int& weight(Rank v, Rank u) { return E[v][u]->weight; } //边(v, u)的权重
    // 边的动态操作
    void insert(Te const& edge, int w, Rank v, Rank u)//插入权重为w的边(v, u)
    {
        if (exists(v, u)) return; //确保该边尚不存在
        E[v][u] = new Edge<Te>(edge, w); //创建新边
        Graph<Tv, Te>::e++; V[v].outDegree++;
        V[u].inDegree++; //更新边计数与关联顶点的度数
    }
    Te remove(Rank v, Rank u) //删除顶点v和u之间的联边（exists(v, u)）
    {
        Te eBak = edge(v, u); delete E[v][u];
        E[v][u] = NULL; //备份后删除边记录
        Graph<Tv, Te>::e--; V[v].outDegree--;
        V[u].inDegree--; //更新边计数与关联顶点的度数
        return eBak; //返回被删除边的信息
    }
}; //GraphMatrix

//=============类定义结束=======================

//=============函数声明开始=======================
//void Function1(); // 全局函数声明：无

//=============函数声明结束=======================

