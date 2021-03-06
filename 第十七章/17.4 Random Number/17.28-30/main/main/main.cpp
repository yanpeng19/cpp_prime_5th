// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <time.h>

using namespace std;

unsigned int get()
{
	static default_random_engine e(time(0));
	static uniform_int_distribution<unsigned> u(0, 100);
	return u(e);
}

unsigned int get(unsigned int i)
{
	static default_random_engine e(i);
	static uniform_int_distribution<unsigned> u(0, 100);
	return u(e);
}

unsigned int get(const unsigned int &i,const unsigned &min,const unsigned &max)
{
	static default_random_engine e(i);
	static uniform_int_distribution<unsigned> u(min,max);
	return u(e);
}

int main()
{
	cout << get(5,60,2000) << endl;
	system("pause");
	
	return 0;
}
