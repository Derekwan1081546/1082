#include<iostream>

using namespace std;

bool go(bool** route, int node1, int* node2, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (route[node1][i] == 1 && node2[i] == 0)
		{
			return true;
		}
	}
	return false;
}
int main()
{
	int n, a, s, node1, node2;
	
	cin >> n;
	while (n!=0)
	{
		cin >> a;
		bool** route = new bool* [a]();
		for (int j = 0; j < a; j++)
		{
			route[j] = new bool[a]();
		}
		cin >> s;
		while (s != 0)
		{
			cin >> node1 >> node2;
			route[node1][node2] = 1;
			route[node2][node1] = 1;
			s--;
		}
		int* past = new int[a]();
		past[0] = 1;
		for (int i = 1; i < a; i++)
		{
			if (!route[0][i])
			{
				int node = 0;
				int node2;
				for (int k = 0; k < a; k++)
				{
					for (int l = k; l < a; l++)
					{
						if (route[node][i])
						{
							route[0][i] = 1;
							route[i][0] = 1;
							break;
						}
						if (route[node][l] && past[l] == 0)
						{
							route[0][l] = 1;
							route[l][0] = 1;
							node2 = node;
							past[l] = 1;
							node = l;
							if (!go(route, node, past, a))
							{
								node = node2;
							}
							l = k - 1;
						}
						if (route[0][i]) 
						{
							break;
						}
					}
					if (route[0][i])
					{
						break;
					}
					for (int j = 1; j < a; j++) 
					{
						past[j] = 0;
					}
				}
			}
		}
		delete[] past;
		bool connected = 1;
		for (int j = 1; j < a; j++)
		{
			if (!route[0][j])
			{
				connected = 0;
				cout << "disconnected" << endl;
				break;
			}
		}
		if (connected)
		{
			cout << "connected" << endl;
		}
		for (int i = 0; i < a; i++)
		{
			delete[] route[i];
		}
		delete[] route;
		n--;
	}
	system("pause");
	return 0;
}