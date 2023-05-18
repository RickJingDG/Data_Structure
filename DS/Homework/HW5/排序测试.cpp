#include<ctime>//引用时间类头文件
#include<iostream>
#include"../../Vector/Vector.h"

using namespace std;
const int MAXN = 6000;

int main()
{
	int A[MAXN];
	clock_t start = {}, end = {};//定义时间类
	double bubbleSortTime = 0, selectionSortTime=0,mergeSortTime = 0, heapSortTime=0, quickSortTime=0, insertionSortTime=0;//存放各排序用时
	int N1 =5000,s=0;
	cout << "本程序是基于向量的排序，将会生成5000个数据的向量用于测试;\n请选择是否输出排序后的数组（1为是，0为否），并按回车继续\n";
	cin >> s;
	cout << "生成5000个数据的向量： "<< endl;
	int N = MAXN-N1;
	//生成类的数组 
	for (int j = 0; j < MAXN - N; j++)
	{
		A[j] = rand() % 3000;
		cout << A[j] << " ";
	}
	cout << endl;
	Vector<int>v(A, MAXN-N);
	Vector<int>b, c,d;
	b = v;
	//插入
	cout << endl;
	int n=0;
	n = v.disordered();//记录逆序数
	cout << "逆序数n = " << n << "，表明向量组未排完" << endl;

	cout << "以下为乱序的各排序用时：" << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(),1);//第三个参数1表示起泡排序
	end = clock();//排序结束运行的时刻
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "起泡排序用时：" << bubbleSortTime*1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;

	//重新置乱
	c = v;//记录有序结果。
	d = v;
	v = b;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 2);//第三个参数2表示选择排序
	end = clock();//排序结束运行的时刻
	selectionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "选择排序用时：" << selectionSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//重新置乱
	v = b;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 3);//第三个参数3表示归并排序
	end = clock();//排序结束运行的时刻
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "归并排序用时：" << mergeSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;
		
	cout << endl;
	//重新置乱
	v = b;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 4);//第三个参数4表示堆排序
	end = clock();//排序结束运行的时刻
	heapSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "堆排序用时：" << heapSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//重新置乱
	v = b;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 5);//第三个参数5表示快速排序
	end = clock();//排序结束运行的时刻
	quickSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "快速排序用时：" << quickSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//重新置乱
	v = b;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 6);//第三个参数6表示插入排序
	end = clock();//排序结束运行的时刻
	insertionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "插入排序用时：" << insertionSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	
	for (int j = 0; j < d.size(); j++)
	{
		d[j] = c[c.size()-1 - j];
	}
	//大部分有序情况
	c[500] = 25;
	v = c;
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组绝大部分有序" << endl;

	cout << "以下为绝大部分有序的各排序用时：" << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 1);//第三个参数1表示起泡排序
	end = clock();//排序结束运行的时刻
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "起泡排序用时：" << bubbleSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = c;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 2);//第三个参数2表示选择排序
	end = clock();//排序结束运行的时刻
	selectionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "选择排序用时：" << selectionSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = c;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 3);//第三个参数3表示归并排序
	end = clock();//排序结束运行的时刻
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "归并排序用时：" << mergeSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = c;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 4);//第三个参数4表示堆排序
	end = clock();//排序结束运行的时刻
	heapSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "堆排序用时：" << heapSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = c;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 5);//第三个参数5表示快速排序
	end = clock();//排序结束运行的时刻
	quickSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "快速排序用时：" << quickSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = c;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 6);//第三个参数6表示插入排序
	end = clock();//排序结束运行的时刻
	insertionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "插入排序用时：" << insertionSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	v = d;
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组为逆序" << endl;
	cout << "以下为逆序的各排序用时：" << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 1);//第三个参数1表示起泡排序
	end = clock();//排序结束运行的时刻
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "起泡排序用时：" << bubbleSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = d;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 2);//第三个参数2表示选择排序
	end = clock();//排序结束运行的时刻
	selectionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "选择排序用时：" << selectionSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = d;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 3);//第三个参数3表示归并排序
	end = clock();//排序结束运行的时刻
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "归并排序用时：" << mergeSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = d;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 4);//第三个参数4表示堆排序
	end = clock();//排序结束运行的时刻
	heapSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "堆排序用时：" << heapSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = d;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 5);//第三个参数5表示快速排序
	end = clock();//排序结束运行的时刻
	quickSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "快速排序用时：" << quickSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	cout << endl;
	//归位
	v = d;

	cout << endl;
	start = clock();//排序开始运行的时刻
	v.sort(0, v.size(), 6);//第三个参数6表示插入排序
	end = clock();//排序结束运行的时刻
	insertionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "插入排序用时：" << insertionSortTime * 1000 << "毫秒，结果为：" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//十个显示一行
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//再次查看逆序数	
	cout << "n = " << n << "，表明向量组已排完" << endl;

	return 0;
}