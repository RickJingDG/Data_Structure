//#define DSA_STACK_VECTOR //使用基于向量的栈
#include<cstdio>//引用c模式精确控制输入输出流
#include<iostream>//引用标准输入输出流
#include"../../Stack/Stack.h"//引用栈
#include"../../Queue/Queue.h" // 引用队列

using namespace std;

const int MAXN = 1000;

int findMax_STACK(int H[], int n, int& r, int& s, int& t); //借助一个栈：O(n)
int findMax_STACKS(int H[], int n, int& r, int& s, int& t); //借助两个栈：O(n)
int findMax_Queue(int H[], int n, int& r, int& s, int& t); //借助一个队列：O(n)暂时搞不出来

int main() 
{
    int* H; int n = 0;
    for (int j = 0; j < 10; j++)//生成10组数据检测
    {
        H = new int[1 + (n = rand() % 106)];//随机生成
        cout << "[ ";
        for (int i = 0; i < n; i++)
        { 
            H[i] = rand() % 104;
            cout << H[i] << " ";
        }
        cout << "]" << endl;
        int r, s, t; //最大矩形：H[r] × [s, t)，r为最大矩形中最小那项的秩
        int findMaxByStack = findMax_STACK(H, n, r = -1, s = -1, t = -1);
        printf("\n用一个栈找到的最大矩形为：%d = %d × [%d,%d)\n", findMaxByStack, H[r], s, t);
        int findMaxByStacks = findMax_STACKS(H, n, r = -1, s = -1, t = -1);
        printf("用两个栈找到的最大矩形为：%d = %d × [%d,%d)\n\n", findMaxByStacks, H[r], s, t);
        delete[] H;
    }
    return 0;
}

int findMax_STACK(int H[], int n, int& r, int& s, int& t) //H[]皆非负
{
    Stack<int> STK; //次栈顶、栈顶总是s1[r1]-1与r1，当前的t1 = t1[r1]
    int maxRect = 0;
    for (int t1 = 0; t1 <= n; t1++)//逐个尝试以t为右边界的
    {
        while (!STK.empty() && (t1 == n || H[STK.top()] > H[t1]))//每一个极大矩形
        {
            int r1 = STK.pop(), s1 = STK.empty() ? 0 : STK.top() + 1;//第一次进入时r1为t1前一项，s1为r1
            int mR = H[r1] * (t1 - s1);
            if (maxRect < mR)
            {
                maxRect = mR; r = r1; s = s1; t = t1;
            }
        }
        if (t1 < n) STK.push(t1); //栈中只记录所有的H[s1] = min{ H[k] | s1 <= k <= t1 }
    } //assert: SR is empty at exit
    return maxRect;
}

int findMax_STACKS(int H[], int n, int& r, int& s, int& t)//除末项-1哨兵，H[]皆非负
{
    int* s1 = new int[n]; Stack<int> R; //自左向右可见项的秩
    for (int r1 = 0; r1 < n; r1++)//依次计算出
    {
        while (!R.empty() && (H[R.top()] >= H[r1])) R.pop(); //每一个s(r)
        s1[r1] = R.empty() ? 0 : 1 + R.top();
        R.push(r1);
    }
    while (!R.empty()) R.pop();

    int* t1 = new int[n]; Stack<int> L; //自右向左可见项的秩
    for (int r1 = n - 1; -1 != r1; r1--) //依次计算出
    { 
        while (!L.empty() && H[r1] <= H[L.top()]) L.pop(); //每一个t(r)
        t1[r1] = L.empty() ? n : L.top();
        L.push(r1);
    }
    while (!L.empty()) L.pop();

    int maxRect = 0;
    for (int r1 = 0; r1 < n; r1++)
    {
        int mR = H[r1] * (t1[r1] - s1[r1]);
        if (maxRect < mR)
        {
            maxRect = mR; r = r1; s = s1[r1]; t = t1[r1];
        }
    }
    delete[] s1; delete[] t1;
    return maxRect;
}
