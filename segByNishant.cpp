/*
Author: Nishant Sharma
Created: 2025-08-01 13:49:17
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

class SGTree{
    private:
    vector<int> segTree;

    public:
    SGTree(int n){
        segTree.resize(4*n);
    }
    void build(int index, int low, int high, vector<int> &arr){
        if(low == high){
            segTree[index] = arr[low];
            return;
        }

        int mid = (low + high) >> 1;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);

        segTree[index] = min(segTree[2 * index + 1], segTree[2 * index + 2]);
    }

    int query(int index, int low, int high, int l, int r, vector<int> &arr){
        // no overlap  low high l r or l r low high
        if(high < l or r < low) return INT_MAX;

        // complete overlap [l low high r]
        if(low >= l and high <= r) return segTree[index];

        // partial overlap
        int mid = (low + high) >> 1;

        int left = query(2 * index + 1, low, mid, l, r, arr);
        int right = query(2 * index + 2, mid + 1, high, l, r, arr);

        return min(left,right);
    }

    void update(int index, int low, int high, int pos, int val, vector<int> &arr){
        if(low == high){
            arr[pos] = val;
            segTree[index] = arr[pos];
            return;
        }

        int mid =  (low + high) >> 1;
        if(pos <= mid) update(2*index + 1, low, mid, pos, val, arr);
        else update(2 * index + 2, mid + 1, high, pos, val, arr);
        
        segTree[index] = min(segTree[2*index + 1], segTree[2 *index + 2]);
    }
};

void solve() {
    int n1; cin >> n1;
    vector<int> arr1(n1);
    for(int i = 0; i < n1; ++i) cin >> arr1[i];
    SGTree sg1(n1);
    sg1.build(0,0,n1-1,arr1);

    int n2; cin >> n2;
    vector<int> arr2(n2);
    for(int i = 0; i < n2; ++i) cin >> arr2[i];
    SGTree sg2(n2);
    sg2.build(0, 0, n2 - 1, arr2);

    int q; cin >> q;
    while(q--){
        int type; cin >> type;
        if(type == 1){
            int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;

            int min1 = sg1.query(0,0,n1-1,l1,r1,arr1);
            int min2 = sg2.query(0,0,n2-1,l2,r2,arr2);
            debug(min1,min2);
            cout << min(min1,min2) << endl;
        }
        else{
            int num, pos, val; cin >> num >> pos >> val;
            if(num == 1){
                sg1.update(0,0,n1-1,pos,val,arr1);
            }
            else sg2.update(0,0,n2-1,pos,val,arr2);
        }
    }

    debug(arr1);debug(arr2);
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


