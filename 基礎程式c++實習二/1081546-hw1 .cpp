#include<iostream>
#include<iomanip>
using namespace std;
struct point
{
	double x1;
	double y1;
	double x2;
	double y2;
	double x3;
	double y3;
	double x4;
	double y4;
};
int main()
{
	struct point a;
	while (cin >> a.x1 >> a.y1 >> a.x2 >> a.y2 >> a.x3 >> a.y3 >> a.x4 >> a.y4)
	{
		if (a.x1 == a.x3 && a.y1==a.y3)
		{
			cout << fixed << setprecision(3) << (a.x2 + a.x4) - a.x1 << " " << (a.y2 + a.y4) - a.y1 << endl;
		}
		else if (a.x1 == a.x4 && a.y1 == a.y4)
		{
			cout << fixed << setprecision(3) << (a.x2 + a.x3) - a.x1 << " " << (a.y2 + a.y3) - a.y1 << endl;
		}
		else if (a.x2 == a.x3 && a.y2 == a.y3)
		{
			cout << fixed << setprecision(3) << (a.x1 + a.x4) - a.x2 << " " << (a.y1 + a.y4) - a.y2 << endl;
		}
		else if (a.x2 == a.x4 && a.y2 == a.y4)
		{
			cout << fixed << setprecision(3) << (a.x1 + a.x3) - a.x2 << " " << (a.y1 + a.y3) - a.y2 << endl;
		}
		else if (a.x1 == a.x2 && a.y1 == a.y2)
		{
			cout << fixed << setprecision(3) << (a.x3 + a.x4) - a.x1 << " " << (a.y3 + a.y4) - a.y1 << endl;
		}
		else
		{
			cout << fixed << setprecision(3) << (a.x1 + a.x2) - a.x3 << " " << (a.y1 + a.y2) - a.y3 << endl;
		}
	}
	return 0;
}