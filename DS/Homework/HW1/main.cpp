#include<ctime>//引用时间类头文件
#include<iostream>
#include"../../Vector/Vector.h"
#include"Complex.h"
using namespace std;
const int MAXN = 1000;
int main()//RickJing说明：在这里重点感谢一下yyhgdx（钱同学）对我代码的鼎力支持和无私帮助。
{
	Complex A[MAXN];//定义复数类
	clock_t start = {}, end = {};//定义时间类
	double bubbleSortTime = 0, mergeSortTime = 0;//存放起泡排序时间和归并排序时间
	int N1 = 0;
	cout << "该算法目前最大能处理312个向量，超过312会产生未知错误，目前版本无法解决；\n因此你可以输入10~317之间的数，因为会删去5个向量，下面请输入生成的向量数，并按回车继续：" << endl;
	cin >> N1;
	int N = MAXN-N1;
	cout << "生成的复数无序向量：" << endl;
	//生成复数类的数组 
	for (int j = 0; j < MAXN - N; j++)
	{
		A[j].write_Real(rand() % 200 / 10.0);
		A[j].write_Imaginary(rand() % 200 / 10.0);
		A[j].write_modulus();
		A[j].write_arg();
		A[j].display();
	}
	cout << endl;
	Vector<Complex>v(A, MAXN-N);

	//置乱
	cout << endl;
	v.unsort();
	cout << "置乱后：" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
	}
	cout << endl;

	//查找
	cout << endl;
	int b[MAXN] = {};
	cout << "查找置乱前每一个复数，在置乱后向量组里的位置为：" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		b[j] = v.find(A[j]);
		A[j].display();
		cout << "第" << b[j] + 1 << "位" << endl;
	}

	//插入
	cout << endl;
	for (int j = 0; j < 10; j++)
	{
		v.insert(rand() % (10 + j), A[rand() % (10)]);
	}
	cout << "生成随机位置插入10个复数后 新的复数向量：" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)
		{
			cout << endl;
		}
	}

	//删除
	cout << endl;
	v.remove(4, 9);
	cout << "删除区间[4，9)后新的向量：" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;

	//唯一化操作
	cout << endl;
	cout << "唯一化操作后新的向量：" << endl;
	v.deduplicate();
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}

	cout << endl;
	int n=0;
	n = v.disordered();//记录逆序数
	cout << "逆序数n = " << n << "，表明复数向量组未排完" << endl;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(),1);//第三个参数1表示起泡排序
	end = clock();//排序结束运行的时刻
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "起泡排序用时：" << bubbleSortTime << "秒，结果为：" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明复数向量组已排完" << endl;

	cout << endl;
	//重新置乱
	v.unsort();
	cout << "重新置乱后：" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
	}
	n = v.disordered();//记录逆序数
	cout << endl;
	cout << "逆序数n = " << n << "，表明复数向量组乱序" << endl;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 3);//第三个参数1表示起泡排序
	end = clock();//排序结束运行的时刻
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "归并排序用时：" << mergeSortTime << "秒，结果为：" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明复数向量组已排完" << endl;
	return 0;
}