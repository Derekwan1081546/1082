#include <iostream>
#include <iomanip>
using namespace std;

struct math
{
	double x[4],y[4],xt,yt;
};

int main() 
{
	math test;
	while(cin>>test.x[0]>>test.y[0])
	{
		for(int i=1;i<4;i++)
			cin>>test.x[i]>>test.y[i];	
		test.xt=test.x[0]+test.x[1]+test.x[2]+test.x[3];
		test.yt=test.y[0]+test.y[1]+test.y[2]+test.y[3];
		
		for(int i=0;i<4;i++)
		{
			for(int j=i+1;j<4;j++)
			{
				if(test.x[i]==test.x[j]&&test.y[i]==test.y[j]){
					test.xt-=(3*test.x[i]);
					test.yt-=(3*test.y[i]);
					cout << fixed <<setprecision(3) << test.xt <<" "<< test.yt << endl;
				}
			}
		}
	}	
	
	return 0;
}
