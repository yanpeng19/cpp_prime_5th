// 15.9 新的文本查询程序.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <memory>
#include <utility>
#include <set>
#include "StrBlob.h"
#include "QueryResault.h"
#include "Query_base.h"


using namespace std;

int main()
{
	ifstream f("D:/story.txt");
	TextQuery tq(f);


	system("pause");

    return 0;
}

