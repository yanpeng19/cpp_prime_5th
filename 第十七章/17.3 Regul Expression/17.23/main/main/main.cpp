

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;
 
int main()
{
	string s("(\\d{5})(([-])(\\d{4}))?");
	regex r(s);

	string temp;
	while (cin >> temp)
	{
		smatch resault;
		regex_search(temp, resault, r);
		if (resault.size()&&resault.prefix()==""&&resault.suffix()=="")
		{
			cout << "valid :" << temp << endl;
		}
		else cout << "not valid :" << temp << endl;

	}
	system("pause");
    return 0;
}

