// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <iterator>
#include <cstdlib>

using namespace std;

template<typename T> class Blob
{
	 
	friend bool operator==<T>(const Blob<T>&,const Blob<T>&);
	friend bool operator< <T>(const Blob<T>&, const Blob<T>&);
	friend bool operator> <T>(const Blob<T>&, const Blob<T>&);

public:
	typedef typename vector<T>::size_type size_type;
	Blob() = default;

	template<typename IT>
	Blob(IT a, IT b);

	Blob(initializer_list<T> il);

	size_type size() { return data.size(); }
	bool empty() { return data.empty(); }
	void push_back(const T t) { data->push_back(t); }
	void pop_back();

	T& front();
	T& back();

	typename vector<T>::iterator begin();
	typename vector<T>::iterator end();

	 T& operator[](const size_type sz);



	 shared_ptr<vector<T>> get_data() const { return data; }

private:
	shared_ptr<vector<T>> data;
	void check(size_type i, const std::string &msg) const;
};

template<typename T>
template<typename IT>
Blob<T>::Blob(IT a,IT b) : data(make_shared<vector<T>>(a, b)) {};

template<typename T>
Blob<T>::Blob(initializer_list<T> il) :
	data(make_shared<vector<T>>(il)) {};

template<typename T>
void Blob<T>::check(size_type i, const std::string &msg) const
{
	if (i > data->size())
		throw std::out_of_range(msg);
}

template<typename T>
void Blob<T>::pop_back()
{
	if (data->empty())
		throw std::out_of_range("vector is empty!can not do this");
	data->pop_back();
	return;
}

template<typename T>
T& Blob<T>::front()
{
	return data->front();
}

template<typename T>
T& Blob<T>::back()
{
	return data->back();
}

template<typename T>
typename vector<T>::iterator Blob<T>::begin()
{
	return data->begin();
}

template<typename T>
typename vector<T>::iterator Blob<T>::end()
{
	return data->end();
}

template<typename T>
T& Blob<T>::operator[](const size_type sz)
{
	check(sz, "下标错误");
	return data[sz];
}


template<typename T>
class BlobPtr
{
public:
	BlobPtr() :sz(0) {};
	BlobPtr(shared_ptr<vector<T>> sp) :
		wptr(sp), curr(0) {};

	T& deref();  //解引用
	BlobPtr<T>& incr();//自增运算

	BlobPtr<T>& operator++();
	BlobPtr<T>& operator--();
	BlobPtr<T>& operator++(int);
	BlobPtr<T>& operator--(int);

	T& operator*();
	T* operator->();

private:
	weak_ptr<vector<T>> wptr;
	size_t curr;
	shared_ptr<vector<T>> check(const string&, size_t n);
};

template<typename T>
shared_ptr<vector<T>>  BlobPtr<T>::check(const string&s, size_t n)
{
	shared_ptr<vector<T>> temp = wptr.lock();
	if (!temp)
		throw runtime_error("底层未初始化，数据为空");
	if (n >= temp->size())
		throw runtime_error(s);
	return temp;
}

template<typename T>
T& BlobPtr<T>::deref()
{
	shared_ptr<vector<T>> temp = check("xiaobiaocuowu", curr);
	return (*temp)[curr];
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::incr()
{
	check("已到末尾", curr);
	++curr;
	return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++()
{
	check("已经到数据末尾", curr);
	++curr;
	return (*this);
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--()
{
	check("已经到数据开头", curr);
	--curr;
	return (*this);
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator++(int)
{
	shared_ptr<vector<T>> temp = check("已经到数据末尾", curr);
	++curr;
	return *this;
}

template<typename T>
BlobPtr<T>& BlobPtr<T>::operator--(int)
{
	shared_ptr<vector<T>> temp = check("已经到数据开头", curr);
	--curr;
	return *this;
}

template<typename T>
T& BlobPtr<T>::operator*()
{
	return this->deref();
}
template<typename T>
T* BlobPtr<T>::operator->()
{
	return & this.operator*();
}

template<typename T>
bool operator==(const Blob<T>&l, const Blob<T>&r)
{
	auto a = l.get_data();
	auto b = r.get_data();

	return *a == *b;
}

template<typename T> 
bool operator<(const Blob<T>&l, const Blob<T>&r)
{
	auto a = l.get_data();
	auto b = r.get_data();

	return *a < *b;
}

template<typename T> 
bool operator>(const Blob<T>&l, const Blob<T>&r)
{
	auto a = l.get_data();
	auto b = r.get_data();

	return *b < *a;
}

int main()
{
	Blob<string> s1, s3;
	s1 = { "dizi","baobao" };
	Blob<string> s2(s1.begin(), s1.end());
	s3 = { "xiaodizi" };
	BlobPtr<string> ps1(s1.get_data());

	cout << *ps1 << endl;
	ps1++;
	cout << *ps1 << endl;

	if (s1 == s2)
		cout << 1 << endl;
	if (s2 < s3)
		cout << 2 << endl;


	system("pause");
    return 0;
}

