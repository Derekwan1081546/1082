#include<iostream>
using namespace std;
int main()
{
	char matrix[200][200];
	int n = 0, m = 0, t = 1;
	while (cin >> n >> m && n != 0 && m != 0)
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				cin >> matrix[j][i];
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < m; j++) 
			{
				if (matrix[j][i] == '.')
				{
					int count = 0;
					if (i > 0 && matrix[j][i - 1] == '*') count++;
					if (i < n - 1 && matrix[j][i + 1] == '*') count++;
					if (j > 0 && matrix[j - 1][i] == '*') count++;
					if (j < m - 1 && matrix[j + 1][i] == '*') count++;
					if (i > 0 && j > 0 && matrix[j - 1][i - 1] == '*') count++;
					if (i > 0 && j < m - 1 && matrix[j + 1][i - 1] == '*') count++;
					if (i < n - 1 && j > 0 && matrix[j - 1][i + 1] == '*') count++;
					if (i < n - 1 && j < m - 1 && matrix[j + 1][i + 1] == '*') count++;
					matrix[j][i] = ('0' + count);
				}
			}
		}
		if (t > 1) cout << endl;
		cout << "Field #" << t++ << ":" << endl;
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				cout << matrix[j][i];
			}
			cout << endl;
		}
	}
	return 0;
}