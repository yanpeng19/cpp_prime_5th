// 12.3.2 更改后的 文本查询.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <memory>
#include <utility>
#include <set>
#include "StrBlob.h"
#include "StrVec.h"

using namespace std;


class QueryResault;

class TextQuery
{
public:
	//using line_no = std::vector<std::string>::size_type;
	using line_no = int;
	TextQuery(std::ifstream&);
	QueryResault query(const string &) const;

//private:
	map<std::string, std::shared_ptr<set<line_no>>> wm;
	//shared_ptr<vector<string>> file;
	shared_ptr<StrBlob> file;
};

TextQuery::TextQuery(std::ifstream &in_file):file(new StrBlob)
{
	string line;
	while (getline(in_file, line)) //申请新内存，并生成地图
	{
		file->push_back(line);
		int n = file->size() - 1;
		string word;
		istringstream is_line(line);
		while (is_line >> word)
		{
			auto &s = wm[word];
			if (!s)
				s.reset(new set<line_no>);
			s->insert(n);
		}
	}
}

class QueryResault
{
	friend ostream& print(std::ostream&, const QueryResault&);

public:
	//using line_no = vector<string>::size_type;
	using line_no = int;
	QueryResault(string s, shared_ptr<set<line_no>> p, shared_ptr <StrBlob> f) :
		souht(s), lines(p), file(f) {};

private:
	string souht;
	shared_ptr<set<line_no>> lines;
	shared_ptr<StrBlob> file;
};

QueryResault 
TextQuery::query(const string & couht) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(couht);
	if (loc == wm.cend())
		return QueryResault(couht, nodata, file);
	else
		return QueryResault(couht, loc->second, file);
}

ostream & print(std::ostream &os, const QueryResault &qr)
{
	os << qr.souht << "occurs " << qr.lines->size() << " times"
		<< endl;
	for (auto num : *qr.lines)
	{
		os << "\t(line " << num + 1 << ") "
			<< *(qr.file->begin() + num) << endl;
	}
	return os;
}

void RunQuery(ifstream & infile)
{
	TextQuery tq(infile);
	while (true)
	{
		cout << " enter word to look for" << endl;
		string s;
		if (!(cin >> s) || s == "q") break;
		print(cout, tq.query(s)) << endl;
	}
}

int main()
{
	ifstream i("D://story.txt");
	RunQuery(i);
	TextQuery a(i);
	TextQuery b = a;

	cout << a.file << endl;
	cout << b.file << endl;

	system("pause");
    return 0;
}

