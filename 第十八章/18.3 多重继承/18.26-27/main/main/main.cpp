// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Base1
{
	void print(const int&i) const
	{
		cout << i << endl;
	}
	
protected:
	int ival;
	double dval;
	char cval = 'a';

private:
	int *id;
};

struct Base2
{
	void print(double&d )const
	{
		cout << d << endl;
	}
protected:
	double fval;
private:
	double dval;
};

struct Derived :public Base1
{
	void print(string&s)const
	{
		cout << s << endl;
	}

protected:
	string sval=("dizibaobao");
	double dval;
};

struct MI : public Derived, public Base2
{
	void print(vector<double> &vt)
	{
		for(auto a:vt)
		{
			cout << a << endl;
		}
	}

	double dval = 1.0;
	void foo()
	{
		////27.a
		//int dval = 0;
		//cout << ival << endl;
		//cout << dval << endl;
		//cout <<  dvec.empty() << endl;
		//cout << sval << endl;
		//cout << Derived::sval << endl;
		//cout << Derived::dval << endl;
		//cout << Base1::cval << endl;
		//cout << Base1::dval << endl;
		//cout << Base1::ival << endl;
		//cout << Base2::fval << endl;

		//27.c
		//dval = Base1::dval + Derived::dval;
		//cout << dval << endl;

		//27.d
		//Base2::fval = dvec[dvec.size()-1];
		//cout << fval << endl;

		//27.e
		
		Derived::sval.replace(0,1, { Base1::cval });
		cout << sval << endl;
	}

protected:
	int* ival;
	vector<double> dvec{ 2.3,5.2,5,5555,2.123 };
};

int main()
{
	MI mi;
	//mi.Base1::print(42);
	mi.foo();

	system("pause");
    return 0;
}

