#pragma once
#include "Vector.h"//����ģ����

template<typename T>
inline void Vector<T>::swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}

template <typename T>//ģ�����ƶ���
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];
	_size = 0;
	while (lo < hi)
	{
		_elem[_size++] = A[lo++];
	}
}

template<typename T>
void Vector<T>::expand()
{
	if (_size < _capacity)
	{
		return;//δ�� ������ 
	}
	if (_capacity < DEFAULT_CAPACITY)
	{
		_capacity = DEFAULT_CAPACITY; //��֤������ԭ�������� 
	}
	T* oldElem = _elem;
	_elem = new T[_capacity <<= long(1)];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[]oldElem;//�ͷ�ԭ�ռ� 
}

template<typename T>
void Vector<T>::shrink()
{
	if (_capacity < DEFAULT_CAPACITY << 1)
	{
		return;
	}
	if (_size << 2 > _capacity)
	{
		return;
	}
	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];
	for (int i = 0; i < _size; i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[]oldElem;
}

template<typename T>
bool Vector<T>::bubble(Rank lo, Rank hi)
{
	bool sorted = true;
	while (++lo < hi)
		if (_elem[lo - 1] > _elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);
		}
	return sorted;
}

template<typename T>
void Vector<T>::bubbleSort(Rank lo, Rank hi)
{
	while (!bubble(lo, hi--));
}

template<typename T>
Rank Vector<T>::max(Rank lo, Rank hi)//��[lo, hi]���ҳ������
{
	Rank max = lo;
	while (++lo < hi)
		if (_elem[lo] >= _elem[max])//ȡ�ȱ�֤�����ֵ��ͬ���������ȡ���һ��
		{
			max = lo;
		}
	return max;//�������ֵ����
}

template<typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) // 0 <= lo < hi <= size
{
	while (lo < --hi)
	{
		swap(_elem[max(lo, hi)], _elem[hi]); //��[hi]��[lo, hi]�е�����߽���
	}
}

template<typename T>//�Ը��������[lo, mi)��[mi, hi)���鲢
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)// lo < mi < hi
{//��mi Ϊ�磬���������������[lo,mi) [mi, hi)
	T* A = _elem + lo; //�ϲ��������A[0,hi-lo) = _elem[lo,hi)
	int lb = mi - lo;
	T* B = new T[lb];//ǰ������B[0,lb) = _elem[lo,mi)
	for (Rank i = 0; i < lb; B[i] = A[i++]);//����ǰ������,ֻ��ǰ����б�Ҫ���ƣ��б����ǵķ���
	int lc = hi - mi;
	T* C = _elem + mi;//ǰ������C[0,lc) = _elem[mi,hi)
	for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);)// ��B[j]��C[k]�е�С������A��ĩβ
	{
		if ((j < lb) && (!(k < lc) || B[j] <= C[k])) A[i++] = B[j++];
		if ((k < lc) && (!(j < lb) || C[k] < B[j])) A[i++] = C[k++];
	}
	delete[]B; //�ͷ���ʱ�ռ�B
}// �鲢��õ��������������� lo,hi


template<typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if (hi - lo < 2) return; //��Ԫ��������Ȼ����
	Rank mi = (lo + hi) / 2; //���е�Ϊ��
	mergeSort(lo, mi);
	mergeSort(mi, hi); //ǰ׺����׺�ֱ�����
	merge(lo, mi, hi); //�鲢
}

template<typename T>//RickJing˵�������㷨�����ҿ��ŵ���㣬��������ʹ�ã�������ԭ���Ǹ�����˲�������������Ǵ������ҵġ�
Rank Vector<T>::partition(Rank lo, Rank hi)// DUP�棺���Ż���������ؼ�����ͬ���˻����
{
	swap(_elem[lo], _elem[lo + rand() % (hi - lo)]); //��ѡһ��Ԫ������Ԫ�ؽ���
	T pivot = _elem[lo]; //�����Ͻ�������Ч�����ѡȡ��ѡ���
	while (lo < hi)//�����˽���ɨ�裬ֱ������
	{
		do hi--;
		while ((lo < hi) && (pivot < _elem[hi])); //������չ��׺G
		if (lo < hi)
		{
			_elem[lo] = _elem[hi];//�赲�߹���ǰ׺L
		} 
		do lo++;
		while ((lo < hi) && (_elem[lo] < pivot)); //������չǰ׺L
		if (lo < hi) 
		{
			_elem[hi] = _elem[lo]; //�赲�߹����׺G
		}
	} // assert: quit with lo == hi or hi + 1
	_elem[hi] = pivot; //��ѡ�������ǰ׺����׺֮�䣬����������ʵ
	return hi; //����������
}

template<typename T>
void Vector<T>::quickSort(Rank lo, Rank hi) // 0 <= lo < hi <= size
{
	if (hi - lo < 2) return; //��Ԫ��������Ȼ����
	Rank mi = partition(lo, hi); //��[lo, hi)�ڹ������
	quickSort(lo, mi); quickSort(mi + 1, hi); //ǰ׺����׺���Եݹ�����
}

template<typename T>//RickJing˵�������㷨���ڶ����򣬵�����ԭ�����˲�������������Ǵ������ҵģ����Ҳ�ȫ�棬������������档
void Vector<T>::heapSort(Rank lo, Rank hi)// 0 <= lo < hi <= size
{
	T* A = _elem + lo; 
	Rank n = hi - lo; 
	heapify(A, n); //�����������佨��һ����ȫ����ѣ�O(n)
	while (0 < --n) //������ժ�����Ԫ������������ĺ�׺��ֱ���ѿ�
	{
		swap(A[0], A[n]); percolateDown(A, n, 0);
	} //�Ѷ���ĩԪ�ضԻ���������
}

template<typename T>
inline int Vector<T>::disordered() const
{
	int n = 0;
	for (int i = 1; i < _size; i++)
	{
		if (_elem[i - 1] > _elem[i])
		{
			n++;
		}
	}
	return n;//���ҽ���n=0ʱ�������� 
}

template<typename T>
inline Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const
{
	while ((lo < hi--) && (e != _elem[hi])); //�Ӻ���ǰ��˳�����
	return hi; //��hi < lo������ζ��ʧ�ܣ�����hi������Ԫ�ص���
}

template<typename T>
inline Rank Vector<T>::search(T* S, T const& e, Rank lo, Rank hi) const
{
	while (lo < hi) //ÿ������������һ�αȽ��жϣ���������֧
	{
		Rank mi = (lo + hi) >> 1; //���е�Ϊ��㣨��������۰룬��Ч������ֵ��ʾ������һλ��
		(e < S[mi]) ? hi = mi : lo = mi + 1; //���ȽϺ�ȷ������[lo, mi)��(mi, hi)
	} //�ɹ����Ҳ�����ǰ��ֹ
	return lo - 1; //���ˣ�[lo]Ϊ����e����С�ߣ���[lo-1]��Ϊ������e�������
}

template <typename T> 
T& Vector<T>::operator[] (Rank r) //�����±������
{
	return _elem[r];
} // assert: 0 <= r < _size

template <typename T>
const T& Vector<T>::operator[] (Rank r) const //����������ֵ
{
	return _elem[r];
} // assert: 0 <= r < _size

template<typename T>
inline Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
	if (_elem)
	{
		delete[]_elem;
	}
	copyFrom(V._elem, 0, V.size());
	return *this;
}

template<typename T>
inline T Vector<T>::remove(Rank r)
{
	T e = _elem[r]; //���ݱ�ɾ��Ԫ��
	remove(r, r + 1); //��������ɾ���㷨����Ч�ڶ�����[r, r + 1)��ɾ��
	return e; //���ر�ɾ��Ԫ��
}

template<typename T>
inline int Vector<T>::remove(Rank lo, Rank hi)//ɾȥ[lo,hi)
{
	if (lo == hi) return 0; //����Ч�ʿ��ǣ����������˻����
	while (hi < _size) _elem[lo++] = _elem[hi++]; //��׺[hi, _size)˳��ǰ��hi-loλ
	_size = lo; 
	shrink(); //���¹�ģ��lo=_size֮��������������㣻���Ҫ��������
	return hi - lo; //���ر�ɾ��Ԫ�ص���Ŀ
}

template<typename T>
inline Rank Vector<T>::insert(Rank r, T const& e)
{
	expand(); //���Ҫ��������
	for (Rank i = _size; r < i; i--) //�Ժ���ǰ�����Ԫ��
	{
		_elem[i] = _elem[i - 1];//˳�κ���һ����Ԫ
	}
	_elem[r] = e; _size++; //������Ԫ�ز���������
	return r; //������
}

template<typename T>
inline void Vector<T>::sort(Rank lo, Rank hi, int Case)
{
	switch (Case)
	{
	case 1: bubbleSort(lo, hi); break; //��������
	case 2: selectionSort(lo, hi); break; //ѡ������
	case 3: mergeSort(lo, hi); break; //�鲢����
	default: quickSort(lo, hi); break; //��������
	} //����ѡ�������㷨�Բ���
}

template<typename T>
inline void Vector<T>::unsort(Rank lo, Rank hi) //�����������[lo, hi)
{
	T* V = _elem + lo; //��������_elem[lo, hi)������һ����V[0, hi - lo)
	for (Rank i = hi - lo; 1 < i; --i) //�Ժ���ǰ
	{
		swap(V[i - 1], V[rand() % i]);//��V[i - 1]��V[0, i)��ĳһԪ���������
	}
}

template<typename T>
inline int Vector<T>::deduplicate()
{
	Rank oldSize = _size; //��¼ԭ��ģ
	for (Rank i = 1; i < _size; ) //��ǰ����������_elem[1,_size)
	{
		if (-1 == find(_elem[i], 0, i)) //��ǰ׺[0,i)��Ѱ����[i]��ͬ�ߣ�����һ������O(i)
		{
			i++;//������ͬ���������������
		} 
		else
		{
			remove(i);//����ɾ��[i]��O(_size-i)
		}
	}
	return oldSize - _size; //��ɾ��Ԫ������
}

template<typename T>
inline int Vector<T>::uniquify()
{
	Rank i = 0, j = 0; //���Ի��조���ڡ�Ԫ�ص���
	while (++j < _size) //��һɨ�裬ֱ��ĩԪ��
	{
		if (_elem[i] != _elem[j]) //������ͬ��
		{
			_elem[++i] = _elem[j];//���ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
		}
	}
	_size = ++i; shrink(); //ֱ�ӽس�β������Ԫ��
	return j - i; //������ģ�仯��������ɾ��Ԫ������
}

template<typename T>
void Vector<T>::traverse(void(*visit)(T&))//��������ָ�����
{
	for (Rank i = 0; i < _size; i++) visit(_elem[i]);//��������
}

template <typename T> 
template <typename VST> //Ԫ�����͡�������
void Vector<T>::traverse(VST& visit) //���������������
{
	for (Rank i = 0; i < _size; i++) visit(_elem[i]);//��������
} 