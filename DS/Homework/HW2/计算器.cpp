#define DSA_STACK_VECTOR //使用基于向量的栈
#include<ctime>//引用时间类头文件
#include<iostream>//引用标准输入输出流
#include"../HW1/Complex.h"//引用复数类
#include"计算器.h"//引用计算器类头文件

using namespace std;
const int MAXN = 1000;

int main() //表达式计算器
{
    cout << "欢迎使用RickJingDG牌计算器，本版本将会在计算1000条等式后自动关闭，\n若表达式中出现语法错误，算数错误，不符合规范错误，则也会自动关闭，请务必按规范使用哦（～￣▽￣～）；" << endl;
    cout << "本版本规定所有表达式括号均用英文/半角小括号即“(”与“）”，且括号必须成对出现，其它符号如右“+”“-”“*”“/”“!”" << endl;
    cout << "本版本最小误差设定为10的-10次方，即运算中若出现数量级小于等于此级别的数将有可能出现不可预知的错误；" << endl;
    cout << "本版本支持基本四则运算，以及基本的复数运算（包括加减乘除，以及复指数运算（计算主值））；\n其中负数-x需要用“(0-x)”来表示，复数xi虚部的x一定不能省略即需要表示为“xi”；\n例如需要表示（1+i）i，则需写为“(1+1i)*1i”，未来可能会加入更多功能，敬请期待；" << endl;
    cout << "下面请开始输入表达式，输完后按回车继续：" << endl;
    cout << endl;
    for (int i = 0; i < MAXN; i++)  //逐一处理各表达式
    {
        char expression[MAXN][MAXN] = {};
        cin.get(expression[i], MAXN);//读取带空格的字符串
        getchar();
        Complex value = evaluate(removeSpace(expression[i])); //求值
        if (abs(value.real()) >= Epslion)
        {
            if (value.imag() > Epslion)
            {
                printf("计算结果如下：\n%s = %.3lf+%.3lfi \n", expression[i], value.real(), value.imag()); //输出表达式的值，实部大于0，虚部不为0
            }
            else if (abs(value.imag()) < Epslion)
            {
                printf("计算结果如下：\n%s = %.3lf \n", expression[i], value.real()); //输出表达式的值虚部为0
            }
            else
            {
                printf("计算结果如下：\n%s = %.3lf%.3lfi\n", expression[i], value.real(), value.imag()); //输出表达式的值，实部小于0，虚部不为0
            }
        }
        else if (abs(value.imag()) >= Epslion)
        {
            printf("计算结果如下：\n%s = %.3lfi \n", expression[i], value.imag()); //输出表达式的值实部为0
        }
        else
        {
            printf("计算结果如下：\n%s = 0 \n", expression[i]); //输出表达式的值为0
        }
        cout << endl;
        cout << "请输入第" << i + 2 << "个表达式" << endl;
        cout << endl;
    }
    return 0;
}

char* removeSpace(char* s) //剔除s[]中的白空格
{
    for (char* p = s - 1, *q = s; (p < s) || *p; *++p = *q++)
        while (isspace(*q)) q++;
    return s;
}

void readNumber(char*& p, Stack<Complex>& stk) //将起始于p的子串解析为数值，并存入操作数栈
{
    stk.push((Complex)(*p - '0')); //当前数位对应的数值进栈
    while (isdigit(*(++p))) //若有后续数字（多位整数），则
    {
        stk.push(stk.pop() * (double)10 + (Complex)(*p - '0')); //追加（可能上溢）
    }
    if ('.' == *p) //若还有小数部分
    {
        double fraction = 1; //则
        while (isdigit(*(++p))) //逐位
        {
            stk.push(stk.pop() + (*p - '0') * (fraction /= 10)); //加入（可能下溢）
        }
    }
    if ('i' == *p)//如果是复数
    {
        Complex a;
        a.write_Complex(0.0, stk.pop());
        stk.push(a);
        ++p;
    }
}

Operator optr2rank(char op) //由运算符转译出编号
{ 
    switch (op)
    {
    case '+': return ADD; //加
    case '-': return SUB; //减
    case '*': return MUL; //乘
    case '/': return DIV; //除
    case '^': return POW; //乘方
    case '!': return FAC; //阶乘
    case '(': return L_P; //左括号
    case ')': return R_P; //右括号
    case '\0': return EOE; //起始符与终止符
    default: cout << "叫你不按规范使用，出错了吧，按任意键退出吧，拜拜<（￣︶￣）/" << endl; exit(-1); //未知运算符
    }
}

char priority(char op1, char op2) //比较两个运算符之间的优先级
{
    return pri[optr2rank(op1)][optr2rank(op2)];
}

Complex calcu(Complex a, char op, Complex b)//执行二元运算
{
    switch (op)
    {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': if (abs(b) < Epslion) exit(-1); return a / b; //通过Epslion，判断浮点数为零
    case '^':
        if (a.real() < 0)//如果实部小于0，调用复数类指数运算法则
        {
            return pow(a, b, false);
        }
        else
        {
            return pow(a, b);
        }
    default: cout << "叫你不按规范使用，出错了吧，按任意键退出吧，拜拜<（￣︶￣）/" << endl; exit(-1);
    }
}

Complex calcu(char op, Complex b) //执行一元运算
{
    switch (op)
    {
    case '!': return (Complex)facI((int)b); //目前仅有阶乘，可照此方式添加
    default: cout << "叫你不按规范使用，出错了吧，按任意键退出吧，拜拜<（￣︶￣）/" << endl; exit(-1);
    }
}

long long facI(int n) { long long f = 1; while (n > 1) f *= n--; return f; } //阶乘运算，迭代法

Complex evaluate(char* S) //对（已剔除白空格的）表达式S求值
{
    Stack<Complex> opnd; Stack<char> optr; //运算数栈、运算符栈
    optr.push('\0'); //尾哨兵'\0'也作为头哨兵首先入栈
    while (!optr.empty())//在运算符栈非空之前，逐个处理表达式中各字符
    {
        if (isdigit(*S))//若当前字符为操作数，则
        {
            readNumber(S, opnd);; //读入操作数
        }
        else //若当前字符为运算符，则
        {
            switch (priority(optr.top(), *S)) //视其与栈顶运算符之间优先级高低分别处理
            {
            case '<': //栈顶运算符优先级更低时
                optr.push(*S); S++; //计算推迟，当前运算符进栈
                break;
            case '=': //优先级相等（当前运算符为右括号或者尾部哨兵'\0'）时
                optr.pop(); S++; //脱括号并接收下一个字符
                break;
            case '>': //栈顶运算符优先级更高时，可实施相应的计算，并将结果重新入栈
            {
                char op = optr.pop();//栈顶运算符出栈
                if ('!' == op) //若属于一元运算符
                {
                    opnd.push(calcu(op, opnd.pop())); //则取一个操作数，计算结果入栈
                }
                else //对于其它（二元）运算符
                {
                    Complex opnd2 = opnd.pop(), opnd1 = opnd.pop(); //取出后、前操作数
                    opnd.push(calcu(opnd1, op, opnd2)); //实施二元计算，结果入栈
                }
                break;
            }
            default: cout << "叫你不按规范使用，出错了吧，按任意键退出吧，拜拜<（￣︶￣）/" << endl; exit(-1); //逢语法错误，不做处理直接退出
            }//switch
        }
    }//while
    return opnd.pop(); //弹出并返回最后的计算结果
}
