#include<iostream>
using namespace std;
int main()
{
	int T = 0, n = 0;
	string instruction[200];
	cin >> T;
	for (int t = 0; t < T; t++)
	{
		cin >> n;
		string str1, str2;
		int str3, p = 0;
		for (int i = 1; i <= n; i++)
		{
			cin >> str1;
			if (str1 == "LEFT")
			{
				instruction[i] = str1;
				p--;
			}
			else if (str1 == "RIGHT")
			{
				instruction[i] = str1;
				p++;
			}
			else
			{
				cin >> str2 >> str3;
				instruction[i] = instruction[str3];
				if (instruction[str3] == "LEFT")p--;
				else if (instruction[str3] == "RIGHT")p++;
			}
		}
		cout << p << endl;
	}

	return 0;
}