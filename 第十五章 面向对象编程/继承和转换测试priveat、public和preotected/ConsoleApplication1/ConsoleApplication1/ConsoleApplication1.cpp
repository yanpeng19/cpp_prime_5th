// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//


#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


class Base
{
	friend void test(Base&);
public:
	Base() = default;
	Base(string n,string sx, string x, string w,int s) :
		first_name(n),sex(sx), xue(x), wife(w),salary(s) {	};
	void get_sal() { cout << salary; }
	virtual void get_sex() { cout << sex; };
	virtual ~Base() = default;
	string first_name = "yan";
	string lase_name = "peng";
	void memfcn(Base &b) { b = *this; }


protected:
	string xue = "chu";

private:
	string wife = "dizi";
	string sex = "chuan";
	int salary = 7000;
};

class son_Base : public Base
{
public:
	son_Base()=default;
	son_Base(string n, string sx, string x, string w, int s) :
		Base(n, sx, x, w, s) {};
	~son_Base() = default;
};

class s_son_Base : public son_Base
{
public:
	s_son_Base() = default;
	s_son_Base(string n, string sx, string x, string w, int s) :
		son_Base(n, sx, x, w, s) {};
	~s_son_Base() = default;
	void s_test(Base&) { cout << "yes" << endl; }
	using son_Base::xue;
};

void test(Base&b)
{
	cout << b.xue << endl;
	return;
}

int main()
{
	Base x,y;
	son_Base xiao_y;
	s_son_Base x_x_y;


	Base *p = &y;
	xiao_y.memfcn(x);
	x_x_y.memfcn(x);


	system("pause");
	return 0;
}