// 13.1.5.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

static string num("100000001");
class Employee
{
public:
	Employee() :number(num)
	{ int i = stoi(num);
	stringstream ss(num);
	ss << ++i;
	ss >> num;
	};
	Employee(string & s) :number(num),name(s)
	{
		int i = stoi(num);
		stringstream ss(num);
		ss << ++i;
		ss >> num;

	}

	Employee(const string & s) :number(num), name(s)
	{
		int i = stoi(num);
		stringstream ss(num);
		ss << ++i;
		ss >> num;

	}

	Employee(Employee & e):name(e.name)
	{
		int i = stoi(num);
		stringstream ss(num);
		ss << ++i;
		ss >> num;
	}
	


//private:
	string number;
	string name;
};

int main()
{
	Employee a("dizi");
	Employee b("pangzi");
	Employee c = a;

	cout << a.number << endl;
	cout << b.number << endl;
	cout << c.number << endl;

	cout << a.name << endl;
	cout << b.name << endl;
	cout << c.name << endl;
	system("pause");
    return 0;
}

