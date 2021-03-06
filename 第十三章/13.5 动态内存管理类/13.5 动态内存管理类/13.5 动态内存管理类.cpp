// 13.5 动态内存管理类.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <fstream>

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
	~StrVec();

	void push_back(const string &);
	int size() { return first_free - elements; };                        //容器内元素哥数
	size_t capcity() { return cap - elements; };                         //可用容器大小
	string *begin() { return elements; };
	string *end() { return first_free; };

	void resize(int i);
	void resize(int i, const string &s);
	void reserve(int i);

private:
	void check_n_size();                  //  检查是否有可用空间函数
	void relocate();                      //  重新分配空间，并拷贝的函数
	void free();                          //  释放内存函数
	pair<string*, string*> allc_n_copy(); //  工具函数，拷贝，赋值使用

	//static std::allocator<string> alloc;  内存分配器，甩出指针，指向分配得内存
	string *elements;                     //  内存开头
	string *first_free;                   //  第一个可用内存地址
	string *cap;                          //  尾后指针
};

StrVec::StrVec(const StrVec & sv)
{
	auto newdata = alloc.allocate(sv.first_free-sv.elements);
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
	//初始版本
	/*auto newdata = alloc.allocate(sv.first_free - sv.elements);
	uninitialized_copy(sv.elements, sv.first_free, newdata);
	free();
	elements = newdata;
	first_free = cap = elements + (sv.first_free - sv.elements);
	return *this;	 */
	//加入 allc_n_copy版本 逻辑更清洗
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
	auto b = first_free;
	while (b != elements)
	{
		alloc.destroy(--b);
	}
	alloc.deallocate(elements, capcity());
}

void StrVec::check_n_size()
{
	if (size()==capcity())
		relocate();
}

void StrVec::relocate()
{
//	//自己写的版本
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
	//使用move
	auto newcapcity = capcity() ? 2 * capcity() : 1;
	auto bg = alloc.allocate(newcapcity);
	auto temp_ele = elements;
	auto temp_bg = bg;
	for (int i = 0; i < size(); i++)
		alloc.construct(temp_bg++, std::move(*temp_ele++));
	free();
	elements = bg;
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
	// 需要容器内元素数量小于当前实际元素数量，则析构i之后的元素
	if (i < size())
	{
		while(size()!=i)
		alloc.destroy(--first_free);
	}
	// 需要容量大于 size() 小于  capcity() 则什么都不做
	// 需要容量大于 capcity(),重新分配内存,容量翻倍
	while (capcity() < i)
			relocate();
}

void StrVec::resize(int i, const string &s)
{
	// 需要容器内元素数量小于当前实际元素数量，则析构i之后的元素
	if (i < size())
	{
		while (size() != i)
			alloc.destroy(--first_free);
	}
	// 需要容量大于 size() 小于  capcity() 则什么都不做
	// 需要容量大于 capcity(),重新分配内存,容量翻倍,并初始化
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
		while(capcity() < n)
			relocate();
}

int main()
{
	StrVec a;
	a.push_back("dizi");
	a.push_back("baobao");

	StrVec b = a;
	StrVec c(a);
	StrVec d = {"dizi","baobao","pangzixiangdi"};
	for (auto e : b)
		cout << e << endl;
	for (auto e : c)
		cout << e << endl;
	a.resize(10, "baobao");
	a.resize(2);
	a.reserve(20);
	cout << a.capcity() << endl;
	for (auto e : a)
		cout << e << endl;
	for (auto e : d)
		cout << e << endl;


	system("pause");
    return 0;
}

