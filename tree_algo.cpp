/*
Author: Nishant Sharma
Created: 2025-07-07 14:18:09
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
    if u is the ancestor of v 

    in(u) < in(v) < out(v) < out(u)    this should be the order
    dfs - o(n)

    we can do the bfs and dfs in tree taking parent only 

    but for graph we have to take the vis array in order to avoid the cycle.

*/

int t = 0;
map<int,pair<int,int>> mp;

void dfs(int node, vector<int> &seen, vector<vector<int>> &adj){
    cout << node << " ";
    mp[node].first = t;
    seen[node] = 1;
    t++;

    for(auto &newNode : adj[node]){
        if(!seen[newNode]) dfs(newNode,seen,adj);
    }

    mp[node].second = t;
    t++;

}

void solve() {
    int n, m; cin >> n >> m;
    vector<vector<int>> adj(n);

    for(int i = 0; i < m; ++i){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> seen(n,0);
    dfs(0,seen,adj);
    debug(mp);
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