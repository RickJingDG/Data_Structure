#pragma once
#include "Graph.h"//引用模板类
#include "../Queue/Queue.h"

template <typename Tv, typename Te> //广度优先搜索BFS算法（全图）
void Graph<Tv, Te>::bfs(Rank s) // s < n
{
    reset(); 
    Rank dClock = 0; //全图复位
    for (Rank v = s; v < s + n; v++) //从s起顺次检查所有顶点
    {
        if (UNDISCOVERED == status(v % n)) //一旦遇到尚未发现者
        {
            BFS(v % n, dClock); //即从它出发启动一次BFS
        }
    }
} //如此可完整覆盖全图，且总体复杂度依然保持为O(n+e)

template <typename Tv, typename Te> //广度优先搜索BFS算法（单个连通域）
void Graph<Tv, Te>::BFS(Rank v, Rank& dClock)// v < n
{ 
    Queue<Rank> Q; 
    status(v) = DISCOVERED; 
    Q.enqueue(v); 
    dTime(v) = dClock++; //起点入队
    for (Rank fClock = 0; !Q.empty(); ) //在Q变空之前，反复地
    { 
        if (dTime(v) < dTime(Q.front())) //dTime的增加，意味着开启新的一代，因此
        {
            dClock++, fClock = 0; //dTime递增，fTime复位
        }
        v = Q.dequeue(); //取出首顶点v，并
        for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //考查v的每一个邻居u
        {
            if (UNDISCOVERED == status(u))//若u尚未被发现，则发现之
            {
                status(u) = DISCOVERED;
                Q.enqueue(u);
                dTime(u) = dClock;
                type(v, u) = TREE; parent(u) = v; //引入树边，拓展BFS树
            }
            else //若u已被发现，或者甚至已访问完毕，则
            {
                type(v, u) = CROSS; //将(v, u)归类于跨边
            }
        }
        status(v) = VISITED; fTime(v) = fClock++; //至此，v访问完毕
    } //for
} //BFS

template <typename Tv, typename Te> //深度优先搜索DFS算法（全图）
void Graph<Tv, Te>::dfs(Rank s)// s < n
{
    reset();
    Rank clock = 0; //全图复位
    for (Rank v = s; v < s + n; v++) //从s起顺次检查所有顶点
    {
        if (UNDISCOVERED == status(v % n)) //一旦遇到尚未发现者
        {
            DFS(v % n, clock); //即从它出发启动一次DFS
        }
    }
}//如此可完整覆盖全图，且总体复杂度依然保持为O(n+e)

template <typename Tv, typename Te> //深度优先搜索DFS算法（单个连通域）
void Graph<Tv, Te>::DFS(Rank v, Rank& clock) // v < n
{ 
    dTime(v) = clock++; 
    status(v) = DISCOVERED; //发现当前顶点v
    for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //考查v的每一个邻居u
    {
        switch (status(u))//并视其状态分别处理
        {
        case UNDISCOVERED: // u尚未发现，意味着支撑树可在此拓展
            type(v, u) = TREE; 
            parent(u) = v;
            DFS(u, clock); 
            break;
        case DISCOVERED: // u已被发现但尚未访问完毕，应属被后代指向的祖先
            type(v, u) = BACKWARD; 
            break;
        default: // u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; 
            break;
        }
    }
    status(v) = VISITED; fTime(v) = clock++; //至此，当前顶点v方告访问完毕
}

template <typename Tv, typename Te> void Graph<Tv, Te>::bcc(Rank s) //基于DFS的BCC分解算法
{ 
    reset(); 
    Rank clock = 0;
    Rank v = s; 
    Stack<Rank> S; //栈S用以记录已访问的顶点
    do
        if (UNDISCOVERED == status(v))//一旦发现未发现的顶点（新连通分量）
        { 
            BCC(v, clock, S); //即从该顶点出发启动一次BCC
            S.pop(); //遍历返回后，弹出栈中最后一个顶点——当前连通域的起点
        }
    while (s != (v = (++v % n)));
}
#define hca(x) (fTime(x)) //利用此处闲置的fTime[]充当hca[]
template <typename Tv, typename Te> //顶点类型、边类型
void Graph<Tv, Te>::BCC(Rank v, Rank& clock, Stack<Rank>& S)  // assert: 0 <= v < n
{
    hca(v) = dTime(v) = ++clock; 
    status(v) = DISCOVERED;
    S.push(v); // v被发现并入栈
    for (int u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //枚举v的所有邻居u
    {
        switch (status(u)) //并视u的状态分别处理
        {
        case UNDISCOVERED:
            parent(u) = v; 
            type(v, u) = TREE;
            BCC(u, clock, S); //从顶点u处深入
            if (hca(u) < dTime(v)) //遍历返回后，若发现u（通过后向边）可指向v的真祖先
            {
                hca(v) = min(hca(v), hca(u)); //则v亦必如此
            }
            else //否则，以v为关节点（u以下即是一个BCC，且其中顶点此时正集中于栈S的顶部）
            {
                while (u != S.pop()); //弹出当前BCC中（除v外）的所有节点，可视需要做进一步处理
            }
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD; //标记(v, u)，并按照“越小越高”的准则
            if (u != parent(v)) hca(v) = min(hca(v), dTime(u)); //更新hca[v]
            break;
        default: //VISITED (digraphs only)
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED; //对v的访问结束
}
#undef hca

template <typename Tv, typename Te> //基于DFS的拓扑排序算法
Stack<Tv>* Graph<Tv, Te>::tSort(Rank s)// assert: 0 <= s < n
{ 
    reset(); 
    Rank clock = 0; //全图复位
    Stack<Tv>* S = new Stack<Tv>; //用栈记录排序顶点
    for (Rank v = s; v < s + n; v++) //从s起顺次检查所有顶点
    {
        if (UNDISCOVERED == status(v % n)) //一旦遇到尚未发现者
        {
            if (!TSort(v, clock, S)) //即从它出发启动一次TSort
            {
                while (!S->empty()) //任一连通域（亦即整图）非DAG
                {
                    S->pop();
                }
                break; //则不必继续计算，故直接返回
            }
        }
    }
    return S; //若输入为DAG，则S内各顶点自顶向底排序；否则（不存在拓扑排序），S空
} //如此可完整覆盖全图，且总体复杂度依然保持为O(n+e)

template <typename Tv, typename Te> //基于DFS的拓扑排序算法（单趟）
bool Graph<Tv, Te>::TSort(Rank v, Rank& clock, Stack<Tv>* S)  // v < n
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED; //发现顶点v
    for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //枚举v的所有邻居u
    {
        switch (status(u)) //并视u的状态分别处理
        {
        case UNDISCOVERED:
            parent(u) = v; 
            type(v, u) = TREE;
            if (!TSort(u, clock, S)) //从顶点u处出发深入搜索
            {
                return false; //若u及其后代不能拓扑排序（则全图亦必如此），故返回并报告
            }
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD; //一旦发现后向边（非DAG），则
            return false; //不必深入，故返回并报告
        default: // VISITED (digraphs only)
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED; S->push(vertex(v)); //顶点被标记为VISITED时，随即入栈
    return true; // v及其后代可以拓扑排序
}

template <typename Tv, typename Te> template <typename PU> //优先级搜索（全图）
void Graph<Tv, Te>::pfs(Rank s, PU prioUpdater) // s < n
{
    reset(); //全图复位
    for (Rank v = s; v < s + n; v++) //从s起顺次检查所有顶点
    {
        if (UNDISCOVERED == status(v % n)) //一旦遇到尚未发现者
        {
            PFS(v % n, prioUpdater); //即从它出发启动一次PFS
        }
    }
}//如此可完整覆盖全图，且总体复杂度依然保持为O(n+e)

template <typename Tv, typename Te> template <typename PU> //顶点类型、边类型、优先级更新器
void Graph<Tv, Te>::PFS(Rank v, PU prioUpdater) //优先级搜索（单个连通域）
{ 
    priority(v) = 0;
    status(v) = VISITED; //初始化，起点v加至PFS树中
    while (1) //将下一顶点和边加至PFS树中
    { 
        for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //对v的每一个邻居u
        {
            prioUpdater(this, v, u); //更新其优先级及其父亲
        }
        int shortest = INT_MAX;
        for (Rank u = 0; u < n; u++) //从尚未加入遍历树的顶点中，选出下一个优先级
        {
            if ((UNDISCOVERED == status(u)) && (shortest > priority(u))) //最高的
            {
                shortest = priority(u), v = u;//顶点v
            } 
        }
        if (shortest == INT_MAX) break; //直至所有顶点均已加入
        status(v) = VISITED; type(parent(v), v) = TREE; //将v加入遍历树
    }
} //通过定义具体的优先级更新策略prioUpdater，即可实现不同的算法功能

template <typename Tv, typename Te> //Prim算法：无向连通图，各边表示为方向互逆、权重相等的一对边
void Graph<Tv, Te>::prim(Rank s) // s < n
{ 
    reset(); 
    priority(s) = 0;
    for (Rank i = 0; i < n; i++) //共需引入n个顶点和n-1条边
    {
        status(s) = VISITED;
        if (-1 != parent(s)) type(parent(s), s) = TREE; //引入当前的s
        for (Rank j = firstNbr(s); -1 != j; j = nextNbr(s, j)) //枚举s的所有邻居j
        {
            if ((status(j) == UNDISCOVERED) && (priority(j) > weight(s, j))) //对邻接顶点j做松弛
            {
                priority(j) = weight(s, j); parent(j) = s;
            } //与Dijkstra算法唯一的不同之处
        }
        int shortest = INT_MAX;
        for (Rank j = 0; j < n; j++) //选出下一极短跨边
        {
            if ((status(j) == UNDISCOVERED) && (shortest > priority(j)))
            {
                shortest = priority(j); s = j;
            }
        }
    }
}

template <typename Tv, typename Te> //最短路径Dijkstra算法：适用于一般的有向图
void Graph<Tv, Te>::dijkstra(Rank s)// s < n
{ 
    reset(); 
    priority(s) = 0;
    for (Rank i = 0; i < n; i++) //共需引入n个顶点和n-1条边
    {
        status(s) = VISITED;
        if (-1 != parent(s)) type(parent(s), s) = TREE; //引入当前的s
        for (Rank j = firstNbr(s); -1 != j; j = nextNbr(s, j)) //枚举s的所有邻居j
        {
            if ((status(j) == UNDISCOVERED) && (priority(j) > priority(s) + weight(s, j))) //对邻接顶点j做松弛
            {
                priority(j) = priority(s) + weight(s, j); parent(j) = s;
            } //与Prim算法唯一的不同之处
        }
        int shortest = INT_MAX;
        for (Rank j = 0; j < n; j++) //选出下一最近顶点
        {
            if ((status(j) == UNDISCOVERED) && (shortest > priority(j)))
            {
                shortest = priority(j); s = j;
            }
        }
    }
} //对于无向连通图，假设每一条边表示为方向互逆、权重相等的一对边
