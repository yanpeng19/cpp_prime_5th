// 12.1.1.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <iterator>

using namespace std;
//需要实现的函数功能是  pop(),front(),
//push_back(),pop_back(), size(),empty()

class StrBlob
{
public:
	typedef std::vector<string>::size_type size_type;        //类型别名以及构造函数
	StrBlob();
	StrBlob(std::initializer_list<string> il);
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

private:
	shared_ptr<vector<string>> data;
	//void check()
};

StrBlob::StrBlob() :data(make_shared<vector<string>>()) {};
StrBlob::StrBlob(initializer_list<string> i) :
	data(make_shared<vector<string>>(i)) {};

void StrBlob::pop_back()//删除操作
{
	//check();
	this->data->pop_back();
}

std::string & StrBlob::front()
{
	//check
	return this->data->front();
}

std::string & StrBlob::back()
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


int main()
{
	const StrBlob a{ "pangzi","xiang","dizi" };
	StrBlob b = a;
	b.push_back("baobei");

	for (auto c : b)
		cout << c << endl;
	if (!b.empty())
	{
		cout << "not empty" << endl;
	}

	cout << "the first is " << b.front() << endl;
	cout << "the last is " << b.back() << endl;

	b.pop_back();
	cout << "delete last one " << " now the last is" << b.back();
	system("pause");
    return 0;
}

