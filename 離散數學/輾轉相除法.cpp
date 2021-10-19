#include<iostream>
using namespace std;
int main()
{
	int a, b, t;
	while (cin >> a >> b && a != 0 && b != 0)
	{
		while (b != 0)
		{
			t = b;
			b = a % b;
			a = t;
		}
		if (b == 0)
		{
			cout << "hello" << endl;

		}
	}
	return 0;
}