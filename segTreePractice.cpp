/*
Author: Nishant Sharma
Created: 2026-04-29 15:22:27
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

vector<int> segTree(4 * 100000);
vector<int> nums(100000);

int leftChild(int index){
    return 2 * index;
}

int rightChild(int index){
    return 2 * index + 1;
}

int combine(int a, int b){
    return a + b;
}

void build(int s, int e, int index){
    if(s == e){
        segTree[index] = nums[s];
        return;
    }

    int mid = (s + e) / 2;
    build(s, mid, leftChild(index));
    build(mid + 1, e, rightChild(index));

    segTree[index] = combine(segTree[leftChild(index)], segTree[rightChild(index)]);
}   

void update(int s, int e, int index, int update_index, int update_value){
    if(s == e){
        segTree[index] = update_value;
        return;
    }

    int mid = (s + e) / 2;

    if(mid >= update_index){
        update(s, mid, leftChild(index), update_index, update_value);
    }
    else{
        update(mid + 1, e, rightChild(index), update_index, update_value);    
    }

    segTree[index] = combine(segTree[leftChild(index)], (segTree[rightChild(index)]);
}

int query(int s, int e, int l, int r, int index){
    // no overlap
    if(e  < l or s > r) return 0;

    // complete overlap
    if(s >= l and e <= r) return segTree[index];

    int mid = (s + e) / 2;
    int left = query(s, mid, l, r, leftChild(index));
    int right = query(mid + 1, e, l, r, rightChild(index));

    return combine(left, right);
}

//  s ________ e l _____r     l ____ r s ____ e  // no overlap

//   l _________ r   //complete overlap
//      s ___ e


void solve() {
    for(int i = 0; i < 100000; i++){
        cin >> nums[i];
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