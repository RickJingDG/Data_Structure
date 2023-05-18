#define _CRT_SECURE_NO_WARNINGS 1
#include<cstdio>//����cģʽ��ȷ�������������
#include<iostream>//���ñ�׼���������
#include "../../Graph/GraphMatrix.h"

template <typename Tv, typename Te> //�������͡�������
void randomGraph(GraphMatrix<Tv, Te>& g, Rank n, Rank e);
void p(GraphMatrix<char, int>& s);
void p(VStatus& e);
void p(EType& e);

int main()//ͼ����
{
    Rank n = 20, e = 20;
    srand((unsigned int)time(NULL)); //�������
    GraphMatrix<char, int> g;
    randomGraph<char, int>(g, n, e); //�������ַ���ţ���Ϊ����Ȩ��
    p(g);
    printf("\n");
    printf("=== BFS\n");
    g.bfs(0);
    p(g);
    printf("=== DFS\n");
    g.dfs(0);
    p(g);
    Stack<char>* ts = g.tSort(0);
    printf("=== Dijkstra\n");
    g.dijkstra(0);
    p(g);
    printf("=== Prim\n");
    g.prim(0);
    p(g);
    return 0;
}

template <typename Tv, typename Te> //�������͡�������
void randomGraph(GraphMatrix<Tv, Te>& g, Rank n, Rank e)//������v�����㡢e���߹��ɵ����ͼ0 < e(e-1) <= v
{
    while ((g.n < n) || (g.e < e)) //�������
    {
        if (g.n < n) //����
        {
            if (rand() % 100 < 65) //65%���ʲ��붥��
            {
                Tv vertex = (Tv)('A' + rand() % 26);
                g.insert(vertex);
            }
            else//35%����ɾ������
            {
                if (1 > g.n) continue;
                int v = rand() % g.n;
                Tv x = g.remove(v);
            }
        }
        if ((1 < g.n) && (g.e < e)) //��
        {
            if (rand() % 100 < 65) //65%���ʲ����
            {
                int v = rand() % g.n, j = rand() % g.n; Te e = rand() % ((Te)3 * n);
                if (!g.exists(v, j))
                {
                    g.insert(e, e, v, j);
                }
            }
            else //35%����ɾ����
            {
                int v = rand() % g.n, j = rand() % g.n;
                if (g.exists(v, j))
                {
                    Te e = g.remove(v, j);
                }
            }
        }
    }
    for (Rank v = 0; v < n; v++) g.vertex(v) = 'A' + (Tv)v;
}

void p(char e) { printf(" %c", (31 < e) && (e < 128) ? e : '$'); }
void p(int& e) { printf(" %04d", e); }
void p(const char* x) { printf(" %s", x ? x : "<NULL>"); }

void p(GraphMatrix<char, int>& s )
{
    Rank inD = 0; for (Rank i = 0; i < s.n; i++) inD += s.inDegree(i);
    Rank outD = 0; for (Rank i = 0; i < s.n; i++) outD += s.outDegree(i);
    p(s.n); printf(" "); p(inD); printf("|");
    for (Rank i = 0; i < s.n; i++) { p(s.vertex(i)); printf("["); p(s.status(i)); printf("] "); }
    printf("\n");
    // �����У�����
    p(outD); printf(" "); p(s.e); printf("|");
    for (Rank i = 0; i < s.n; i++) { p(s.inDegree(i)); printf(" "); }
    printf("|\n");
    // ˮƽ�ָ���
    printf("-----------+"); for (Rank i = 0; i < s.n; i++) printf("------");
    printf("+----------------------------\n");
    // �������������
    for (Rank i = 0; i < s.n; i++) {
        p(s.vertex(i)); printf("["); p(s.status(i)); printf("] "); p(s.outDegree(i)); printf("|");
        for (Rank j = 0; j < s.n; j++)
            if (s.exists(i, j)) { p(s.edge(i, j)); p(s.type(i, j)); }
            else printf("     .");
        printf("| "); p(s.dTime(i)); printf(" "); p(s.fTime(i));
        printf("     "); if (-1 == s.parent(i)) p("^"); else p(s.vertex(s.parent(i)));
        printf("  "); if (INT_MAX > s.priority(i)) p(s.priority(i)); else p(" INF");
        printf("\n");
    }
    printf("\n");
}
void p(VStatus& e)
{
        switch (e)
        {
        case UNDISCOVERED:   printf("U"); break;
        case DISCOVERED:     printf("D"); break;
        case VISITED:        printf("V"); break;
        default:             printf("X"); break;
        }
}
void p(EType& e)
{
    switch (e)
    {
    case UNDETERMINED:   printf("U"); break;
    case TREE:           printf("T"); break;
    case CROSS:          printf("C"); break;
    case BACKWARD:       printf("B"); break;
    case FORWARD:        printf("F"); break;
    default:             printf("X"); break;
    }
}

