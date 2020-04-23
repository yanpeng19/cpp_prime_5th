#pragma once
#include "stdafx.h"
#include <memory>
#include <iostream>
#include <initializer_list>
#include <vector>
#include <iterator>
#include <functional> 
#include <string>
#include <forward_list>

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
	template<typename T> friend class BlobPtr;
public:
	my_shared_ptr() :counter(0) {};

	my_shared_ptr(const my_shared_ptr<T> &mp, void(*dt)(T*) = my_delete) :
		p(mp.p), counter(++mp.counter), deleter(dt) {};


	~my_shared_ptr()
	{
		if (!--counter)
			deleter(p);
	}
	my_shared_ptr(const make_my_shared<T>& md) :counter(1), p(md.base_ptr), deleter(my_delete) {};

	my_shared_ptr& operator=(const my_shared_ptr& mp)
	{
		deleter = my_delete;
		counter = ++mp.counter;
		p = mp.p;
		return *this;
	}

	my_shared_ptr& operator=(my_shared_ptr& mp)
	{
		deleter = my_delete;
		counter = ++mp.counter;
		p = mp.p;
		return *this;
	}

	my_shared_ptr& operator=(make_my_shared<T>& md)
	{
		deleter = my_delete;
		counter++;
		p = md.base_ptr;
		return *this;
	}

	T* operator->()
	{
		return  &(*this).operator*();
	}

	T& operator*()
	{
		return *p;
	}

private:
	mutable unsigned counter;
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
	my_unique_ptr(T* np, void(*del)(T*) = my_delete) :p(np), deleter(del) {};
	~my_unique_ptr()
	{
		if (p) deleter(p);
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
	{
		if (p)
			deleter(p);
		p = t;
	}

private:
	T * p;
	void(*deleter)(T*);
};

template<typename T>
class make_my_shared
{
public:
	//typedef typename T::iterator iterator;
	friend class my_shared_ptr<T>;

	make_my_shared() = default;

	//老版本的构造函数
	/*make_my_shared(const T t) :data(t) { base_ptr = new T(data); };
	make_my_shared(initializer_list<T> it) :data(), base_ptr(it) {};*/
	template<typename ...Args>
	make_my_shared(Args&&...args) :data( T (forward<Args>(args)...))
	{
		base_ptr = new T(data);
	}


	template<typename IT>
	make_my_shared(IT r, IT l) :data(T(r, l))
	{
		base_ptr = new T(data);
	}

	//make_my_shared(iterator l, iterator r) :data(), base_ptr(l, r) {};

	~make_my_shared() = default;
private:
	T data;
	T* base_ptr;
};
