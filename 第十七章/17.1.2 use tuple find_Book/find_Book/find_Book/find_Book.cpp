// find_Book.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include "Sales_data.h"
#include <algorithm>
#include <numeric>

using namespace std;

using matchs = tuple<vector<Sales_data>::size_type,
	               vector<Sales_data>::const_iterator, 
	               vector<Sales_data>::const_iterator>;

using matchs1 = tuple<vector<Sales_data>::size_type,
	pair<vector<Sales_data>::const_iterator,
	vector<Sales_data>::const_iterator>>;


////17.4
//vector<matchs> find_Book(const string&s, const vector<vector<Sales_data>> &file)
//{
//	vector<matchs> ret;
//	for (auto it = file.cbegin(); it != file.cend();it++)  //  a is  vector<Sales_data>::iterator  every bookstore's Sales_data
//	{
//
//		auto found = equal_range(it->cbegin(), it->cend(), s, compare_isbn);
//		if (found.first != found.second)
//			ret.push_back(make_tuple(it-file.cbegin(),found.first,found.second));
//
//	}
//	return ret;
//}

//17.5
//vector<matchs1> find_Book(const string&s, const vector<vector<Sales_data>> &file)
//{
//	vector<matchs1> ret;
//	for (auto it = file.cbegin(); it != file.cend(); it++)  //  a is  vector<Sales_data>::iterator  every bookstore's Sales_data
//	{
//
//		auto found = equal_range(it->cbegin(), it->cend(), s, compare_isbn);
//		if (found.first != found.second)
//			ret.push_back(make_tuple(it - file.cbegin(), make_pair(found.first, found.second)));
//
//	}
//	return ret;
//}

//17.6
class matchs2
{
public:
	matchs2(const Sales_data& s, const size_t&size) :
		data(s), sz(size) {};
	const Sales_data & data;
	size_t sz;
};

vector<matchs2> find_Book(const string&s, const vector<vector<Sales_data>> &file)
{
	vector<matchs2> ret;
	size_t i = 0;
	for (auto it = file.cbegin(); it != file.cend(); it++)  //  a is  vector<Sales_data>::iterator  every bookstore's Sales_data
	{
		
		auto found = equal_range(it->cbegin(), it->cend(), s, compare_isbn);
		if (found.first != found.second)
			ret.push_back(matchs2(*found.first,i));

	}
	return ret;
}


int main()
{

	Sales_data a("xiaodizi", 5.5, 2);
	vector<vector<Sales_data>> file{ {a},{a},{a} };
	string s;
	while(cin >> s)
	{
		auto trans = find_Book(s, file);
		if (trans.empty())
		{
			cout << "no sales" << endl;
			continue;
		}
		//17.4
		/*for (auto store : trans)
		{
			cout << "store: " << get<0>(store) << "sales";
			Sales_data temp(s);
			for (auto a = get<1>(store);a != get<2>(store); a++)
			{
				temp += *a;
			}
			cout << a << endl;
		}*/

		//17.5
	/*	for (auto store : trans)
		{
			cout << "store: " << get<0>(store) << "sales";
			Sales_data temp(s);
			for (auto a = get<1>(store).first; a != get<1>(store).second; a++)
			{
				temp += *a;
			}
			cout << a << endl;
		}*/
		 
		//17.6
		Sales_data temp(s);
		for (auto store : trans)
		{
			
			cout << "store: " << store.sz << "sales";
			temp += store.data;
			cout << temp << endl;
		}


	}


    return 0;
}

