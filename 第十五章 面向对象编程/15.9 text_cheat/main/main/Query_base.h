#pragma once


#include "stdafx.h"
#include "StrBlob.h"
#include "QueryResault.h"
#include <memory>
#include <algorithm>

using namespace std;

class Query_base
{
	friend class Query;

protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;

	//private:
	virtual QueryResault eval(const TextQuery&) const = 0;
	virtual string rep() const = 0;

};

class Query
{
	friend Query operator~(const Query&);
	friend Query operator&(const Query&, const Query&);
	friend Query operator|(const Query&, const Query&);

public:
	//~Query() = default;
	//Query() = default;
	Query(const string&s);
	QueryResault eval(const TextQuery &t) const { return q->eval(t); };
	string rep() const { return q->rep(); }

private:
	shared_ptr<Query_base> q;
	Query(shared_ptr<Query_base> qb) :q(qb) {};
};

ostream& operator<<(ostream &os, const Query &query)
{
	return os << query.rep();
}


class Word_Query :public Query_base
{
	friend class Query;

public:
	Word_Query(const string&st) :query_word(st) {};
	QueryResault eval(const TextQuery&tq) const { return tq.query(query_word); };
	string rep() const { return query_word; };
	string query_word;
};

inline Query::Query(const string&s) : q(new Word_Query(s)) {};


class Not_Query :public Query_base
{
	friend Query operator~(const Query &operand);
	friend class Query;

public:
	Not_Query(const Query &q) :query(q) {};

	QueryResault eval(const TextQuery&tq) const;
	string rep() const { return string("~(" + query.rep() + ")"); };
	//string query_word;
	Query query;
};

QueryResault Not_Query::eval(const TextQuery &tq) const
{
	auto resault = query.eval(tq);
	auto ret = make_shared<set<line_no>>();
	//auto beg = resault.begin(), end = resault.end();
	auto sz = resault.get_file()->size();
	for (line_no n = 0; n != sz; ++n)
	{
		if (resault.find(n) == resault.end())
			ret->insert(n);
	}
	return QueryResault(rep(), ret, resault.get_file());
}

inline Query operator~(const Query &operand)
{
	return shared_ptr<Query_base>(new Not_Query(operand));
}

class Binary_Query :public Query_base
{
	friend class Query;

public:
	Binary_Query(const Query &l, const Query &r, const string &s) :
		left(l), right(r), sym(s) {};
	string rep() const { return string(left.rep() + sym + right.rep()); }

protected:
	Query left;
	Query right;
	string sym;
};

class And_Query :public Binary_Query
{
	friend Query operator&(const Query&, const Query&);
	friend class Query;

public:
	And_Query(const Query&l, const Query &r) :
		Binary_Query(l, r, "&") {};

	QueryResault eval(const TextQuery&) const;
};

Query operator&(const Query &left, const Query &right)
{
	return shared_ptr<Query_base>(new And_Query(left, right));
}

class Or_Query :public Binary_Query
{
	friend Query operator|(const Query&, const Query&);
	friend class Query;

public:
	Or_Query(const Query&l, const Query &r) :
		Binary_Query(l, r, "|") {};

	QueryResault eval(const TextQuery&) const;
};

Query operator|(const Query &left, const Query &right)
{
	return shared_ptr<Query_base>(new Or_Query(left, right));
}

QueryResault Or_Query::eval(const TextQuery&tq) const
{

	auto l = left.eval(tq), r = right.eval(tq);
	auto line = make_shared<set<line_no>>(l.begin(), l.end());
	line->insert(r.begin(), r.end());
	return QueryResault(rep(), line, l.get_file());
}

QueryResault And_Query::eval(const TextQuery &tq) const
{
	auto l = left.eval(tq);
	auto r = right.eval(tq);
	auto line = make_shared<set<line_no>>();

	set_intersection(l.begin(), l.end(), r.begin(), r.end(), inserter(*line, line->begin()));

	return QueryResault(rep(), line, l.get_file());
}

