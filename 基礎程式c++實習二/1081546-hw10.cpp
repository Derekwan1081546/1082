#include<iostream>
using namespace std;
int main()
{
	int testcase;
	cin >> testcase;
	for (int k = 0; k < testcase; k++)
	{
		int g[10][10] = {};
		for (int i = 0; i < 9; i += 2)
		{
			for (int j = 0; j <= i; j += 2)
			{
				cin >> g[i][j];
			}
		}
		int a, b, c;
		for (int i = 8; i > 0; i -= 2)
		{
			for (int j = 0; j < i; j += 2)
			{
				a = g[i][j];
				b = g[i][j + 2];
				c = g[i - 2][j];
				g[i][j + 1] = (c - a - b) / 2;
				g[i - 1][j] = g[i][j] + g[i][j + 1];
				g[i - 1][j + 1] = g[i][j + 1] + g[i][j + 2];
			}
		}
		for (int i = 0; i < 9; i++) 
		{
			cout << g[i][0];
			for (int j = 1; j <= i; j++) 
			{
				cout << " " << g[i][j];
			}
			cout << endl;
		}
	}
	//system("pause");
	return 0;
}