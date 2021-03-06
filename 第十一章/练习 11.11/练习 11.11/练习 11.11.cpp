// 练习 11.11.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <set>
#include <string>
#include <iostream>


using namespace std;                       

struct My_class
{
	string name;
	int score;
	bool operator< (const My_class &mc)const            // 如果MAP关键字要使用 自定义类，必须重载"<" 符号
	{
		if (score < mc.score)
		{
			return true;
		}

		return false;
	}
	
};

bool Sget(const My_class &a,const My_class &b)
{
	return a.score < b.score ? a.score : b.score;
}

int main()
{
	My_class di{ "wangdizi",100 };
	My_class pang{ "yanpangzi",50 };

	map<My_class, int> my_map;

	string word;
	string word2;
	while (cin >> word )
	{
		my_map[di] = 1;
		my_map[pang] = 2;
	}

	for (auto a : my_map)
	{
		cout << a.first.name << ' ' << a.second;
		cout << endl;
	}
	system("pause");
    return 0;
}

