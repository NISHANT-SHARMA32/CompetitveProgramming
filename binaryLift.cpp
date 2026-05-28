/*
Author: Nishant Sharma
Created: 2025-07-09 15:19:41
.
.
*/
#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void debug_out() { cerr << endl; }
template<typename Head, typename... Tail> void debug_out(Head H, Tail... T) { cerr << ' ' << H; debug_out(T...); }
#define LOCAL
#ifdef LOCAL
#define debug(...) cerr << "(" << #__VA_ARGS__ << "):", debug_out(__VA_ARGS__)
#else
#define debug(...)
#endif

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

/*
    find the kth parent -> first we have to maintain the parent map and then k step to find the kth parent
    but this will give TC- O(n + q*k)
    n for dfs traversal for findding the parents 
    q * k for each query 

    we can optimize the query part to logk for each query bcz every number can be repersented in the form of 2^POWER.

    space complexity we will store logn parent for each node

    nlogn will be the space complexity.   n for node and for each node logn parents
*/

void dfs(int node, int par, vector<int> adj[], vector<vector<int>> &dp){
  dp[node][0] = par;

  for(int i = 1; i <= 16; ++i){
    dp[node][i] = dp[dp[node][i-1]][i-1];
  }

  for(auto it : adj[node]){
    if(it == par) continue;
    dfs(it,node,adj,dp);
  }
}

void solve() {
    vector<int> adj[n+1];
    for(int i = 0; i < n-1; ++i){
      int u, v;
      cin >> u >> v;
      adj[v].slide(u);
      adj[u].slide(v);
    }

    vector<vector<int>> dp(n+1,vector<int>(17,0));
    dfs(1,0,adj,dp);

    //now only we have to print the kth ancestor
    int node, k; // these two will be given to us
    cin >> node >> k;
    int bit = 0;
    while(k){
      if(k&1){
          node = dp[node][bit];
      }
      bit++;
      k = k >> 1;
    }
    cout << node << endl;
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