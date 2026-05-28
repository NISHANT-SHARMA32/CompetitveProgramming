#include <bits/stdc++.h>

using namespace std;

template<typename A, typename B> ostream& operator<<(ostream &os, const pair<A, B> &p) { return os << '(' << p.first << ", " << p.second << ')'; }
template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) { os << '{'; string sep; for (const T &x : v) os << sep << x, sep = ", "; return os << '}'; }
void dbg_out() { cerr << endl; }
template<typename Head, typename... Tail> void dbg_out(Head H, Tail... T) { cerr << ' ' << H; dbg_out(T...); }
#ifdef LOCAL
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
#else
#define dbg(...)
#endif

#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;

ll dfs(ll node, ll par, vector<ll> adj[], vector<ll> &count, ll vis){
    ll c = 0;

    for(auto it : adj[node]){
        if(it == par) continue;
        c += dfs(it,node,adj,count,vis+1);
    }
    count[node] = vis - c;
    return c + 1;
}

void solve() {
    ll n, k;
    cin >> n >> k;
   
    vector<ll> adj[n+1];
    for(ll i = 0; i < n-1; ++i){
        ll u, v;
        cin >> u >> v;
        adj[v].push_back(u);
        adj[u].push_back(v);
    }
    vector<ll> count(n+1);
    dfs(1,1,adj,count,0);
    sort(count.begin()+1,count.end(),greater<ll>());
    ll ans = 0;
    for(ll i = 1; i <= k; ++i){
        ans += count[i];
    }cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    int tc = 1;
    //cin >> tc;
    for (int t = 1; t <= tc; t++) {
        // cout << "Case #" << t << ": ";
        solve();
    }
}