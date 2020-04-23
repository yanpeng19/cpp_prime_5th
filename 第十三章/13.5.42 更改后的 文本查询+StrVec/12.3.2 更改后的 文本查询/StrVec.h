#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <fstream>
#include <algorithm>

using namespace std;

static std::allocator<string> alloc;

class StrVec
{
public:
	StrVec() :
		elements(NULL), first_free(NULL), cap(NULL) {};
	StrVec(initializer_list<string> s);
	StrVec(const StrVec&);
	StrVec &operator=(const StrVec&);
	StrVec(StrVec&&s) :
		elements(s.elements), first_free(s.first_free), cap(s.cap)
	{
		s.elements = s.first_free = s.cap = NULL;
	}
	StrVec & operator = (StrVec&&s)
	{
		elements = s.elements;
		first_free = s.first_free;
		cap = s.cap;
		s.elements = s.first_free = s.cap = NULL;
		return *this;
	}
	~StrVec();

	void push_back(const string &);
	int size() { return first_free - elements; };                     //������Ԫ�ظ���
	int capcity() { return cap - elements; };                         //����������С
	bool empty() { return size() ? 1 : 0; }
	void pop_back() { alloc.destroy(--first_free); };
	string &front() { return *elements; };
	string &back() { return *(first_free-1); }

	string *begin() { return elements; };
	string *end() { return first_free; };

	void resize(int i);
	void resize(int i, const string &s);
	void reserve(int i);

private:
	void check_n_size();                  //  ����Ƿ��п��ÿռ亯��
	void relocate();                      //  ���·���ռ䣬�������ĺ���
	void free();                          //  �ͷ��ڴ溯��
	pair<string*, string*> allc_n_copy(); //  ���ߺ�������������ֵʹ��

										  //static std::allocator<string> alloc;  �ڴ��������˦��ָ�룬ָ�������ڴ�
	string *elements;                     //  �ڴ濪ͷ
	string *first_free;                   //  ��һ�������ڴ��ַ
	string *cap;                          //  β��ָ��
};

StrVec::StrVec(const StrVec & sv)
{
	auto newdata = alloc.allocate(sv.first_free - sv.elements);
	uninitialized_copy(sv.elements, sv.first_free, newdata);
	elements = newdata;
	first_free = cap = elements + (sv.first_free - sv.elements);
}

StrVec::StrVec(initializer_list<string> init_l)
{
	elements = first_free = cap = NULL;
	for (auto a : init_l)
		push_back(a);
}

StrVec & StrVec::operator=(const StrVec & sv)
{
	//��ʼ�汾
	/*auto newdata = alloc.allocate(sv.first_free - sv.elements);
	uninitialized_copy(sv.elements, sv.first_free, newdata);
	free();
	elements = newdata;
	first_free = cap = elements + (sv.first_free - sv.elements);
	return *this;	 */
	//���� allc_n_copy�汾 �߼�����ϴ
	auto newdata = allc_n_copy();
	uninitialized_copy(sv.elements, sv.first_free, newdata.first);
	free();
	elements = newdata.first;
	first_free = cap = newdata.second;
	return *this;
}

pair<string *, string*> StrVec::allc_n_copy()
{
	auto newele = alloc.allocate(first_free - elements);
	auto newcap = newele + (first_free - elements);
	return pair<string*, string*>{newele, newcap};
}

void StrVec::free()
{
	/*if (elements)
		for (auto a = first_free; a != elements;)
			alloc.destroy(--a);
	alloc.deallocate(elements, capcity());*/

	//for_each�汾 
	if (elements)
	{
		for_each(elements, first_free - 1,
			[](string &s) { alloc.destroy(&s); });
		alloc.deallocate(elements, capcity());
	}
		

}
void StrVec::check_n_size()
{
	if (size() == capcity())
		relocate();
}

void StrVec::relocate()
{
	//	//�Լ�д�İ汾
	//	int i, j;
	//	string *newdata;
	//	if (elements == NULL)
	//	{
	//		newdata = alloc.allocate(1);
	//		i = 0;
	//		j = 1;
	//	}
	//	else
	//	{
	//		newdata = alloc.allocate(size() * 2);
	//		i = first_free - elements;
	//		j = size() * 2;
	//		uninitialized_copy(elements, first_free, newdata);
	//		free();
	//	}
	//	elements = newdata;
	//	first_free = newdata + i;
	//	cap = newdata + j;
	//ʹ��move
	auto newcapcity = capcity() ? 2 * capcity() : 1;
	auto newelements = alloc.allocate(newcapcity);
	auto temp_ele = elements;
	auto temp_bg = newelements;
	for (int i = 0; i < size(); i++)
		alloc.construct(temp_bg++, std::move(*temp_ele++));
	free();
	elements = newelements;
	first_free = temp_bg;
	cap = elements + newcapcity;
}

StrVec::~StrVec()
{
	free();
}

void StrVec::push_back(const string &s)
{
	check_n_size();
	alloc.construct(first_free++, s);
}

void StrVec::resize(int i)
{
	// ��Ҫ������Ԫ������С�ڵ�ǰʵ��Ԫ��������������i֮���Ԫ��
	if (i < size())
	{
		while (size() != i)
			alloc.destroy(--first_free);
	}
	// ��Ҫ�������� size() С��  capcity() ��ʲô������
	// ��Ҫ�������� capcity(),���·����ڴ�,��������
	while (capcity() < i)
		relocate();
}

void StrVec::resize(int i, const string &s)
{
	// ��Ҫ������Ԫ������С�ڵ�ǰʵ��Ԫ��������������i֮���Ԫ��
	if (i < size())
	{
		while (size() != i)
			alloc.destroy(--first_free);
	}
	// ��Ҫ�������� size() С��  capcity() ��ʲô������
	// ��Ҫ�������� capcity(),���·����ڴ�,��������,����ʼ��
	if (i > capcity())
	{
		while (capcity() < i)
			relocate();
		while (size() < i)
			alloc.construct(first_free++, s);
	}
}

void StrVec::reserve(int n)
{
	if (n > capcity())
		while (capcity() < n)
			relocate();
}
