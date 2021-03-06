// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template<typename T>
unsigned Statistic(const T &t,const vector<T>& vt)
{
	unsigned i = 0;
	for (auto a : vt)
		if (t == a) i++;
	return i;
}

template<unsigned N>
unsigned Statistic(const char(&p)[N] , const vector<string>&vt)
{
	unsigned i = 0;
	for (auto a : vt)
		if (p == a) i++;
	return i;
}

template<unsigned N>
unsigned Statistic(const char(&p)[N], const vector<const char*>&vt)
{
	unsigned i = 0;
	for (auto a : vt)
		if (p == a) i++;
	return i;
}

template<>
unsigned Statistic(const char* const &t,const vector<const char*> &vs)
{
	unsigned i = 0;
	for (auto a : vs)
		if (t == a) i++;
	return i;
}

int main()
{
	vector<int> vt= { 1,2,4,5,6,78,214,6125,12,3,5 };
	vector<double> vd = { 1.2,25,2.3,5,5,5,2,6,7.2 };
	vector<string> vs = { "dizi","baobao","pangzi","xiang ","dizi" };
	string s = "dizi";
	cout << Statistic(5, vt) << endl;
	cout << Statistic("dizi", vs) << endl;
	cout << Statistic(5.0, vd) << endl;



	vector<const char*> vc;
	vc.push_back("ABC");
	const char* p = "DDDDD";
	const char* p1 = "XIAODIZI";
	const char* p2 = "DDDDD";

	vc.push_back(p);
	vc.push_back(p1);
	vc.push_back(p2);


	cout << Statistic(p, vc) << endl;
	cout << Statistic("dizi", vc) << endl;
	
	system("pause");
    return 0;
}

