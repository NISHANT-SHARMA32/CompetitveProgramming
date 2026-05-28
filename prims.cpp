/*
Author: Nishant Sharma
Created: 2025-07-01 20:34:00
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

void solve() {
    int n, m; cin >> n >> m;
    vector<pair<int,int>> adj[n+1];
    for(int i = 0; i < m; ++i){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }

    priority_queue<vector<int>> pq;
    vector<int> vis(n+1,0);
    int sum = 0;
    pq.push({0,1,0}); // weight node parent
    vector<pair<int,int>> edges;    
    while(pq.empty() == false){
        int node = pq.top()[1];
        int wt = -pq.top()[0];
        int par = pq.top()[2];
        pq.pop();

        if(vis[node] == 1) continue;

        vis[node] = 1;
        sum += wt;
        if(par != 0) edges.push_back({node,par});
        for(auto it : adj[node]){
            if(vis[it.first] == 0){
                pq.push({-it.second,it.first,node});
            }
        }
    }

    cout << sum << endl;
    for(auto it : edges){
        cout << it.first << " " << it.second << endl;
    }
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