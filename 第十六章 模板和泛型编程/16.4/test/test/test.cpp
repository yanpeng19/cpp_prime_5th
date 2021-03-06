// test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename T>
string debug_rep(const T& t)
{
	ostringstream os;
	os << t;
	cout << "use template <typename T> string debug_rep(T&) " << endl;
	return os.str();
}

template <typename T>
string debug_rep(T* t)
{
	ostringstream os = cout;
	os << t << " :";
	if (t)
		os << *t;
	else os << "null ptr";

	cout << "use template <typename T> string debug_rep(T*) " << endl;
	return os.str();
}

string debug_rep(const string& s)
{
	cout << "use string debug_rep(const string& s) " << endl;
	return "" + s + "";
}

string debug_rep(char *p)
{
	cout << "use string debug_rep(char *p) " << endl;
	return debug_rep(string(p));
}

string debug_rep(const char *p)
{
	cout << "use string debug_rep(const char *p) " << endl;
	return debug_rep(string(p));
}
template<typename T,typename... Args>
void foo(const T &t, const Args& ... args)
{
	os << sizeof...(Args) << endl;
	os << sizeof...(args) << endl;
	return os;
}

template<typename T>
ostream& print(ostream &os, const T &t)
{
	os << t << " ";
	return os;
}

template<typename T,typename...Args>
ostream& print(ostream &os, const T &t,const Args&...args)
{
	os << t << " ";;
	return print(os,args...);
}

template<typename...Args>
ostream& Error_mes(ostream &os,const Args&... args)
{
	return print(os,debug_rep(args)...);
	
}


int main()
{
	int i = 10;
	double d = 3.14;
	string s = "dizi";

	Error_mes(cout, i,d,s);

	system("pause");
    return 0;
}

