/*
Author: Nishant Sharma
Created: 2025-07-13 13:52:52
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

// this code is 1 based indexing segTree. 
// left = 2 * index.
// right = 2 * index + 1. 

vector<int> segtree; 

void build(vector<int> &arr, int start, int end, int index){ // time complexity is O(n).
    if(start == end){
        segtree[index] = arr[start];
        return;
    }

    int left = 2 * index, right = 2 * index + 1;
    int mid = (start + end) / 2;
    build(arr,start,mid,left);
    build(arr,mid+1,end,right);

    segtree[index] = min(segtree[left], segtree[right]);
}

void update(vector<int> &arr, int start, int end, int index, int pos, int value){ // time complexity O(logn).
    if(start == end){
        arr[pos] == __gcd(value,arr[pos]);
        segtree[index] = arr[pos];
        return;
    }

    int mid = (start + end) / 2;

    if(pos <= mid) update(arr,start,mid,2*index,pos,value);
    else update(arr,mid + 1, end,2*index + 1, pos, value);
    segtree[index] = segtree[2 * index] ^ segtree[2 * index + 1];

}

int query(int start, int end, int index, int l, int r){ // we have to return sum from l to r. TC- O(logn)
    if(start >= l and end <= r) return segtree[index]; //..  this is complete overlap
    if(l > end || r < start) return INT_MAX; //.. this is no overlap

    //.. we will go to the left child and the right child. this is partial overlap.
    int mid = (start + end) / 2;
    int left_ans = query(start,mid,2*index,l,r);
    int right_ans = query(mid+1,end,2*index+1,l,r);
    return min(left_ans,right_ans);

}
void solve() {   
    int n; cin >> n;
    segtree.resize(4*n,-1);

    vector<int> arr(n);
    for(int i = 0; i < n; ++i) cin >> arr[i];

    build(arr,0,n-1,1); 
    debug(arr);
    cout << query(0,n-1,1,0,2) << endl; 
    update(arr,0,n-1,1,0,5); debug(arr);
    cout << query(0,n-1,1,0,2); 
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
/*
    if query is changes  to update value to current  to current + new value
    give range minimum  -> instead of adding this time we will take the minimum(in build code)
    and the query part will also get updates.. as we are returning 0 in case of disjoint... but to get minimum overall .. we have to return INT_MAX.
    arr[pos] += value
*/ 


/*
   update the value at arr with gcd(current value, value)
   give me xor or range 
*/ 