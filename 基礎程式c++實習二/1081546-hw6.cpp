#include<iostream>
#include<string>
using namespace std;
string rule;
int num;
string words[105];
string numbers[10] = { "0","1","2","3","4" ,"5" ,"6" ,"7" ,"8" ,"9" };
string output[300];
void PrintOut(int pos)
{
	if (pos == rule.size())
	{
		for (int i = 0; i < pos; ++i)
		{
			cout << output[i];
		}
		cout << endl;
	}
	else
	{
		if (rule[pos] == '#')
		{
			for (int i = 0; i < num; ++i)
			{
				output[pos] = words[i];
				PrintOut(pos + 1);
			}
		}
		else
		{
			for (int i = 0; i < 10; ++i)
			{
				output[pos] = numbers[i];
				PrintOut(pos + 1);
			}
		}
	}
}
int main()
{
	while (cin >> num)
	{
		for (int i = 0; i < num; ++i)
		{
			cin >> words[i];
		}
		cout << "--" << endl;
		int numrule;
		cin >> numrule;
		while (numrule--)
		{
			cin >> rule;
			PrintOut(0);
		}
	}
	return 0;
}