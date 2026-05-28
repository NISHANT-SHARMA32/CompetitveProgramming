/*
Author: Nishant Sharma
Created: 2026-04-29 11:53:29
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

const int dx[] = {1, 0};
const int dy[] = {0, 1};

ll n, m, k;
map<ll, ll> mp[25][25];
ll grid[25][25];

ll ans = 0;

void dfs1(int x, int y, int steps, ll xr){
    xr ^= grid[x][y];

    if(steps == 0){
        mp[x][y][xr]++;
        return;
    }

    if(x + 1 < n) dfs1(x + 1, y, steps - 1, xr);
    if(y + 1 < m) dfs1(x, y + 1, steps - 1, xr);
}

void dfs2(int x, int y, int steps, ll xr){
    if(steps == 0){
        ll need = k ^ xr;
        ans += mp[x][y][need];
        return;
    }

    xr ^= grid[x][y];


    if(x - 1 >= 0) dfs2(x - 1, y, steps - 1, xr);
    if(y - 1 >= 0) dfs2(x, y - 1, steps - 1, xr);
}

void solve() {
    cin >> n >> m >> k;

    
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> grid[i][j];
        }
    }

    int total = n + m - 2;
    int mid = total / 2;

    dfs1(0, 0, mid, 0);
    dfs2(n - 1, m - 1, total - mid, 0);

    cout << ans << endl;
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