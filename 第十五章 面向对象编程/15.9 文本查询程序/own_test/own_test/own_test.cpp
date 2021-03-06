// own_test.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

static map<int, string> f_story;

class Data
{
public:
	Data() = default;
	Data(string st) : s(st) {};
	//Data(set<int> set_int) :st(set_int) {};

	string s;
	set<int> st;
};

class Pro
{
public:
	Pro() = default;
	Pro(Data &item): 
		l()
		//r(string(item.s.begin() + l.s.find_first_of(f) - 1,item.s.end())),
		//sym(item.s[item.s.find_first_of(f)])
	{
		auto p = item.s.find_first_of(f);
		while (p<1 || p>item.s.size())
		{
			cout << "输入错误，请按照格式输入" << endl;
			return;
		}

		l.s = string(item.s.begin()+1,item.s.begin() + item.s.find_first_of(f));
		r.s = string(item.s.begin() + p+1, item.s.end());
		sym = item.s[p];
		
		//string temp(string(item.s.begin() + l.s.find_first_of('(') + 1, item.s.begin() + l.s.find_first_of(f)))

		if (item.s[0] == '~')
			rev = -1;
		if (l.s.find_first_of('(') != std::string::npos)
		{
			Data d(l.s);
			Pro p(d);
			l.st = p.resault();
			l.s.clear();
		}

		if (r.s.find_first_of('(') != std::string::npos)
		{
			Data d(r.s);
			Pro p(d);
			r.st = p.resault();
			r.s.clear();
		}

	};
	
	void stoset()
	{
		if (l.s.size())
		{
			for (auto a : f_story)
			{
				if (auto p = a.second.find(l.s)!=std::string::npos)        //逐行扫面，如果存在，记入行数set<int> st
					l.st.insert(a.first);
			}
			l.s.clear();
		}
		if (r.s.size())
		{
			for (auto a : f_story)
			{
				if (a.second.find(r.s)!=std::string::npos)        //逐行扫面，如果存在，记入行数set<int> st
					r.st.insert(a.first);
			}
			r.s.clear();
		}

	}

	set<int> resault()
	{
		stoset();
		if (sym == '&')
			for (auto a : l.st)
				if (auto b = r.st.find(a) == r.st.cend())
					l.st.erase(a);
			
		
		if (sym == '|')
			for (auto a : r.st) l.st.insert(a);

		if (sym == -1)
		{
			set<int> temp;
			for (int i = 1; i <= (--f_story.end())->first; i++)   //创建一个完整set<int> 并从中剔除 现有数据，进行取反
				temp.insert(i);

			for (auto a : l.st)
				if (auto p = temp.find(a) != temp.cend())
					temp.erase(p);

			l.st = temp;
		}
		return l.st;
	}
private:
	Data l;
	Data r;
	char sym;
	int rev;

	string f = "&|";
};

	//对字符串进行处理
	/*逻辑:
			1.函数名  Item Get_(Item&){}; 传递进去一个 Itme类，得到一个string为空，而set<int>存在结果的 Item.

	        2.确定优先级：通过循环查找，找到最考前的"("然后找到最外侧的 ")" 符号，将他们中间的内容截取出来，并且判断（符号前是否有取反的“~”符号，如果有就一起截取。
			  得到一个类似“ ~（alis|~（set&bot)"的字符串，并转化成Item类型。


			3.检查Item是否为空，如果不为空，则说明字符串内有内容，仍需要处理
			  将字符串s “ ~（alis|（set&bot)) " 划分为四个部分：

			  int mian(){

			  Item is(s);
			  Item r = Get_(s);
			  prin(r);  //根据r的sent<int> 内容，来输出结果。
			  
			  }

			  Item Get_(Item&it)
			  {
			    chuli c(it);
				return c.resault();
			  }
			  
			  class chuli
			  {
			     chuli(Item &item):Item l(string(item.first_of("(")+1,item.find_first_of("|"|&") ),
				                   Item r(string(item.find_first_of("|""&")+1,item.end()-1), 
								   Symbol(temp.find_first_of("|""&"))
								   {
								     if(l.find_first_of("("!=std::string::nops)
									 {
									     Item l = Get_(l);
									 }
									 if(r.find_first_of("("!=std::string::nops)
									 {
									     Item r = Get_(r);
									 }
								     if(*item.begin()=="~")
									 rev = -1;
								   }
		
				 
				  
				  int rev = -1 ;  取反符号，默认为0.如果字符串有“~”，则值为-1；

				  pucblic:
				     set<int> resault(item& l,item r,Symbol,rev);          // 处理关系，返回要set结果,并且把l和r的string 部分清空
					 {
					    1.得到符号是| 还是&
						2.分别检查l和r的string部分，如果不为空，就通过查找函数，将item中的string遍历全文，并将行数，存到set<int>中
						3.根据符号不同 处理两个item,得到重叠/累计的set<int>，并将string 清空
						4.判断是否取反 如果取对set<int> 进行 相应操作
						5.retrun 处理后的set<int>
					 }
			  }



			  


			4.将类传递给计算函数，得到一结果参数，计算函数如下：
			  Item f(Item r,Item l);

			5.将结果参数和没有计算外的另外一部分string,一起传递到新的计算函数中
			6.最终结果以 set<int> 形势返回来

			*/


int main()
{

	ifstream in("D:/story.txt");
	string line;
	int i = 1;
	set<int> st;
	string s;

	while (getline(in,s)) //读数据 存行
		if(s.size()>0)
		  f_story[i++] = s;

	//for (auto a : f_story)
	//{
	//	cout << a.first << a.second << endl;
	//}
	
	while (getline(cin,s))
	{
		Data ds(s);
		Pro p(ds);
		st = p.resault();
		for (auto a : st)
		{
			cout << a << "  " << f_story[a] << endl;
		}
	}
    return 0;
}

