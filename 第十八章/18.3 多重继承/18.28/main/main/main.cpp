// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Base {
	void bar(int) { return; }; //Accessed without qualification, not defined with int arg anywhere
protected:
	int ival;//Need qualification, VMI will use Derived2::ival by default
};

struct Derived1 : virtual public Base {
	void bar(char) { return; };//Accessed with no qualification, VMI derives from Derived1 which derives from Base.
	void foo(char) { return; };//Need qualification, can convert arg between two foos.
protected:
	char cval;//need to qualify ambiguous with other cval.
};

struct Derived2 : virtual public Base {
	void foo(int) { return; };//Need qualification, can convert arg between two foos.
protected:
	int ival;//Accessed with no qualification.
	char cval;//need to qualify ambiguous with other cval.
};
class VMI : public Derived1, public Derived2 { };

int main()
{
	VMI v;
	cout << v.ival << endl;
	cout << v.cval << endl;
	cout << v.Base::ival << endl;
	cout << v.Derived1::cval << endl;
	v.Base::bar(1);
	v.Derived1::bar('e');
	v.Derived1::foo('c');
	v.Derived2::foo(1);
	


	system("pause");
    return 0;
}

