#include<algorithm>
#include<iostream>
#define MAX 10000
using namespace std;
int abs(int a)
{
    return (a >= 0) ? a : -a;
}
int gcd(int a, int b)
{
    return (b == 0) ? a : gcd(b, a % b);
}
int main()
{
    int max = 0;
    int n[MAX], num, i, j;

    while (1) {
        cin >> n[0];

        if (n[0] == 0)break;
        int n_len = 1;
        while (cin >> n[n_len])
        {
            if (n[n_len] == 0)break;
            n_len++;
        }

        // if(n_len==0)break;
        max = 0;
        for (i = 0; i < n_len - 1; i++)
            for (j = i + 1; j < n_len; j++)
            {
                if (n[j] - n[i] != 0)max = gcd(abs(n[j] - n[i]), max);
            }
        cout << max << endl;
        for (i = 0; i < n_len; i++)n[i] = 0;
    }
    system("pause");
    return 0;
}