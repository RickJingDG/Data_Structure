#define DSA_STACK_VECTOR //ʹ�û���������ջ
#include<ctime>//����ʱ����ͷ�ļ�
#include<iostream>//���ñ�׼���������
#include"../HW1/Complex.h"//���ø�����
#include"������.h"//����ջ

using namespace std;
const int MAXN = 1000;

int main() //���ʽ������
{
    cout << "��ӭʹ��RickJingDG�Ƽ����������汾�����ڼ���1000����ʽ���Զ��رգ�\n�����ʽ�г����﷨�����������󣬲����Ϲ淶������Ҳ���Զ��رգ�����ذ��淶ʹ��Ŷ����������������" << endl;
    cout << "���汾�涨���б��ʽ���ž���Ӣ��/���С���ż���(���롰�����������ű���ɶԳ��֣������������ҡ�+����-����*����/����!��" << endl;
    cout << "���汾��С����趨Ϊ10��-10�η�����������������������С�ڵ��ڴ˼���������п��ܳ��ֲ���Ԥ֪�Ĵ���" << endl;
    cout << "���汾֧�ֻ����������㣬���и���-x��Ҫ�á�(0-x)������ʾ��δ�����ܻ������๦�ܣ������ڴ���" << endl;
    cout << "�����뿪ʼ������ʽ������󰴻س�������" << endl;
    cout << endl;
    for (int i = 0; i < MAXN; i++)  //��һ��������ʽ
    {
        char expression[MAXN][MAXN] = {};
        cin.get(expression[i], MAXN);//��ȡ���ո���ַ���
        getchar();
        double value = evaluate(removeSpace(expression[i])); //��ֵ
        printf("���������£�\n%s = %.4f \n", expression[i], value); //������ʽ��ֵ
        cout << endl;
        cout << "�������" << i + 2 << "�����ʽ" << endl;
        cout << endl;
    }
    return 0;
}

char* removeSpace(char* s) //�޳�s[]�еİ׿ո�
{
    for (char* p = s - 1, *q = s; (p < s) || *p; *++p = *q++)
        while (isspace(*q)) q++;
    return s;
}

Vector<Complex> partModulusSearch(Vector<Complex>const& V, double m1, double m2)//�������������еĲ���
{
	Complex M1, M2;
    M1.write_Complex(0.0, m1);//��ʵ�������鲿���ģ�����ڵ��ڵ�Ч��
    //��Ϊ��ģ�����ʱ��Ƚ�ʵ�������轫m1����ʵ������ģ����Ⱥ����ڴ����鲿����ʵ����С��m1ʹ�ñ��ų����⡣
    //��m1�����鲿�Ͳ������������
    M2.write_Complex(0.0, m2);//ͬ��
    //��Ϊģ�����ʱ�����轫m1��ʵ������ʹ�ô����鲿��ʹʵ��С��m1������������С�ڵķ�Χ��
    //����˵����ȫ���鲿��������ҿ����䣬ȫ��ʵ���������ұ�����
    Rank a = V.search(M1) + 1, b = V.search(M2) + 1;//search����ֵ�ǲ���������Ҫ���m1,m2�����ֵ�������Ҫ��һ
	Vector<Complex> Result(V, a, b);
	return Result;
}

void readNumber(char*& p, Stack<double>& stk) //����ʼ��p���Ӵ�����Ϊ��ֵ�������������ջ
{
    stk.push((double)(*p - '0')); //��ǰ��λ��Ӧ����ֵ��ջ
    while (isdigit(*(++p))) //���к������֣���λ����������
    {
        stk.push(stk.pop() * 10 + (*p - '0')); //׷�ӣ��������磩
    }
    if ('.' == *p) //������С������
    {
        double fraction = 1; //��
        while (isdigit(*(++p))) //��λ
        {
            stk.push(stk.pop() + (*p - '0') * (fraction /= 10)); //���루�������磩
        }
    }
}

Operator optr2rank(char op) //�������ת������
{ 
    switch (op)
    {
    case '+': return ADD; //��
    case '-': return SUB; //��
    case '*': return MUL; //��
    case '/': return DIV; //��
    case '^': return POW; //�˷�
    case '!': return FAC; //�׳�
    case '(': return L_P; //������
    case ')': return R_P; //������
    case '\0': return EOE; //��ʼ������ֹ��
    default: cout << "���㲻���淶ʹ�ã������˰ɣ���������˳��ɣ��ݰ�<���������/" << endl; exit(-1); //δ֪�����
    }
}

char priority(char op1, char op2) //�Ƚ����������֮������ȼ�
{
    return pri[optr2rank(op1)][optr2rank(op2)];
}

double calcu(double a, char op, double b)//ִ�ж�Ԫ����
{ 
    switch (op)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': if (abs(b)<Epslion ) exit(-1); return a / b; //ͨ��Epslion���жϸ�����Ϊ��
    case '^': return pow(a, b);
    default: cout << "���㲻���淶ʹ�ã������˰ɣ���������˳��ɣ��ݰ�<���������/" << endl; exit(-1);
    }
}

double calcu(char op, double b) //ִ��һԪ����
{
    switch (op)
    {
    case '!': return (double)facI((int)b); //Ŀǰ���н׳ˣ����մ˷�ʽ���
    default: cout << "���㲻���淶ʹ�ã������˰ɣ���������˳��ɣ��ݰ�<���������/" << endl; exit(-1);
    }
}

long long facI(int n) { long long f = 1; while (n > 1) f *= n--; return f; } //�׳����㣬������

double evaluate(char* S) //�ԣ����޳��׿ո�ģ����ʽS��ֵ
{
    Stack<double> opnd; Stack<char> optr; //������ջ�������ջ
    optr.push('\0'); //β�ڱ�'\0'Ҳ��Ϊͷ�ڱ�������ջ
    while (!optr.empty())//�������ջ�ǿ�֮ǰ�����������ʽ�и��ַ�
    {
        if (isdigit(*S))//����ǰ�ַ�Ϊ����������
        {
            readNumber(S, opnd);; //���������
        }
        else //����ǰ�ַ�Ϊ���������
        {
            switch (priority(optr.top(), *S)) //������ջ�������֮�����ȼ��ߵͷֱ���
            {
            case '<': //ջ����������ȼ�����ʱ
                optr.push(*S); S++; //�����Ƴ٣���ǰ�������ջ
                break;
            case '=': //���ȼ���ȣ���ǰ�����Ϊ�����Ż���β���ڱ�'\0'��ʱ
                optr.pop(); S++; //�����Ų�������һ���ַ�
                break;
            case '>': //ջ����������ȼ�����ʱ����ʵʩ��Ӧ�ļ��㣬�������������ջ
            {
                char op = optr.pop();//ջ���������ջ
                if ('!' == op) //������һԪ�����
                {
                    opnd.push(calcu(op, opnd.pop())); //��ȡһ������������������ջ
                }
                else //������������Ԫ�������
                {
                    double opnd2 = opnd.pop(), opnd1 = opnd.pop(); //ȡ����ǰ������
                    opnd.push(calcu(opnd1, op, opnd2)); //ʵʩ��Ԫ���㣬�����ջ
                }
                break;
            }
            default: cout << "���㲻���淶ʹ�ã������˰ɣ���������˳��ɣ��ݰ�<���������/" << endl; exit(-1); //���﷨���󣬲�������ֱ���˳�
            }//switch
        }
    }//while
    return opnd.pop(); //�������������ļ�����
}
