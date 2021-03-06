// 14.41.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <fstream>

using namespace std;

struct fun_1
{
public:
	fun_1()=default;
	fun_1( string ca, string cb) :a(ca), b(cb) {};
	bool operator()(const string a,const string b) { return a.size() < b.size(); };

private:
	string a;
	string b;
};

void elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
	fun_1 f1;
	elimDups(words);
	stable_sort(words.begin(), words.end(),f1);

	auto wc = find_if(words.begin(), words.end(),
		[sz](const string &a)
	{return a.size() >= sz; });

	auto count = words.end() - wc;
	cout << count << " " << "words"<< " of lengt " << sz << " or longer" << endl;
	for_each(wc, words.end(),
		[](const string &s) {cout << s << " "; });
}

int main()
{
	ifstream in("D://story.txt");
	vector<string> vs;
	if (in)
	{
		string word;
		while (in >> word)
			vs.push_back(word);
		biggies(vs, 5);
	}
	
	system("pause");
    return 0;
}

