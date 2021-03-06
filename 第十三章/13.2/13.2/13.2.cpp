// 13.2.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class HasPtr
{
public:
	HasPtr(HasPtr & h) :ps(new std::string(*(h.ps))), i(h.i) {}
	HasPtr & operator=(const HasPtr&h)
	{
		auto newp = new std::string(*h.ps);
		delete h.ps;
		ps = newp;
		i = h.i;
		return *this;
	}
	
	HasPtr(const std::string &s = std::string()) :
		ps(new std::string(s)), i(0) {};
	~HasPtr() { delete ps; };


//private:
	string *ps;
	int i;
};


int main()
{
	HasPtr a("dizi");
	auto b = a;
	HasPtr c(a);
	cout << a.ps << endl;
	cout << b.ps << endl;
	cout << c.ps << endl;
	cout << *(a.ps) << endl;
	cout << *(b.ps) << endl;
	cout << *c.ps << endl;
	system("pause");
    return 0;
}

