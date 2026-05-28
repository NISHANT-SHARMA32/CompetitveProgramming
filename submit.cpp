/*
Author: Nishant Sharma
Created: 2025-08-03 10:38:00
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

class SGT{
    private:
        vector<ll> sg, msg;
    public:
        SGT(int n){
            sg.resize(4 * n);
            msg.resize(4 * n,0);
        }

        void build(int index, int low, int high, vector<ll> &arr){
            if(low == high){
                sg[index] = arr[low];
                msg[index] = 1;
                return;
            }

            int mid = (low + high) >> 1;
            build(2*index + 1, low, mid, arr);
            build(2*index + 2, mid + 1, high, arr);
            sg[index] = min(sg[2 * index + 1], sg[2 * index + 2]);
            if(sg[index] == sg[2 * index + 1]) msg[index] += msg[2 * index + 1];
            if(sg[index] == sg[2 * index + 2]) msg[index] += msg[2 * index + 2]; 
        }

        void update(int index, int low, int high, int pos, int val, vector<ll> &arr){
            if(low == high){
                arr[pos] = val;
                sg[index] = arr[pos];
                return;
            }

            int mid = (low + high) >> 1;
            if(pos <= mid) update(2*index + 1, low, mid, pos, val, arr);
            else update(2*index + 2, mid + 1, high, pos, val, arr);
            
            sg[index] = min(sg[2 * index + 1], sg[2 * index + 2]);
            if(sg[index] == sg[2 * index + 1]) msg[index] += msg[2 * index + 1];
            if(sg[index] == sg[2 * index + 2]) msg[index] += msg[2 * index + 2]; ; 
        }

        pair<ll,ll> query(int index, int low, int high, int l, int r){
            //complete overlap [l low high r]
            if(l <= low and high <= r) return {msg[index], sg[index]};

            // no overlap low high l r..       .. l r low high ..
            if(high < l || r < low) return {INT_MAX,0};

            // partial overlap
            int mid = (low + high) >> 1;
            pair<ll,ll> left = query(2*index + 1, low, mid, l, r);
            pair<ll,ll> right = query(2*index + 2, mid + 1, high,l, r);
            return {left.first + right.first, min(left.second,right.second)};
        }
};

void solve() {
    int n, m; cin >> n >> m;
    vector<ll> arr(n);

    for(int i = 0; i < n; ++i) cin >> arr[i];

    SGT seg(n);
    seg.build(0,0,n-1,arr);
    cout << seg.query(0,0,n-1,0,n-1) << endl;

    while(m--){
        
        ll pos, val; cin >> pos >> val;
        seg.update(0,0,n-1,pos,val,arr);
        cout << seg.query(0,0,n-1,0,n-1) << endl;
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