#pragma once
#include "Graph.h"//����ģ����
#include "../Queue/Queue.h"

template <typename Tv, typename Te> //�����������BFS�㷨��ȫͼ��
void Graph<Tv, Te>::bfs(Rank s) // s < n
{
    reset(); 
    Rank dClock = 0; //ȫͼ��λ
    for (Rank v = s; v < s + n; v++) //��s��˳�μ�����ж���
    {
        if (UNDISCOVERED == status(v % n)) //һ��������δ������
        {
            BFS(v % n, dClock); //��������������һ��BFS
        }
    }
} //��˿���������ȫͼ�������帴�Ӷ���Ȼ����ΪO(n+e)

template <typename Tv, typename Te> //�����������BFS�㷨��������ͨ��
void Graph<Tv, Te>::BFS(Rank v, Rank& dClock)// v < n
{ 
    Queue<Rank> Q; 
    status(v) = DISCOVERED; 
    Q.enqueue(v); 
    dTime(v) = dClock++; //������
    for (Rank fClock = 0; !Q.empty(); ) //��Q���֮ǰ��������
    { 
        if (dTime(v) < dTime(Q.front())) //dTime�����ӣ���ζ�ſ����µ�һ�������
        {
            dClock++, fClock = 0; //dTime������fTime��λ
        }
        v = Q.dequeue(); //ȡ���׶���v����
        for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //����v��ÿһ���ھ�u
        {
            if (UNDISCOVERED == status(u))//��u��δ�����֣�����֮
            {
                status(u) = DISCOVERED;
                Q.enqueue(u);
                dTime(u) = dClock;
                type(v, u) = TREE; parent(u) = v; //�������ߣ���չBFS��
            }
            else //��u�ѱ����֣����������ѷ�����ϣ���
            {
                type(v, u) = CROSS; //��(v, u)�����ڿ��
            }
        }
        status(v) = VISITED; fTime(v) = fClock++; //���ˣ�v�������
    } //for
} //BFS

template <typename Tv, typename Te> //�����������DFS�㷨��ȫͼ��
void Graph<Tv, Te>::dfs(Rank s)// s < n
{
    reset();
    Rank clock = 0; //ȫͼ��λ
    for (Rank v = s; v < s + n; v++) //��s��˳�μ�����ж���
    {
        if (UNDISCOVERED == status(v % n)) //һ��������δ������
        {
            DFS(v % n, clock); //��������������һ��DFS
        }
    }
}//��˿���������ȫͼ�������帴�Ӷ���Ȼ����ΪO(n+e)

template <typename Tv, typename Te> //�����������DFS�㷨��������ͨ��
void Graph<Tv, Te>::DFS(Rank v, Rank& clock) // v < n
{ 
    dTime(v) = clock++; 
    status(v) = DISCOVERED; //���ֵ�ǰ����v
    for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //����v��ÿһ���ھ�u
    {
        switch (status(u))//������״̬�ֱ���
        {
        case UNDISCOVERED: // u��δ���֣���ζ��֧�������ڴ���չ
            type(v, u) = TREE; 
            parent(u) = v;
            DFS(u, clock); 
            break;
        case DISCOVERED: // u�ѱ����ֵ���δ������ϣ�Ӧ�������ָ�������
            type(v, u) = BACKWARD; 
            break;
        default: // u�ѷ�����ϣ�VISITED������ͼ�������ӳ�Ϯ��ϵ��Ϊǰ��߻���
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; 
            break;
        }
    }
    status(v) = VISITED; fTime(v) = clock++; //���ˣ���ǰ����v����������
}

template <typename Tv, typename Te> void Graph<Tv, Te>::bcc(Rank s) //����DFS��BCC�ֽ��㷨
{ 
    reset(); 
    Rank clock = 0;
    Rank v = s; 
    Stack<Rank> S; //ջS���Լ�¼�ѷ��ʵĶ���
    do
        if (UNDISCOVERED == status(v))//һ������δ���ֵĶ��㣨����ͨ������
        { 
            BCC(v, clock, S); //���Ӹö����������һ��BCC
            S.pop(); //�������غ󣬵���ջ�����һ�����㡪����ǰ��ͨ������
        }
    while (s != (v = (++v % n)));
}
#define hca(x) (fTime(x)) //���ô˴����õ�fTime[]�䵱hca[]
template <typename Tv, typename Te> //�������͡�������
void Graph<Tv, Te>::BCC(Rank v, Rank& clock, Stack<Rank>& S)  // assert: 0 <= v < n
{
    hca(v) = dTime(v) = ++clock; 
    status(v) = DISCOVERED;
    S.push(v); // v�����ֲ���ջ
    for (int u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //ö��v�������ھ�u
    {
        switch (status(u)) //����u��״̬�ֱ���
        {
        case UNDISCOVERED:
            parent(u) = v; 
            type(v, u) = TREE;
            BCC(u, clock, S); //�Ӷ���u������
            if (hca(u) < dTime(v)) //�������غ�������u��ͨ������ߣ���ָ��v��������
            {
                hca(v) = min(hca(v), hca(u)); //��v������
            }
            else //������vΪ�ؽڵ㣨u���¼���һ��BCC�������ж����ʱ��������ջS�Ķ�����
            {
                while (u != S.pop()); //������ǰBCC�У���v�⣩�����нڵ㣬������Ҫ����һ������
            }
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD; //���(v, u)�������ա�ԽСԽ�ߡ���׼��
            if (u != parent(v)) hca(v) = min(hca(v), dTime(u)); //����hca[v]
            break;
        default: //VISITED (digraphs only)
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED; //��v�ķ��ʽ���
}
#undef hca

template <typename Tv, typename Te> //����DFS�����������㷨
Stack<Tv>* Graph<Tv, Te>::tSort(Rank s)// assert: 0 <= s < n
{ 
    reset(); 
    Rank clock = 0; //ȫͼ��λ
    Stack<Tv>* S = new Stack<Tv>; //��ջ��¼���򶥵�
    for (Rank v = s; v < s + n; v++) //��s��˳�μ�����ж���
    {
        if (UNDISCOVERED == status(v % n)) //һ��������δ������
        {
            if (!TSort(v, clock, S)) //��������������һ��TSort
            {
                while (!S->empty()) //��һ��ͨ���༴��ͼ����DAG
                {
                    S->pop();
                }
                break; //�򲻱ؼ������㣬��ֱ�ӷ���
            }
        }
    }
    return S; //������ΪDAG����S�ڸ������Զ�������򣻷��򣨲������������򣩣�S��
} //��˿���������ȫͼ�������帴�Ӷ���Ȼ����ΪO(n+e)

template <typename Tv, typename Te> //����DFS�����������㷨�����ˣ�
bool Graph<Tv, Te>::TSort(Rank v, Rank& clock, Stack<Tv>* S)  // v < n
{
    dTime(v) = ++clock;
    status(v) = DISCOVERED; //���ֶ���v
    for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //ö��v�������ھ�u
    {
        switch (status(u)) //����u��״̬�ֱ���
        {
        case UNDISCOVERED:
            parent(u) = v; 
            type(v, u) = TREE;
            if (!TSort(u, clock, S)) //�Ӷ���u��������������
            {
                return false; //��u��������������������ȫͼ�����ˣ����ʷ��ز�����
            }
            break;
        case DISCOVERED:
            type(v, u) = BACKWARD; //һ�����ֺ���ߣ���DAG������
            return false; //�������룬�ʷ��ز�����
        default: // VISITED (digraphs only)
            type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS;
            break;
        }
    }
    status(v) = VISITED; S->push(vertex(v)); //���㱻���ΪVISITEDʱ���漴��ջ
    return true; // v������������������
}

template <typename Tv, typename Te> template <typename PU> //���ȼ�������ȫͼ��
void Graph<Tv, Te>::pfs(Rank s, PU prioUpdater) // s < n
{
    reset(); //ȫͼ��λ
    for (Rank v = s; v < s + n; v++) //��s��˳�μ�����ж���
    {
        if (UNDISCOVERED == status(v % n)) //һ��������δ������
        {
            PFS(v % n, prioUpdater); //��������������һ��PFS
        }
    }
}//��˿���������ȫͼ�������帴�Ӷ���Ȼ����ΪO(n+e)

template <typename Tv, typename Te> template <typename PU> //�������͡������͡����ȼ�������
void Graph<Tv, Te>::PFS(Rank v, PU prioUpdater) //���ȼ�������������ͨ��
{ 
    priority(v) = 0;
    status(v) = VISITED; //��ʼ�������v����PFS����
    while (1) //����һ����ͱ߼���PFS����
    { 
        for (Rank u = firstNbr(v); -1 != u; u = nextNbr(v, u)) //��v��ÿһ���ھ�u
        {
            prioUpdater(this, v, u); //���������ȼ����丸��
        }
        int shortest = INT_MAX;
        for (Rank u = 0; u < n; u++) //����δ����������Ķ����У�ѡ����һ�����ȼ�
        {
            if ((UNDISCOVERED == status(u)) && (shortest > priority(u))) //��ߵ�
            {
                shortest = priority(u), v = u;//����v
            } 
        }
        if (shortest == INT_MAX) break; //ֱ�����ж�����Ѽ���
        status(v) = VISITED; type(parent(v), v) = TREE; //��v���������
    }
} //ͨ�������������ȼ����²���prioUpdater������ʵ�ֲ�ͬ���㷨����

template <typename Tv, typename Te> //Prim�㷨��������ͨͼ�����߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�
void Graph<Tv, Te>::prim(Rank s) // s < n
{ 
    reset(); 
    priority(s) = 0;
    for (Rank i = 0; i < n; i++) //��������n�������n-1����
    {
        status(s) = VISITED;
        if (-1 != parent(s)) type(parent(s), s) = TREE; //���뵱ǰ��s
        for (Rank j = firstNbr(s); -1 != j; j = nextNbr(s, j)) //ö��s�������ھ�j
        {
            if ((status(j) == UNDISCOVERED) && (priority(j) > weight(s, j))) //���ڽӶ���j���ɳ�
            {
                priority(j) = weight(s, j); parent(j) = s;
            } //��Dijkstra�㷨Ψһ�Ĳ�֮ͬ��
        }
        int shortest = INT_MAX;
        for (Rank j = 0; j < n; j++) //ѡ����һ���̿��
        {
            if ((status(j) == UNDISCOVERED) && (shortest > priority(j)))
            {
                shortest = priority(j); s = j;
            }
        }
    }
}

template <typename Tv, typename Te> //���·��Dijkstra�㷨��������һ�������ͼ
void Graph<Tv, Te>::dijkstra(Rank s)// s < n
{ 
    reset(); 
    priority(s) = 0;
    for (Rank i = 0; i < n; i++) //��������n�������n-1����
    {
        status(s) = VISITED;
        if (-1 != parent(s)) type(parent(s), s) = TREE; //���뵱ǰ��s
        for (Rank j = firstNbr(s); -1 != j; j = nextNbr(s, j)) //ö��s�������ھ�j
        {
            if ((status(j) == UNDISCOVERED) && (priority(j) > priority(s) + weight(s, j))) //���ڽӶ���j���ɳ�
            {
                priority(j) = priority(s) + weight(s, j); parent(j) = s;
            } //��Prim�㷨Ψһ�Ĳ�֮ͬ��
        }
        int shortest = INT_MAX;
        for (Rank j = 0; j < n; j++) //ѡ����һ�������
        {
            if ((status(j) == UNDISCOVERED) && (shortest > priority(j)))
            {
                shortest = priority(j); s = j;
            }
        }
    }
} //����������ͨͼ������ÿһ���߱�ʾΪ�����桢Ȩ����ȵ�һ�Ա�
