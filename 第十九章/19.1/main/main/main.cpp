// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>

using namespace std;

void * operator new (size_t t)
{
	void* mem = malloc(t);
	if (mem)
		return mem;
	else throw bad_alloc();
}

void operator delete(void *mem) noexcept
{
	free(mem);
}


int main()
{
	int *p = new int (42);
	cout << *p << endl;
	delete p;

	system("pause");
    return 0;
}

