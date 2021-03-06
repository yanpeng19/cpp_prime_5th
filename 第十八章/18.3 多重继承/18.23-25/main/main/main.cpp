// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Base
{
public:
	Base() = default;
	Base(const string & st) :s(st) {};
	void print() 
	{
		cout << s << endl;
		cout << "执行Base::cout " << endl;
	}
	virtual ~Base() { cout << "Base::delete" << endl; }
private:
	string s;
};

class A
{
public:
	A() = default;
	A(const int &in) :i(in) {};
	void print() 
	{
		cout << i << endl;
		cout << "执行A::print" << endl;
	}

	void gogo()
	{
		cout << "yes" << endl;
	}
	virtual ~A() { cout << "A::delete" << endl; }

private:
	int i = 0;
};

class T:public Base,public A
{
public:
	T() = default;
	T(const char ch) :Base(""), A(0), c(ch) {};
	/*void print()
	{
		cout << c << endl;
		cout << "执行T::print" << endl;
	}*/
	virtual ~T() { cout << "T::delete" << endl; }

private:
	char c;

};	


int main()
{
	T t('c');
	A* p = new T('c');

	p->print();
	delete(p);

	system("pause");
    return 0;
}

