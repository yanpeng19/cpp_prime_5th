#include "stdafx.h"
#include <numeric>
#include <algorithm> 
#include <iostream>
#include <iterator>
#include <vector>
#include <list>

using namespace std;


int main()
{
	istream_iterator<int> int_it(std::cin), eof;
	vector<int> int_v;
	list<int> int_l;
	int n;
	while (int_it != eof)
	{
		int_v.push_back(*int_it++);
	}

	int_l.insert(int_l.begin(),int_v.size(), 0);
	sort(int_v.begin(), int_v.end());
	auto b = unique_copy(int_v.begin(), int_v.end(), int_l.begin());
	//int_l.erase(b, int_l.end());

	for(auto a : int_l)
		cout << a << endl;

	system("pause");
	
    return 0;
}

