// Author: Nishant Sharma
// Created: 2026-04-26 19:38:34
#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class Solution {
public:
    vector<int> findValidElements(vector<int>& nums) {
        int n = nums.size();
        vector<int> ans;


        // making left array;
        vector<int> left(n); left[0] = -1e9;
        int curr_max = nums[0];

        for(int i = 1; i < n; ++i){
            left[i] = curr_max;
            curr_max = max(curr_max, nums[i]);
        }

        vector<int> right(n); right[n - 1] = -1e9;
        curr_max = nums[n - 1];

        for(int i = n - 2; i >= 0 ; --i){
            right[i] = curr_max;
            curr_max = max(curr_max, nums[i]);
        }


        for(int i = 0; i < n; ++i){
            if(nums[i] > left[i] || nums[i] > right[i]){
                ans.push_back(nums[i]);
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    vector<int> nums = {1,2,4,2,3,2};

    Solution s;

    
    vector<int> ans = s.findValidElements(nums);

    cout << ans.size() << endl;

    for(auto it : ans){
        cout << it << " ";
    }
    return 0;
}