#pragma once

/*
* Copyright (c) 2023,RickJingDG
* All rights reserved.
*
* �ļ����ƣ�HuffmanTree.h
* �ļ���ʶ��δ����
* ժ Ҫ��������������
*
* ��ǰ�汾��1.0
* �汾��Ҫ�����ڶ����������Ļ�����������
* �� �ߣ�RickJingDG
* ������ڣ�2023��4��17��
*
*/

#include <cstdlib>//���ļ����ú��ļ���Ϣ����һ��
#include <cstdio>
#include <memory.h>
// ���ñ�׼���ͷ�ļ�

#include"../../BinTree/BinTree.h"
// ���÷Ǳ�׼���ͷ�ļ�

//=============ȫ�ֱ������忪ʼ=======================
#define  N_CHAR  (0x80 - 0x20)//���Կɴ�ӡ�ַ�Ϊ��
//=============ȫ�ֱ����������=======================

//=============�ṹ�嶨�忪ʼ=======================

struct HuffChar//Huffman�ַ�
{
	char ch; unsigned int weight; //�ַ���Ƶ��
	HuffChar(char c = '^', unsigned int w = 0) : ch(c), weight(w) {};
	// �Ƚ������е���
	bool operator< (HuffChar const& hc) { return weight > hc.weight; } //Ƶ��Խ�󣬻���������ֵԽС
	bool operator<= (HuffChar const& hc) { return weight >= hc.weight; }
	bool operator> (HuffChar const& hc) { return weight < hc.weight; } //Ƶ��ԽС������������ֵԽ��
	bool operator>= (HuffChar const& hc) { return weight <= hc.weight; }
	bool operator== (HuffChar const& hc) { return weight == hc.weight; }
	bool operator!= (HuffChar const& hc) { return weight != hc.weight; }
};

//=============�ṹ�嶨�����=======================

//=============�ඨ�忪ʼ=======================
class Bitmap//λͼBitmap�� 
{ 
private:
    unsigned char* M;
    Rank N, _sz; //λͼ�ռ�M[]��N*sizeof(char)*8�������к�_sz����Чλ
protected:
    void init(Rank n)
    {
        M = new unsigned char[N = (n + 7) / 8]; memset(M, 0, N); _sz = 0;
    }
public:
    Bitmap(Rank n = 8) { init(n); } //��ָ����������λͼ
    Bitmap(char* file, Rank n = 8)//��ָ����Ĭ�Ϲ�ģ����ָ���ļ��ж�ȡλͼ
    { 
        init(n);
        FILE* fp;
        fopen_s(&fp, file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
        for (Rank k = 0, _sz = 0; k < n; k++) _sz += test(k);
    }
    ~Bitmap() { delete[] M; M = NULL; _sz = 0; } //����ʱ�ͷ�λͼ�ռ�

    Rank size() { return _sz; }
    void set(Rank k) { expand(k); _sz++; M[k >> 3] |= (0x80 >> (k & 0x07)); }
    void clear(Rank k) { expand(k); _sz--; M[k >> 3] &= ~(0x80 >> (k & 0x07)); }
    bool test(Rank k) { expand(k); return M[k >> 3] & (0x80 >> (k & 0x07)); }

    void dump(char* file) //��λͼ���嵼����ָ�����ļ����Ա�Դ˺����λͼ������ʼ��
    {
        FILE* fp;
        fopen_s(&fp, file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }
    char* bits2string(Rank n) //��ǰnλת��Ϊ�ַ�������
    { 
        expand(n - 1); //��ʱ���ܱ����ʵ����λΪbitmap[n - 1]
        char* s = new char[n + 1]; s[n] = '\0'; //�ַ�����ռ�ռ䣬���ϲ�����߸����ͷ�
        for (Rank i = 0; i < n; i++) s[i] = test(i) ? '1' : '0';
        return s; //�����ַ���λ��
    }
    void expand(Rank k)//�������ʵ�Bitmap[k]�ѳ��磬��������
    { 
        if (k < 8 * N) return; //���ڽ��ڣ���������
        Rank oldN = N; unsigned char* oldM = M;
        init(2 * k); //���������ƣ��ӱ�����
        memcpy_s(M, N, oldM, oldN);
        delete[] oldM; //ԭ����ת�����¿ռ�
    }
};
class HuffTable//Huffman�����
{
public:
    HuffTable() {};
    HuffTable(char, char*);
    ~HuffTable();
    bool put(char, char*); 
    char** get(char k);
private:
    Vector<char> key;
    Vector<char*> value;
};
HuffTable::HuffTable(char k,char* v)
{
    key.insert(k);
    value.insert(v);
}
HuffTable::~HuffTable()
{
    key.~Vector();
    value.~Vector();
}
inline bool HuffTable::put(char k, char* v)
{
    if (key.find(k) != -1)
    {
        return false;
    }
    key.insert(k);
    value.insert(v);
    return true;
}
inline char** HuffTable::get(char k)
{
    Rank r = key.find(k);
    if (r==-1)
    {
        return nullptr;
    }
    else
    {
        return &value[r];
    }
}
using HuffTree = BinTree<HuffChar>; //Huffman������BinTree�������ڵ�����ΪHuffChar
using HuffForest = List<HuffTree*>; //Huffmanɭ��
using HuffCode = Bitmap; //Huffman�����Ʊ���
//=============�ඨ�����=======================

//=============ȫ�ֺ���������ʼ=======================
 int* statistics(char*); //���������ļ�ͳ�Ƹ��ַ�����Ƶ��
extern HuffForest* initForest(int*); //����������ɭ��
extern HuffTree* generateTree(HuffForest*); //���������
extern HuffTable* generateTable(HuffTree*); //�ɱ�����ת��Ϊ�����
extern int encode(HuffTable*, Bitmap*, char*); //���ĵı��룬���ر��볤��
extern void decode(HuffTree*, Bitmap*, int); //�����ƴ��Ľ���
//=============ȫ�ֺ�����������=======================