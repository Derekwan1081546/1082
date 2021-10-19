#include<iostream>
#include<map>
#include<vector>
using namespace std;
//vector<int> twoSum(vector<int>& nums, int target)
//{
//    map<int, int> m;
//    vector<int> res;
//    for (int i = 0; i < nums.size(); ++i) {
//        m[nums[i]] = i;
//    }
//    for (int i = 0; i < nums.size(); ++i) {
//        int t = target - nums[i];
//        if (m.count(t) && m[t] != i) {
//            res.push_back(i);
//            res.push_back(m[t]);
//            break;
//        }
//    }
//    return res;
//}
int main()
{
    int t, target, size, numbers;
    vector<int>num;
    vector<int> ans;
    ans.push_back(0);
    ans.push_back(0);
    cin >> t;
    for (int k = 0; k < t; k++)
    {
        cin >> target;
        cin >> size;
        for (int i = 0; i < size; i++)
        {
            cin >> numbers;
            num.push_back(numbers);
        }
        for (int i = 0; i < size; i++)
        {
            for (int j = i + 1; j < size; j++)
            {
                if ((num[i] + num[j]) == target)
                {
                    ans[0]=i;
                    ans[1]=j;
                }
            }
        }
        //num = twoSum(num, target);
        cout << ans[0] << " " << ans[1] << endl;

        num.clear();
    }

	return 0;
}