#include<iostream>
#include<string>
const int correctcount = 64;
const char symbol = '/';
using namespace std;
int main()
{
	int values[200];
	values['W'] = 64;
	values['H'] = 32;
	values['Q'] = 16;
	values['E'] = 8;
	values['S'] = 4;
	values['T'] = 2;
	values['X'] = 1;
	string line;
	while (cin >> line && line != "*")
	{
		int correct = 0, currentCount = 0;
		for (int i = 0; i < line.size(); ++i)
		{
			if (line[i] == symbol)
			{
				if (currentCount == correctcount)
				{
					++correct;
				}
				currentCount = 0;
			}
			else
			{
				currentCount += values[line[i]];
			}
		}
		cout << correct << endl;
	}
	return 0;
}