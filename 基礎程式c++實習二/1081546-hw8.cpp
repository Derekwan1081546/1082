#include <iostream>
#include <string>

using namespace std;

bool isPalindrome(string s, int l, int r) 
{
    while (l < r) 
    {
        if (s[l++] != s[r--])
            return false;
       
    }
    return true;
}

bool validPalindrome(string s) 
{
    int l = 0;
    int r = s.size() - 1;
    while (l < r) 
    {
        if (s[l] != s[r]) 
        {
            return isPalindrome(s, l + 1, r) || isPalindrome(s, l, r - 1);
        }
        else 
        {
            r--;
            l++;
        }
    }
    return true;
}

// Driver code to test above methods 
int main()
{
    string str;
    while (cin >> str)
    {
        validPalindrome(str);
        if (validPalindrome )
            cout << "True" << endl;
        else
            cout << "False" << endl;
    }
    
    return 0;
}