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

#define end endl
#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

const int MAX_N = 1e5 + 5;
const ll MOD = 1e9 + 7;
const ll INF = 1e9;
const ld EPS = 1e-9;


vector<int> seive(int n){
    vector<int> prime(n+1,1);
    prime[0] = prime[1] = 0;
    for(int i = 2; i*i <= n; ++i){
        if(prime[i]){
            for(int j = i*i; j <= n; j+=i){    
                prime[j] = false;
            }
        }
    }  
    vector<int> ans;
    for(int i = 2; i <= n; ++i){
        if(prime[i]) ans.push_back(i);
    }
    return ans;
}

void segment(int low, int high){
    int limit = sqrt(high) + 1;
    vector<int> prime = seive(limit);

    vector<int> range(high-low+1,1);  // here in this array we will shift the indexes 

    for(auto it : prime){
        int firstMultiple = (low / it) * it;
        if(firstMultiple < low) firstMultiple += it;

        for(int i = max(it*it, firstMultiple); i <= high; i+=it){
            range[i-low] =  0;
        }
    }
    if(low == 1) range[0] = 0;
    for(int i = low; i <= high; ++i){
        if(range[i-low]) cout << i << endl;
    }
}
void solve() {
    int n, m; cin >> m >> n;
    segment(m,n);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        solve();
        cout << endl;
    }
}