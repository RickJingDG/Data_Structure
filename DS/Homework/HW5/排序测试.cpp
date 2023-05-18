#include<ctime>//����ʱ����ͷ�ļ�
#include<iostream>
#include"../../Vector/Vector.h"

using namespace std;
const int MAXN = 6000;

int main()
{
	int A[MAXN];
	clock_t start = {}, end = {};//����ʱ����
	double bubbleSortTime = 0, selectionSortTime=0,mergeSortTime = 0, heapSortTime=0, quickSortTime=0, insertionSortTime=0;//��Ÿ�������ʱ
	int N1 =5000,s=0;
	cout << "�������ǻ������������򣬽�������5000�����ݵ��������ڲ���;\n��ѡ���Ƿ�������������飨1Ϊ�ǣ�0Ϊ�񣩣������س�����\n";
	cin >> s;
	cout << "����5000�����ݵ������� "<< endl;
	int N = MAXN-N1;
	//����������� 
	for (int j = 0; j < MAXN - N; j++)
	{
		A[j] = rand() % 3000;
		cout << A[j] << " ";
	}
	cout << endl;
	Vector<int>v(A, MAXN-N);
	Vector<int>b, c,d;
	b = v;
	//����
	cout << endl;
	int n=0;
	n = v.disordered();//��¼������
	cout << "������n = " << n << "������������δ����" << endl;

	cout << "����Ϊ����ĸ�������ʱ��" << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(),1);//����������1��ʾ��������
	end = clock();//����������е�ʱ��
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << bubbleSortTime*1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;

	//��������
	c = v;//��¼��������
	d = v;
	v = b;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 2);//����������2��ʾѡ������
	end = clock();//����������е�ʱ��
	selectionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "ѡ��������ʱ��" << selectionSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��������
	v = b;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 3);//����������3��ʾ�鲢����
	end = clock();//����������е�ʱ��
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "�鲢������ʱ��" << mergeSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;
		
	cout << endl;
	//��������
	v = b;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 4);//����������4��ʾ������
	end = clock();//����������е�ʱ��
	heapSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "��������ʱ��" << heapSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��������
	v = b;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 5);//����������5��ʾ��������
	end = clock();//����������е�ʱ��
	quickSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << quickSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��������
	v = b;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 6);//����������6��ʾ��������
	end = clock();//����������е�ʱ��
	insertionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << insertionSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	
	for (int j = 0; j < d.size(); j++)
	{
		d[j] = c[c.size()-1 - j];
	}
	//�󲿷��������
	c[500] = 25;
	v = c;
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "��������������󲿷�����" << endl;

	cout << "����Ϊ���󲿷�����ĸ�������ʱ��" << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 1);//����������1��ʾ��������
	end = clock();//����������е�ʱ��
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << bubbleSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = c;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 2);//����������2��ʾѡ������
	end = clock();//����������е�ʱ��
	selectionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "ѡ��������ʱ��" << selectionSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = c;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 3);//����������3��ʾ�鲢����
	end = clock();//����������е�ʱ��
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "�鲢������ʱ��" << mergeSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = c;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 4);//����������4��ʾ������
	end = clock();//����������е�ʱ��
	heapSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "��������ʱ��" << heapSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = c;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 5);//����������5��ʾ��������
	end = clock();//����������е�ʱ��
	quickSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << quickSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = c;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 6);//����������6��ʾ��������
	end = clock();//����������е�ʱ��
	insertionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << insertionSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	v = d;
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������Ϊ����" << endl;
	cout << "����Ϊ����ĸ�������ʱ��" << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 1);//����������1��ʾ��������
	end = clock();//����������е�ʱ��
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << bubbleSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = d;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 2);//����������2��ʾѡ������
	end = clock();//����������е�ʱ��
	selectionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "ѡ��������ʱ��" << selectionSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = d;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 3);//����������3��ʾ�鲢����
	end = clock();//����������е�ʱ��
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "�鲢������ʱ��" << mergeSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = d;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 4);//����������4��ʾ������
	end = clock();//����������е�ʱ��
	heapSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "��������ʱ��" << heapSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = d;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 5);//����������5��ʾ��������
	end = clock();//����������е�ʱ��
	quickSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << quickSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	cout << endl;
	//��λ
	v = d;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 6);//����������6��ʾ��������
	end = clock();//����������е�ʱ��
	insertionSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << insertionSortTime * 1000 << "���룬���Ϊ��" << endl;
	for (int j = 0; j < v.size() && s != 0; j++)
	{
		cout << v[j] << " ";
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "������������������" << endl;

	return 0;
}