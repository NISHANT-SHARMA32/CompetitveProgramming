#include <bits/stdc++.h>
using namespace std;
// #include <ext/pb_ds/assoc_container.hpp> // everything related to pbds
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef int node; // change type here
// typedef tree<node, null_type, less<node>,
//              rb_tree_tag, tree_order_statistics_node_update> // this is push_backds
//     ordered_set;
using ll = long long;
using vi = vector<long long>;
using vpi = vector<pair<ll, ll>>;
typedef long double ld;
#define all(x) (x).begin(), (x).end()
#define rall(a) (a).rbegin(), (a).rend()
#define lb lower_bound
#define ps(x, y) fixed << setprecision(y) << x
#define int long long

ll INF = 1e18;
ll MOD = 1e9 + 7;

int dx[] = {0, 0, -1, 1};
int dy[] = {-1, 1, 0, 0}; // useful when dealing with points
ll maxx(vi &a)
{
    return (*max_element(a.begin(), a.end()));
}

ll minn(vi &a)
{
    return (*min_element(a.begin(), a.end()));
}

long long gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to return LCM of two numbers
long long lcm(ll a, ll b)
{
    return (a / gcd(a, b)) * b;
}

bool isPrime(ll n)
{
    if (n <= 1)
    {
        return false;
    }
    for (ll i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

// mod stuff starts here
long long mod(long long x)
{
    return ((x % MOD + MOD) % MOD);
}
long long add(long long a, long long b)
{
    return mod(mod(a) + mod(b));
}
long long mul(long long a, long long b)
{
    return mod(mod(a) * mod(b));
}
// this is mod stuff

void input(vi &a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
}

void print(vector<int> &a)
{
    for (auto x : a)
    {
        cout << x  << " ";
    }
    cout << endl;
}

int stringToInt(string s)
{
    stringstream geek(s);
    int x = 0;
    geek >> x;
    return x;
}

bool isPowerOfTwo(ll n)
{
    if (n == 0)
        return false;

    return (ceil(log2(n)) == floor(log2(n)));
}

bool isPalindrome(string s)
{
    int n = s.size();
    for (int i = 0; i < n; i++)
    {
        if (s[i] != s[n - i - 1])
        {
            return false;
        }
    }
    return true;
}
string binaryTransformation(long long x)
{
    if (x == 0)
        return "";
    else
    {
        string s = binaryTransformation(x / 2);
        s.push_back(char('0' + x % 2));
        return s;
    }
}
ll power(ll a, ll b, ll mod)
{
    if (b == 0)
    {
        return 1;
    }
    ll ans = power(a, b / 2, mod);
    ans *= ans;
    ans %= mod;
    if (b % 2)
    {
        ans *= a;
    }
    return ans % mod;
}
double power(double a, int b)
{
    if (b == 0)
    {
        return 1;
    }
    double t = power(a, b / 2);
    if (b & 1)
    {
        return t * t * a;
    }
    else
    {
        return t * t;
    }
}
int modularInverse(int number, int mod)
{
    return power(number, mod - 2, mod);
}
// it should be 1LL and not 1
// write more tests
// google if stuck
// take a walk if stuck

int msb(int n)
{
    for (int i = 32; i >= 0; i--)
    {
        if (n & (1LL << i))
        {
            return i;
        }
    }
    return 0;
}


vector<bool> sieve(int n){
    vector<bool> prime(n,1);
    prime[0] = prime[1] = 0;
    for(int i = 2; i * i < n; ++i){
        if(prime[i]){
            for(int j = i*i; j < n; ++j) prime[j] = 0;
        }
    }
    return prime;
}

// {vector<int> spf(20,-1);
// for(int i = 2; i < 20; ++i){
//     if(spf[i] == -1){
//         for(int j = i; j < 20; j +=i) if(spf[j] == -1) spf[j] = i;
//     }
// }}

void dfs(vector<int> adj[], int node, int par, vector<int> &dp){
    dp[node] = 1;
    for(auto it : adj[node]){
        if(it == par) continue;
        dfs(adj,it,node,dp);
        dp[node] += dp[it];
    }
}

void solve()
{
    int n; cin >> n;
    vector<int> adj[n+1];
    for(int i = 2; i <= n; ++i){
        int v; cin >> v;
        adj[i].push_back(v);
        adj[v].push_back(i);
    }
    vector<int> dp(n+1,0);
    dfs(adj,1,0,dp);

    for(auto i : dp){
        cout << i - 1 << " " << endl;
    }
    
}

// https://github.com/Manjunath0408/CPSnippets
int32_t main()
{
    // freopen("dishes.in", "r", stdin);
    // freopen("dishes.out", "w", stdout);
    /* stuff you should look for
     * int overflow, array bounds
     * special cases (n==1?)
     * do smth instead of nothing and stay organized
     * WRITE STUFF DOWN
     * DON'T GET STUCK ON ONE APPROACH
     * IF STUCK ON A QUESTION, MOVE TO THE NEXT ONE
     */
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // int t = 1;
    // cin >> t;
    // for (int i = 1; i <= t; i++)
    // {
    //     solve();
    // }
    cout << 123;
    return 0;
}