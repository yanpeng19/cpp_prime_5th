// main.cpp: 定义控制台应用程序的入口点。
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

using namespace std;



class QueryResault
{
	friend ostream& print(std::ostream&, const QueryResault&);

public:
	using line_no = vector<string>::size_type;
	QueryResault(string s, shared_ptr<set<line_no>> p, shared_ptr <StrBlob> f) :
		souht(s), lines(p), file(f) {};

private:
	string souht;
	shared_ptr<set<line_no>> lines;
	shared_ptr<StrBlob> file;
};




class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	//QueryResault query(const string &) const;
	tuple<string, shared_ptr<set<unsigned>>, shared_ptr<StrBlob>> query(const string &) const;

	//private:
	map<std::string, std::shared_ptr<set<line_no>>> wm;
	//shared_ptr<vector<string>> file;
	shared_ptr<StrBlob> file;                        //file 中存入是每行的文字
};

TextQuery::TextQuery(std::ifstream &in_file) :file(new StrBlob)
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

//
//QueryResault
//TextQuery::query(const string & couht) const
//{
//	static shared_ptr<set<line_no>> nodata(new set<line_no>);
//	auto loc = wm.find(couht);           // 查找单词，如果成功，返回单词所在行数 形式为： map<string,shared_ptr<set<int>>::iterator 
//	if (loc == wm.cend())
//		return QueryResault(couht, nodata, file);
//	else
//		return QueryResault(couht, loc->second, file);
//}

tuple<string, shared_ptr<set<unsigned>>, shared_ptr<StrBlob>>
TextQuery::query(const string & couht) const
{
	static shared_ptr<set<line_no>> nodata(new set<line_no>);
	auto loc = wm.find(couht);           // 查找单词，如果成功，返回单词所在行数 形式为： map<string,shared_ptr<set<int>>::iterator 
	if (loc == wm.cend())
		return make_tuple(couht, nodata, file);
	else
		return make_tuple(couht, loc->second, file);
}

//ostream & print(std::ostream &os, const QueryResault &qr)
//{
//	os << qr.souht << "occurs " << qr.lines->size() << " times"
//		<< endl;
//	for (auto num : *qr.lines)
//	{
//		os << "\t(line " << num + 1 << ") "
//			<< *(qr.file->begin() + num) << endl;
//	}
//	return os;
//}

ostream & print(std::ostream &os, const tuple<string, shared_ptr<set<unsigned>>, shared_ptr<StrBlob>> &qr)
{
	os << get<0>(qr) << "occurs " << get<1>(qr)->size() << " times"
		<< endl;
	for (auto num : *get<1>(qr))
	{
		os << "\t(line " << num + 1 << ") "
			<< *(get<2>(qr)->begin() + num) << endl;
	}
	return os;
}

void RunQuery(ifstream & infile)
{
	TextQuery tq(infile);
	/*tq 内部存储了文件地图，其结构是
	{
	shared_str file<vector<string>>  存入每行的string内容
	map<string,shared_ptr<set<int>>
	即文件中每个单词的 内容和对应的行数
	}
	*/

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

