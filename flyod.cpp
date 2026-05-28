/*
Author: Nishant Sharma
Created: 2025-07-01 20:49:23
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
    this algorithm is brute force dp based algo
    time complexity is -> n*n*n just three simple loops

    in this algo we keep the distance of every node to itself as 0. and if no direct edges is there then we keep distance as 1e8 
    so if any graph contain any negative cycle then it distance to itself will get reduced from o to some neg value
    that means graph contain neg cycle.

*/

void solve() {
    for(int via = 0; via < n; ++via){
            for(int i = 0; i < n; ++i){
                for(int j = 0; j < n; ++j){
                    if(dist[i][via] == 1e8 or dist[via][j] == 1e8) continue;
                    dist[i][j] = min(dist[i][j], dist[i][via] + dist[via][j]);
                }
            }
    }

    for(int i = 0; i < n; ++i){
        if(dis[i][i] != 0) cout << "neg weight cycle" << endl;
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