// template shared unique.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <memory>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <iterator>
#include <functional> 

using namespace std;

template<typename T> class make_my_shared;
template<typename T>

void my_delete(T t)
{
	if (t)
		delete(t);

}

template <typename T>
class my_shared_ptr
{
public:
	my_shared_ptr() :counter(new unsigned(0)) {};

	my_shared_ptr(const my_shared_ptr<T> &mp,void (*dt)(T*)=my_delete) :
		p(mp.p), counter(mp.counter), deleter(dt) {
		(*counter)++;
	};

	
	~my_shared_ptr()
	{
		if (!--(*counter))
		{
			deleter(p);
			delete(counter);
		}
			
	}
	my_shared_ptr(const make_my_shared<T>& md) :counter(new unsigned(1)), p(md.base_ptr),deleter(my_delete) {};

	my_shared_ptr& operator=(const my_shared_ptr& mp)
	{
		deleter = my_delete;
		counter = mp.counter;
		p = mp.p;
		(*conuter)++;
		return *this;
	}

	my_shared_ptr& operator=( my_shared_ptr& mp)
	{
		deleter = my_delete;
		counter = mp.counter;
		p = mp.p;
		(*conuter)++;
		return *this;
	}

	my_shared_ptr& operator=(make_my_shared<T>& md)
	{
		deleter = my_delete;
		counter = new unsigned(1);
		p = md.base_ptr;
		return *this;
	}

	T* operator->()
	{
		return  &  (*this).operator*();
	}

	T& operator*()
	{
		return *p;
	}

private:
	mutable unsigned* counter;
	T * p;
	void(*deleter)(T*);
};



template<typename T>
void test_delet(T t)
{
	if (t)
	{
		cout << "执行析构" << endl;
		delete(t);
	}
}

template<typename T>
class my_unique_ptr
{
public:
	my_unique_ptr() :p(NULL) {};
	//my_unique_ptr(T* np) :p(np) {};
	my_unique_ptr(T* np,void (*del)(T*) = my_delete) :p(np),deleter(del) {};
	~my_unique_ptr()
	{
		if(p) deleter(p);
	}

	T* release() { 

		if (p)
		{
			auto a = p; 
			p = NULL; 
			return a;
		}
		return p;
			 }
	void reset() {
		if (p)
		{
			deleter(p);
			p = NULL;
		};
	}
	void reset(T* t) 
	{ if(p)
		deleter(p); 
	  p = t; 
	}

private:
	T * p;
	void (*deleter)(T*);
};

template<typename T>
class make_my_shared
{
public:
	//typedef typename T::iterator iterator;
	friend class my_shared_ptr<T>;

	make_my_shared() = default;
	make_my_shared(const T t) :data(t) { base_ptr = new T(data); };
	make_my_shared(initializer_list<T> it) :data(), base_ptr(it) {};
	//make_my_shared(iterator l, iterator r) :data(), base_ptr(l, r) {};
	
	~make_my_shared() = default;
private:
	T data;
	T* base_ptr;
};


vector<int>& fun()
{
	my_shared_ptr<vector<int>> test = make_my_shared <vector<int>>({ 111,1,2,2 });
	vector<int> &p = *test;
	auto a = test->size();
	
	return p;
}

int main()
{
	vector<int> vi{1,2,2,4,5};
	
	my_shared_ptr<int> mp = make_my_shared<int>(5);
	auto mp1 = mp;
	auto mp2 = mp;


	int a = 40;

	system("pause");
    return 0;
}

