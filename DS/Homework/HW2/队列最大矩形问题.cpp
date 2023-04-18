#define DSA_STACK_VECTOR //ʹ�û���������ջ
#include<cstdio>//����cģʽ��ȷ�������������
#include<iostream>//���ñ�׼���������
#include"../../Stack/Stack.h"//����ջ
#include"../../Queue/Queue.h" // ���ö���

using namespace std;

const int MAXN = 1000;

int findMax_STACK(int H[], int n, int& r, int& s, int& t); //����һ��ջ��O(n)
int findMax_STACKS(int H[], int n, int& r, int& s, int& t); //��������ջ��O(n)
int findMax_Queue(int H[], int n, int& r, int& s, int& t); //����һ�����У�O(n)��ʱ�㲻����

int main() 
{
    int* H; int n = 0;
    for (int j = 0; j < 10; j++)//����10�����ݼ��
    {
        H = new int[1 + (n = rand() % 106)];//�������
        cout << "[ ";
        for (int i = 0; i < n; i++)
        { 
            H[i] = rand() % 104;
            cout << H[i] << " ";
        }
        cout << "]" << endl;
        int r, s, t; //�����Σ�H[r] x [s, t)��rΪ����������С�������
        int findMaxByStack = findMax_STACK(H, n, r = -1, s = -1, t = -1);
        printf("\n��һ��ջ�ҵ���������Ϊ��%d = %d �� [%d,%d)\n", findMaxByStack, H[r], s, t);
        int findMaxByStacks = findMax_STACKS(H, n, r = -1, s = -1, t = -1);
        printf("������ջ�ҵ���������Ϊ��%d = %d �� [%d,%d)\n\n", findMaxByStacks, H[r], s, t);
        delete[] H;
    }
    return 0;
}

int findMax_STACK(int H[], int n, int& r, int& s, int& t) //H[]�ԷǸ�
{
    Stack<int> SR; //��ջ����ջ������s[r]-1��r����ǰ��t = t[r]
    int maxRect = 0;
    for (int t1 = 0; t1 <= n; t1++)//���������tΪ�ұ߽��
    { 
        while (!SR.empty() && (t1 == n || H[SR.top()] > H[t1]))//ÿһ���������
        { 
            int r1 = SR.pop(), s1 = SR.empty() ? 0 : SR.top() + 1;
            int mR = H[r1] * (t1 - s1);
            if (maxRect < mR)
            {
                maxRect = mR; r = r1; s = s1; t = t1;
            }
        }
        if (t1 < n) SR.push(t1); //ջ��ֻ��¼���е�H[s] = min{ H[k] | s <= k <= t }
    } //assert: SR is empty at exit
    return maxRect;
} //ÿ���ջ����ջ���������Σ��ۼƳɱ�O(n)

int findMax_STACKS(int H[], int n, int& r, int& s, int& t)//��ĩ��-1�ڱ���H[]�ԷǸ�
{ 
    int* s1 = new int[n]; Stack<int> S; //���ҿɼ������
    for (int r1 = 0; r1 < n; r1++)//���μ����
    { 
        while (!S.empty() && (H[S.top()] >= H[r1])) S.pop(); //ÿһ��s(r)
        s1[r1] = S.empty() ? 0 : 1 + S.top();
        S.push(r1);
    }
    while (!S.empty()) S.pop();

    int* t1 = new int[n]; Stack<int> T; //����ɼ������
    for (int r = n - 1; -1 != r; r--) { //���μ����
        while (!T.empty() && H[r] <= H[T.top()]) T.pop(); //ÿһ��t(r)
        t1[r] = T.empty() ? n : T.top();
        T.push(r);
    }
    while (!T.empty()) T.pop();

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
} //ÿ���ջ����ջ���������Σ��ۼƳɱ�O(n)
