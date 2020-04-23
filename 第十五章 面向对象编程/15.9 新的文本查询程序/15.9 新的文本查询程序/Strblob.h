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
	typedef std::vector<std::string>::size_type size_type;        //���ͱ����Լ����캯��
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() { return data->size(); }
	bool empty() { return data->empty(); }

	void push_back(const string &s) { data->push_back(s); }
	//void push_back(const string s) { data->push_back(s); }
	void pop_back();

	//��ѯ����
	std::string & front();
	std::string & back();

	//begin��end ����
	std::vector<std::string>::iterator begin();
	std::vector<std::string>::iterator end();

private:
	std::shared_ptr<std::vector<std::string>> data;
	//void check()
};


//weak_ptrʹ���߼�����Ϊ����ֱ��ͨ�������÷��ʣ���Ϊ��ȷ��ָ����ڴ��Ƿ�������ݣ�
//������Ҫ����ʱ����shared_ptr,����ֵ��weak_ptr,���в���

StrBlob::StrBlob() :data(make_shared<vector<string>>()) {};
StrBlob::StrBlob(initializer_list<string> i) :
	data(make_shared<vector<string>>(i)) {};

void StrBlob::pop_back()//ɾ������
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

