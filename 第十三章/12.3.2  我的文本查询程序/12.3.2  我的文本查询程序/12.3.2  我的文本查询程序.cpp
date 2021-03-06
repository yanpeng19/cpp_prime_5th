// 12.3.2  我的文本查询程序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <utility>
#include <numeric>
#include <algorithm>

using namespace std;





class Query_reasault
{
public:
	friend class TextQuery;
	Query_reasault() = default;
	//Query_reasault(TextQuery TQ) : P_TextQuery(&TQ) {};

	void push_back(const string& s) { resault.push_back(s); }
	void push_back(string& s) { resault.push_back(s); }

	vector<string> & Return() { return this->resault; };
	ostream & print(ostream & out, vector<string> resault);

	vector<string>::iterator begin() { return resault.begin(); }
	vector<string>::iterator end() { return resault.end(); }
	

private:
	vector<string> resault;
	//shared_ptr<TextQuery> P_TextQuery;
};

class TextQuery
{
public:
	TextQuery() = default;
	TextQuery(istream &i) :in_file(i) { MakeMap(in_file); };
	void MakeMap(istream& i);
	vector<string> & query(string &s,Query_reasault  &rt);

private:
	istream &in_file;
	vector<string> vs;
	map<string, vector<int>> textmap;      //关键字+出现的行数
};

ostream & Query_reasault::print(ostream & out, vector<string> resault)
{
	for (auto a : resault)
	{
		out << a;
	}
	return out;
}

void TextQuery::MakeMap(istream & i)
{
	string line, word;
	string f(",.?:![]123456789’“”\"");
	int n = 0;
	vs.push_back("");
	while (getline(i, line))
	{
		n++;
		istringstream os_line(line);
		vs.push_back(line);
		while (os_line >> word)
		{
			//处理标点符号
			while (word.find_first_of(f) != string::npos)
			{
				auto a = word.find_first_of(f);
				word.erase(a);
			}
			//map下标操作生成一个map
			auto &vi = textmap[word];
			if (vi.empty())
				vi.push_back(1);
			else(vi[0] = vi[0]++);

			vi.push_back(n);
		}
	}
	for (auto &a : textmap)
	{
		//cout << a.first << " : ";
		auto p = unique(a.second.begin()+1,a.second.end());
		a.second.erase(p, a.second.end());
		/*for (auto b : a.second)
			cout << b << " ";
		cout << endl;*/
	}
}

//此函数通过关键词进行查找，并生成格式vector<string>
vector<string>& TextQuery::query(string &s, Query_reasault  &rt)
{
	//Query_reasault rt(*this);
	if (textmap.find(s) == textmap.cend())
	{
		rt.push_back("Not found");
		return rt.Return();
	}
	auto pr = textmap.find(s);
	vector<int> &v = pr->second;
	//string sen;
	ostringstream os;
	os << s << " ";
	if (v[0] > 1)
		os << "occurs " << v[0] << " times" << endl;
	else os << "occurs " << v[0] << " time" << endl;
	rt.push_back(os.str());

	for (auto i = v.begin() + 1; i < v.end(); i++)
	{
		ostringstream os_;
		//ostringstream os(sen);
		os_ << "(line " << *i << ") " << vs[*i] << endl;
		rt.push_back(os_.str());
	}
	/*for (auto a : rt)
	{
		cout << a << endl;
	}*/
	return rt.Return();
}

void run_Queries(istream &infile)
{
	TextQuery tq(infile);
	while (true)
	{
		Query_reasault rt;
		cout << " enter word to look for, or q to quit" << endl;
		string s;
		if(!(cin >> s) || s == "q") break;
		rt.print(cout, tq.query(s,rt)) << endl;
	}

}

int main()
{
	ifstream ifile("D:/story.txt");
	if (ifile.is_open())
	{
		run_Queries(ifile);
	}
	system("pause");
    return 0;
}

