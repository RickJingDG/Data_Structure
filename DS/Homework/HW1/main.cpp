#include<ctime>//����ʱ����ͷ�ļ�
#include<iostream>
#include"Complex.h"
#include"../../Vector/Vector.h"

using namespace std;
const int MAXN = 1000;

Vector<Complex> partModulusSearch(Vector<Complex>const& V, double m1, double m2)
{
	Complex M1, M2;
	M1.write_Imaginary(m1);//��ʵ�������鲿���ģ�����ڵ��ڵ�Ч��
	M1.write_Real(0.0); //��Ϊ��ģ�����ʱ��Ƚ�ʵ�������轫m1����ʵ������ģ����Ⱥ����ڴ����鲿����ʵ����С��m1ʹ�ñ��ų����⡣
	M1.write_modulus();//��m1�����鲿�Ͳ������������
	M1.write_arg();
	M2.write_Imaginary(m2);//ͬ��
	M2.write_Real(0.0);//��Ϊģ�����ʱ�����轫m1��ʵ������ʹ�ô����鲿��ʹʵ��С��m1������������С�ڵķ�Χ��
	M2.write_modulus();
	M2.write_arg();//����˵����ȫ���鲿��������ҿ����䣬ȫ��ʵ���������ұ�����
	Rank a = V.search(M1) + 1, b = V.search(M2) + 1;//search����ֵ�ǲ���������Ҫ���m1,m2�����ֵ�������Ҫ��һ
	Vector<Complex> Result(V, a, b);
	return Result;
}

int main()//RickJing˵�����������ص��лһ��yyhgdx��Ǯͬѧ�����Ҵ���Ķ���֧�ֺ���˽������
{
	Complex A[MAXN];//���帴����
	clock_t start = {}, end = {};//����ʱ����
	double bubbleSortTime = 0, mergeSortTime = 0;//�����������ʱ��͹鲢����ʱ��
	int N1 = 0;
	cout << "���㷨Ŀǰ����ܴ���312������������312�����δ֪����Ŀǰ�汾�޷������\n������������10~317֮���������Ϊ��ɾȥ5������������300���ҵ������������㷨���ܲŻ���ϸ΢���\n�������������ɵ��������������س�������" << endl;
	cin >> N1;
	int N = MAXN-N1;
	cout << "���ɵĸ�������������" << endl;
	//���ɸ���������� 
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

	//����
	cout << endl;
	v.unsort();
	cout << "���Һ�" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
	}
	cout << endl;

	//����
	cout << endl;
	int b[MAXN] = {};
	cout << "��������ǰÿһ�������������Һ����������λ��Ϊ��" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		b[j] = v.find(A[j]);
		A[j].display();
		cout << "��" << b[j] + 1 << "λ" << endl;
	}

	//����
	cout << endl;
	for (int j = 0; j < 10; j++)
	{
		v.insert(rand() % (10 + j), A[rand() % (10)]);
	}
	cout << "�������λ�ò���10�������� �µĸ���������" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)
		{
			cout << endl;
		}
	}

	//ɾ��
	cout << endl;
	v.remove(4, 9);
	cout << "ɾ������[4��9)���µ�������" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;

	//Ψһ������
	cout << endl;
	cout << "Ψһ���������µ�������" << endl;
	v.deduplicate();
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}

	cout << endl;
	int n=0;
	n = v.disordered();//��¼������
	cout << "������n = " << n << "����������������δ����" << endl;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(),1);//����������1��ʾ��������
	end = clock();//����������е�ʱ��
	bubbleSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "����������ʱ��" << bubbleSortTime << "�룬���Ϊ��" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "����������������������" << endl;

	cout << endl;
	//��������
	v.unsort();
	cout << "�������Һ�" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
	}
	n = v.disordered();//��¼������
	cout << endl;
	cout << "������n = " << n << "��������������������" << endl;

	cout << endl;
	start = clock();//����ʼ���е�ʱ��
	v.sort(0, v.size(), 3);//����������1��ʾ��������
	end = clock();//����������е�ʱ��
	mergeSortTime = (double(end - start)) / CLOCKS_PER_SEC;
	cout << "�鲢������ʱ��" << mergeSortTime << "�룬���Ϊ��" << endl;
	for (int j = 0; j < v.size(); j++)
	{
		v[j].display();
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	n = v.disordered();//�ٴβ鿴������	
	cout << "n = " << n << "����������������������" << endl;
	
	cout << endl;
	double m1 = 0, m2 = 0;//������ҵ�����
	cout << "��������ҵ�ģ������[m1,m2)��������m1��m2���ɣ��ÿո���������س�������:";
	cin >> m1 >> m2;
	Vector<Complex> Finded;
	Finded = partModulusSearch(v, m1, m2);
	for (int j = 0; j < Finded.size(); j++)
	{
		Finded[j].display();
		if (j % 10 == 9)//ʮ����ʾһ��
		{
			cout << endl;
		}
	}
	cout << endl;
	return 0;
}