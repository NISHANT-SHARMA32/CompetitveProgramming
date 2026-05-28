/*
Author: Nishant Sharma
Created: 2026-04-30 21:15:43
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

vector<int> segtree;
vector<int> nums;

int leftChild(int index){
    return 2 * index;
}
int rightChild(int index){
    return 2 * index + 1;
}

int combine(int a, int b, bool isor){
    return isor ? (a | b) : (a ^ b);
}

void build(int s, int e, int index, bool isor){
    if(s == e){
        segtree[index] = nums[s];
        return;
    }

    int mid = (s + e) >>  1;

    build(s, mid, leftChild(index), !isor);
    build(mid + 1, e, rightChild(index), !isor);

    segtree[index] = combine(segtree[leftChild(index)], segtree[rightChild(index)], isor);
}

void update(int s, int e, int index, int update_index, int update_value, bool isor){
    if(s == e){
        segtree[index] = update_value;
        return;
    }

    int mid = (s + e) >> 1;
    
    if(mid >= update_index){
        update(s, mid, leftChild(index), update_index, update_value, !isor);
    }else{
        update(mid + 1, e, rightChild(index), update_index, update_value, !isor);
    }

    segtree[index] = combine(segtree[leftChild(index)], segtree[rightChild(index)], isor);
}

/*
int query(int s, int e, int l, int r, int index){
    if(l > e or s > r) return 0; 
    if(l <= s and e <= r) return segtree[index];

    int mid = (s + e) >> 1;
    int left = query(s, mid, l, r, leftChild(index));
    int right = query(mid + 1, e, l, r, rightChild(index));

    return combine(left, right);
}
*/


void solve() {
    int level, m; cin >> level >> m;
    int n = 1 << level;
    segtree.resize(4 * n);
    nums.resize(n);

    for(int i = 0; i < n; ++i) cin >> nums[i];

    bool rootOr = (level & 1) == 1;
    build(0, n - 1, 1, rootOr);

    for(int i = 0; i < m; ++i){
        int index, value; cin >> index >> value;

        update(0, n - 1, 1, index - 1, value, rootOr);

        cout << segtree[1] << endl;
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