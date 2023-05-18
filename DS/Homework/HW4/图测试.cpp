#define _CRT_SECURE_NO_WARNINGS 1
#include<cstdio>//引用c模式精确控制输入输出流
#include<iostream>//引用标准输入输出流
#include "../../Graph/GraphMatrix.h"

template <typename Tv, typename Te> //顶点类型、边类型
void randomGraph(GraphMatrix<Tv, Te>& g, Rank n, Rank e);
void p(GraphMatrix<char, int>& s);
void p(VStatus& e);
void p(EType& e);

int main()//图测试
{
    Rank n = 20, e = 20;
    srand((unsigned int)time(NULL)); //随机种子
    GraphMatrix<char, int> g;
    randomGraph<char, int>(g, n, e); //顶点以字符编号，边为整数权重
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

template <typename Tv, typename Te> //顶点类型、边类型
void randomGraph(GraphMatrix<Tv, Te>& g, Rank n, Rank e)//生成由v个顶点、e条边构成的随机图0 < e(e-1) <= v
{
    while ((g.n < n) || (g.e < e)) //随机测试
    {
        if (g.n < n) //顶点
        {
            if (rand() % 100 < 65) //65%概率插入顶点
            {
                Tv vertex = (Tv)('A' + rand() % 26);
                g.insert(vertex);
            }
            else//35%概率删除顶点
            {
                if (1 > g.n) continue;
                int v = rand() % g.n;
                Tv x = g.remove(v);
            }
        }
        if ((1 < g.n) && (g.e < e)) //边
        {
            if (rand() % 100 < 65) //65%概率插入边
            {
                int v = rand() % g.n, j = rand() % g.n; Te e = rand() % ((Te)3 * n);
                if (!g.exists(v, j))
                {
                    g.insert(e, e, v, j);
                }
            }
            else //35%概率删除边
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
    // 标题行（续）
    p(outD); printf(" "); p(s.e); printf("|");
    for (Rank i = 0; i < s.n; i++) { p(s.inDegree(i)); printf(" "); }
    printf("|\n");
    // 水平分隔线
    printf("-----------+"); for (Rank i = 0; i < s.n; i++) printf("------");
    printf("+----------------------------\n");
    // 逐行输出各顶点
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

