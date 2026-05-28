/*
.
.
Author: Nishant Sharma
Created: 2025-06-07 13:05:41
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

int fact[MAX_N];

ll binaryExponetiation(ll a, ll b){
  if(b == 0) return 1;
  ll half = binaryExponetiation(a,b/2);
  if(b&1) return a * 1ll * half * half;
  return 1ll * half * half;
}

void precomp(){
    fact[0] = 1;
    for(ll i = 1; i < 1e5; ++i){
        fact[i] = (fact[i - 1] * i) % MOD;
    }
}

ll nCr(ll n, ll r){  
    if(r > n) return 0;
    ll numo = fact[n];
    ll deno = (fact[r] * fact[n - r]) % MOD;
    ll ans  = (numo * binaryExponetiation(deno,MOD - 2)) % MOD;
    return ans;
}

void solve() {
    precomp();
    cout << nCr(10,2);
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