#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <initializer_list>
#include <memory>
#include <iterator>
#include <fstream>
#include <sstream>

using namespace std;

class StrBlob
{
	friend class StrBlobPtr;
	friend class ConstStrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;        //类型别名以及构造函数
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() { return data->size(); }
	bool empty() { return data->empty(); }

	void push_back(const string &s) { data->push_back(s); }
	//void push_back(const string s) { data->push_back(s); }
	void pop_back();

	//查询操作
	std::string & front();
	std::string & back();

	//begin和end 操作
	std::vector<std::string>::iterator begin();
	std::vector<std::string>::iterator end();

private:
	std::shared_ptr<std::vector<std::string>> data;
	//void check()
};


//weak_ptr使用逻辑：因为不能直接通过姐引用访问（因为不确定指向的内存是否存在数据）
//所以需要先临时生成shared_ptr,并赋值给weak_ptr,进行操作

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

void GetString(ifstream & inf, StrBlob &a)
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

