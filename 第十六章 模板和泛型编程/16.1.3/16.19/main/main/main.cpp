// main.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <list>
#include <map>
#include <iostream>


using namespace std;

template<typename T>
void print(T& t)
{
	using size_type = typename T::size_type ;
	using iter = typename T::iterator;
	iter i = t.begin();
	while (i != t.end())
		cout << *i++;

}


int main()
{
	vector<string> vc{ "baozi","xiaodizi","xiang" };

	print(vc);
	system("pause");
    return 0;
}

