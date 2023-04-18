#define DSA_STACK_VECTOR //ʹ�û���������ջ
#include<ctime>//����ʱ����ͷ�ļ�
#include<iostream>//���ñ�׼���������
#include"../HW1/Complex.h"//���ø�����
#include"������.h"//���ü�������ͷ�ļ�

using namespace std;
const int MAXN = 1000;

int main() //���ʽ������
{
    cout << "��ӭʹ��RickJingDG�Ƽ����������汾�����ڼ���1000����ʽ���Զ��رգ�\n�����ʽ�г����﷨�����������󣬲����Ϲ淶������Ҳ���Զ��رգ�����ذ��淶ʹ��Ŷ����������������" << endl;
    cout << "���汾�涨���б��ʽ���ž���Ӣ��/���С���ż���(���롰�����������ű���ɶԳ��֣������������ҡ�+����-����*����/����!��" << endl;
    cout << "���汾��С����趨Ϊ10��-10�η�����������������������С�ڵ��ڴ˼���������п��ܳ��ֲ���Ԥ֪�Ĵ���" << endl;
    cout << "���汾֧�ֻ����������㣬�Լ������ĸ������㣨�����Ӽ��˳����Լ���ָ�����㣨������ֵ������\n���и���-x��Ҫ�á�(0-x)������ʾ������xi�鲿��xһ������ʡ�Լ���Ҫ��ʾΪ��xi����\n������Ҫ��ʾ��1+i��i������дΪ��(1+1i)*1i����δ�����ܻ������๦�ܣ������ڴ���" << endl;
    cout << "�����뿪ʼ������ʽ������󰴻س�������" << endl;
    cout << endl;
    for (int i = 0; i < MAXN; i++)  //��һ��������ʽ
    {
        char expression[MAXN][MAXN] = {};
        cin.get(expression[i], MAXN);//��ȡ���ո���ַ���
        getchar();
        Complex value = evaluate(removeSpace(expression[i])); //��ֵ
        if (abs(value.real()) >= Epslion)
        {
            if (value.imag() > Epslion)
            {
                printf("���������£�\n%s = %.3lf+%.3lfi \n", expression[i], value.real(), value.imag()); //������ʽ��ֵ��ʵ������0���鲿��Ϊ0
            }
            else if (abs(value.imag()) < Epslion)
            {
                printf("���������£�\n%s = %.3lf \n", expression[i], value.real()); //������ʽ��ֵ�鲿Ϊ0
            }
            else
            {
                printf("���������£�\n%s = %.3lf%.3lfi\n", expression[i], value.real(), value.imag()); //������ʽ��ֵ��ʵ��С��0���鲿��Ϊ0
            }
        }
        else if (abs(value.imag()) >= Epslion)
        {
            printf("���������£�\n%s = %.3lfi \n", expression[i], value.imag()); //������ʽ��ֵʵ��Ϊ0
        }
        else
        {
            printf("���������£�\n%s = 0 \n", expression[i]); //������ʽ��ֵΪ0
        }
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

void readNumber(char*& p, Stack<Complex>& stk) //����ʼ��p���Ӵ�����Ϊ��ֵ�������������ջ
{
    stk.push((Complex)(*p - '0')); //��ǰ��λ��Ӧ����ֵ��ջ
    while (isdigit(*(++p))) //���к������֣���λ����������
    {
        stk.push(stk.pop() * (double)10 + (Complex)(*p - '0')); //׷�ӣ��������磩
    }
    if ('.' == *p) //������С������
    {
        double fraction = 1; //��
        while (isdigit(*(++p))) //��λ
        {
            stk.push(stk.pop() + (*p - '0') * (fraction /= 10)); //���루�������磩
        }
    }
    if ('i' == *p)//����Ǹ���
    {
        Complex a;
        a.write_Complex(0.0, stk.pop());
        stk.push(a);
        ++p;
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

Complex calcu(Complex a, char op, Complex b)//ִ�ж�Ԫ����
{
    switch (op)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': if (abs(b) < Epslion) exit(-1); return a / b; //ͨ��Epslion���жϸ�����Ϊ��
    case '^':
        if (a.real() < 0)//���ʵ��С��0�����ø�����ָ�����㷨��
        {
            return pow(a, b, false);
        }
        else
        {
            return pow(a, b);
        }
    default: cout << "���㲻���淶ʹ�ã������˰ɣ���������˳��ɣ��ݰ�<���������/" << endl; exit(-1);
    }
}

Complex calcu(char op, Complex b) //ִ��һԪ����
{
    switch (op)
    {
    case '!': return (Complex)facI((int)b); //Ŀǰ���н׳ˣ����մ˷�ʽ���
    default: cout << "���㲻���淶ʹ�ã������˰ɣ���������˳��ɣ��ݰ�<���������/" << endl; exit(-1);
    }
}

long long facI(int n) { long long f = 1; while (n > 1) f *= n--; return f; } //�׳����㣬������

Complex evaluate(char* S) //�ԣ����޳��׿ո�ģ����ʽS��ֵ
{
    Stack<Complex> opnd; Stack<char> optr; //������ջ�������ջ
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
                    Complex opnd2 = opnd.pop(), opnd1 = opnd.pop(); //ȡ����ǰ������
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
