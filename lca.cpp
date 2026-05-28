/*
Author: Nishant Sharma
Created: 2025-10-14 09:15:03
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

void dfs(int node, int parent, vector<vector<int>> &adj, vector<vector<int>> &dp, vector<int> &level, int l){
    dp[node][0] = parent;

    for(int i = 1; i <= 16; ++i){
        dp[node][i] = dp[dp[node][i - 1]][i - 1];
    }
    level[node] = l;
    for(auto child : adj[node]){
        if(child == parent) continue;
        dfs(child, node, adj, dp, level, l + 1);
    }
}

int getKthparent(int node, int k, vector<vector<int>> &dp){
  int cnt = 0; 
  while(k){
    if(k&1) node = dp[node][cnt];
    cnt++;
    k = k >> 1;
  }return node;
}

void solve() {
    int n; cin >> n;
    vector<vector<int>> adj(n + 1);

    for(int i = 0; i < n - 1; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<vector<int>> dp(n + 1, vector<int> (17, 0));
    vector<int> level(n + 1, 0);
    dfs(1,0,adj,dp, level, 1);

    // this is where the lca logic starts
    int a, b; cin >> a >> b;
    if(level[a] > level[b]) swap(a,b);

    // considering a is at the lesser level
    int k = level[b] - level[a];
    b = getKthparent(b,k,dp);

    //now both are at the same level
    for(int i = 16; i >= 0; i--){
      if(dp[a][i] != dp[b][i]){
         a = dp[a][i];
         b = dp[b][i];
      }
    }
    cout << dp[a][0] << endl;
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