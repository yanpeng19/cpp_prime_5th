// 13.3 交换赋值 swap.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "stdafx.h"
#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <algorithm>

using namespace std;



class HasPtr
{
	friend void swap(HasPtr &, HasPtr&);
public:
	//HasPtr(const std::string &s = std::string()) :                   //默认构造函数
	//ps(new std::string(s)), i(0),/* use(new std::size_t(1))*/ceshi("dizi") {};
	HasPtr(const string &s) :
		ps(new std::string(s)), i(0) {};
	HasPtr(const HasPtr & hp) :                                       //拷贝控制的初始化
		ps(new string(*hp.ps)), i(hp.i)/* use(hp.use)*/ {};

	HasPtr& operator =(HasPtr  hp)
	{

		/*if (--*use == 0)
		{
		delete ps;
		delete use;
		}*/

		swap(*this, hp);
		//use = hp.use;
		return *this;
	}


	~HasPtr()
	{
		//delete ps;
		//if (--*use == 0)
		//{
		//	delete ps;
		//	delete use;
		//	//cout << "shifang neicun " << endl;
		//}
	}
	string ceshi;

	//private:
	std::string *ps;
	int i;
	//std::size_t *use;

};

bool xiaoyu(HasPtr &hp, HasPtr &hp2)
{
	return hp.ps < hp2.ps ? 1 : 0;
}

void swap(HasPtr &rht, HasPtr &lht)
{
	using std::swap;
	swap(rht.ps, lht.ps);
	swap(rht.i, lht.i);
	cout << "交换一次" << endl;
}

class TreeNode
{

public:
	TreeNode(const string &s = string()) :
		value(new std::string(s)), count(0), /*left(new TreeNode), right(new TreeNode),*/use(new size_t(1)) {};

	TreeNode(TreeNode & tn) :
		value(tn.value), count(tn.count), left(tn.left), right(tn.right), use(tn.use)
	{
		++*use;
	}

	TreeNode& operator =(const TreeNode & tn)
	{
		++*tn.use;
		if (--*use == 0)
		{
			delete value;
		}
		value = tn.value;
		count = tn.count;
		left = tn.left;
		right = tn.right;
	}

	~TreeNode()
	{
		if (--*use == 0)
		{
			delete value;

		}
		cout << "xigou hanshu zhixing" << endl;

		cout << " " << endl;
	}


private:
	std::string *value;
	int count;
	TreeNode *left;
	TreeNode *right;
	size_t *use;
};

class BinStrTree
{
public:
	BinStrTree() = default;
	BinStrTree(TreeNode& tn) :
		root(&tn) {};
	BinStrTree(BinStrTree& bt) :
		root(bt.root) {};
	BinStrTree &operator =(BinStrTree &bt)
	{
		root = bt.root;
	}
	~BinStrTree() = default;

private:
	TreeNode *root;
};

int main()
{
	HasPtr a("dizi");
	HasPtr b("baobao");
	HasPtr c("guaidizi");
	HasPtr d("xiao diz");
	vector<HasPtr> VH;
	VH.push_back(a);
	VH.push_back(b);
	VH.push_back(c);
	VH.push_back(d);

	sort(VH.begin(), VH.end(), xiaoyu);

	for (auto a : VH)
		cout << *a.ps << endl;

	system("pause");
	return 0;
}

