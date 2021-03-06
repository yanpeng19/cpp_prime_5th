// 12.1.6.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <iterator>
#include <fstream>
#include <sstream>
#include <utility>

using namespace std;
//需要实现的函数功能是  pop(),front(),
//push_back(),pop_back(), size(),empty()

class StrBlob
{
	friend class StrBlobPtr;
	friend class ConstStrBlobPtr;

public:

	typedef std::vector<string>::size_type size_type;        //类型别名以及构造函数
	StrBlob();
	StrBlob(std::initializer_list<string> il);
	StrBlob(StrBlob & sb) : data(make_shared<vector<string>>(*sb.data)) {};
	StrBlob & operator=(const StrBlob & sb)
	{
		auto newsp = make_shared<vector<string>>(*sb.data);
	}


	size_type size() { return data->size(); }
	bool empty() { return data->empty(); }
	void push_back(const string &s) { data->push_back(s); }
	//void push_back(const string s) { data->push_back(s); }
	void pop_back();

	//查询操作
	std::string & front();
	std::string & back();

	//begin和end 操作
	std::vector<string>::iterator begin();
	std::vector<string>::iterator end();

//private:
	shared_ptr<vector<string>> data;
	//void check()
};


//weak_ptr使用逻辑：因为不能直接通过姐引用访问（因为不确定指向的内存是否存在数据）
//所以需要先临时生成shared_ptr,并赋值给weak_ptr,进行操作

class StrBlobPtr
{
public:
	StrBlobPtr() :curr(0) {}
	StrBlobPtr(StrBlob &a, string::size_type sz = 0) :wptr(a.data), curr(sz) {};


	//两个操作函数
	string& deref() const;//解引用操作
	StrBlobPtr& incr();//自增操作

	StrBlobPtr& operator++();
	StrBlobPtr& operator--();
	StrBlobPtr& operator++(int);
	StrBlobPtr& operator--(int);

	StrBlobPtr& operator+(StrBlobPtr&, int);
	StrBlobPtr& operator-(StrBlobPtr&, int);

	vector<string>::iterator begin();
	vector<string>::iterator end();

private:
	string::size_type curr;
	shared_ptr<vector<string>> 
		check(const string & s, size_t sz) const;//主要函数，功能是根据下标，检查是否合法生成一个shard_ptr，返回赋值给wptr，进行下一步处理
	weak_ptr <vector<string>> wptr;

};

shared_ptr<vector<string>> StrBlobPtr:: check(const string& s, size_t i) const
{
	shared_ptr<vector<string>> p = wptr.lock();
	if (!p)
		throw runtime_error("vector<string> 已被清除，数据为空");
	if (i >= p->size())
		throw runtime_error("xiaobiaocuowu,");
	return p;
}

string& StrBlobPtr:: deref() const
{
	auto p = check("xiabiaoyuejie", curr);
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	check("daojieweile", curr);
	++curr;
	return (*this);
}

StrBlobPtr& StrBlobPtr::operator++()
{
	check("xiaobiaocuowu",curr);
	++curr;
	return *this;
}

StrBlobPtr& StrBlobPtr::operator--()
{
	--curr;
	check("xiabiaocuowu",curr);
	return *this;
}

StrBlobPtr& StrBlobPtr::operator++(int)
{
	StrBlobPtr ret = *this;
	++*this;
	return ret;
}

StrBlobPtr& StrBlobPtr::operator--()
{
	StrBlobPtr ret = *this;
	--*this;
	return ret;
}

StrBlobPtr& operator+(StrBlobPtr& sb_l, int n)
{
	StrBlobPtr temp = sb_l;
	temp.curr = sb_l.curr + n;
	check("xiaobiaocuowu", temp.curr);
	return temp;
}

StrBlobPtr& operator-(StrBlobPtr& sb_l, int n)
{
	StrBlobPtr temp = sb_l;
	temp.curr = sb_l.curr - n;
	check("xiaobiaocuowu", temp.curr);
	return temp;
}

vector<string>::iterator StrBlobPtr::begin()
{
	auto p = check("1", 0);
	return p->begin();
}

vector<string>::iterator StrBlobPtr::end()
{
	auto p = check("1", 0);
	return p->end();
}



StrBlob::StrBlob() :data(make_shared<vector<string>>()) {};
StrBlob::StrBlob(initializer_list<string> i) :
	data(make_shared<vector<string>>(i)) {};

void StrBlob::pop_back()//删除操作
{
	//check();
	this->data->pop_back();
}

std::string& StrBlob::front()
{
	//check
	return this->data->front();
}

std::string& StrBlob::back()
{
	//check
	return this->data->back();
}

std::vector<string>::iterator StrBlob::begin()
{
	return data->begin();
}

std::vector<string>::iterator StrBlob::end()
{
	return data->end();
}

void GetString(ifstream& inf, StrBlob &a)
{
	string line, word;
	while (getline(inf, line))
	{
		istringstream iss(line);
		while (iss >> word)
		{
			a.push_back(word);
		}
	}

	return;
}

class ConstStrBlobPtr
{
public:
	ConstStrBlobPtr() :curr(0) {}
	ConstStrBlobPtr(StrBlob &a, string::size_type sz = 0) :wptr(a.data), curr(sz) {};

	//两个操作函数
	string& deref() const;//解引用操作
	//ConstStrBlobPtr & incr();//自增操作

	//vector<string>::iterator begin();
	//vector<string>::iterator end();

private:
	string::size_type curr;
	shared_ptr<vector<string>>
		check(const string & s, size_t sz) const;//主要函数，功能是根据下标，检查是否合法生成一个shard_ptr，返回赋值给wptr，进行下一步处理
	weak_ptr <vector<string>> wptr;

};

string& ConstStrBlobPtr::deref() const
{
	auto p = check("xiabiaoyuejie", curr);
	return (*p)[curr];
}

//ConstStrBlobPtr & ConstStrBlobPtr::incr()
//{
//	check("daojieweile", curr);
//	++curr;
//	return (*this);
//}

shared_ptr<vector<string>> ConstStrBlobPtr::check(const string & s, size_t i) const
{
	shared_ptr<vector<string>> p = wptr.lock();
	if (!p)
		throw runtime_error("vector<string> 已被清除，数据为空");
	if (i >= p->size())
		throw runtime_error("xiaobiaocuowu,");
	return p;
}

int main()
{
	StrBlob a{ "dizibaobao kuaidao huaililai" };
	StrBlobPtr pa(a);



	system("pause");
	return 0;
}

