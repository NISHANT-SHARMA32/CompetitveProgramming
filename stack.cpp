/*
Author: Nishant Sharma
Created: 2026-03-13 15:12:51
*/
#include <bits/stdc++.h>
using namespace std;

// ========== DEBUGGER ========== //
template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type>
ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const auto &x : v) os << sep << x, sep = ", "; return os << '}'; }
#include <queue>
#include <stack>
#include <bitset>
template<typename T> ostream& operator<<(ostream &os, queue<T> q) { os << "queue{"; string sep; while (!q.empty()) os << sep << q.front(), q.pop(), sep = ", "; return os << "}"; }
template<typename T> ostream& operator<<(ostream &os, stack<T> s) { os << "stack{"; string sep; while (!s.empty()) os << sep << s.top(), s.pop(), sep = ", "; return os << "}"; }
template<typename T> ostream& operator<<(ostream &os, priority_queue<T> pq) { os << "pq{"; string sep; vector<T> v; while (!pq.empty()) v.push_back(pq.top()), pq.pop(); reverse(v.begin(), v.end()); for (auto x : v) os << sep << x, sep = ", "; return os << "}"; }
template<size_t N> ostream& operator<<(ostream &os, bitset<N> b) { os << b.to_string(); return os; }

void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#define LOCAL
#ifdef LOCAL
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif
// ========== DEBUGGER END ========== //

#define endl '\n'
#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, 1, 0, -1};

class Solution {
  public:
    int solve(vector<int> &nums, int n, int prev, int index, vector<vector<int>> &dp){
        if(index >= n) return 0;
        if(dp[index][prev + 1] != -1) return dp[index][prev + 1];

        int notTake = solve(nums, n, prev, index + 1, dp);

        int take = 0;
        if(prev == -1 || nums[prev] < nums[index]){
            take = 1 + solve(nums, n, index, index + 1, dp);
        }

        return dp[index][prev + 1] = max(take, notTake);
    }
    int longestBitonicSequence(int n, vector<int> &nums) {
        vector<vector<int>> dp1(n + 1, vector<int>(n + 1, -1));
        vector<vector<int>> dp2(n + 1, vector<int>(n + 1, -1));
        
        int l = solve(nums, n, -1, 0, dp1);
        reverse(begin(nums),end(nums));
        int r = solve(nums, n, -1, 0, dp2);
        
        debug(dp1);
        debug(dp2);

        return 0;
    }
};


void solve() {
    int n = 5;
    vector<int> nums = {1, 11, 2, 10, 4, 5, 2, 1};
    
    Solution s1;
    cout << s1.longestBitonicSequence(n, nums);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    // cin >> tc;
    for (int t = 1; t <= tc; t++) {
        solve();
    }
}