// 11.2.3 pair.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <map>
#include <set>
#include <string>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;


struct My_class
{
	string s;
	int i;

public:
	bool empty()
	{
		if (s.empty())
			return true;
		return false;
	}
};
int main()
{
	vector<pair<string,int>> mv;
	pair<string, int> temp;
	vector<My_class> v_m;
	My_class m;
	string t_s;
	int t_i;

	while (cin >> t_s&&t_s!="exit")                 //形成v_m;
	{
		m.s = t_s;
		cout << "Please input int : " << endl;
		while (cin >> t_i && t_i != -1)
		{
			m.i = t_i;
		}
		v_m.push_back(m);
	}

	for (auto a : v_m)
	{
		//temp = make_pair(a.s, a.i);
		//temp = pair<string, int>(a.s, a.i);
		pair<string, int> temp(a.s, a.i);
		mv.push_back(temp);
	}

	for (auto a : mv)
	{
		cout << a.first << " " << a.second << endl;
	}

	system("pause");
    return 0;
}

