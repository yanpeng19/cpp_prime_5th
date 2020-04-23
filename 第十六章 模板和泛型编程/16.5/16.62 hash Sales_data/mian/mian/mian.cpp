// mian.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Sales_data.h"
#include <map>
#include <set>
#include <unordered_set>

using namespace std;




int main()
{
	Sales_data s1;
	Sales_data s2("112950", 20, 9.8);
	Sales_data s3("1201204", 5, 83.5);

	unordered_multiset<Sales_data> us;
	us.emplace(s1);
	us.insert(s2);
	us.insert(s3);

	for (auto a : us)
		cout << a << endl;

	system("pause");
    return 0;
}

