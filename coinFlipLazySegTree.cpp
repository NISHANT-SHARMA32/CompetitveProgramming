/*
Author: Nishant Sharma
Created: 2025-08-02 21:59:39
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

class ST{
private: 
    vector<int> sg, lazy;
public:
    ST(int n){
        sg.resize(4 * n);
        lazy.resize(4 * n);
    }

    void build(int index, int low, int high, vector<int> &arr){
        if(low == high){
            sg[index] = arr[low];
            return;
        }

        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);

        sg[index] = sg[2*index + 1] + sg[2 * index + 2];
    }

    void update(int index, int low, int high, int l, int r){

        //update the previous remaining updates and propgate downwards
        if(lazy[index] != 0){
            sg[index] += (high - low + 1) - lazy[index]; // total - prev will be the new heads

            // if there are children then we have to propogate downwards
            if(low != high){
                lazy[2 * index + 1] = !lazy[2*index+1];
                lazy[2 * index + 2] = !lazy[2*index+2];
            }

            // we have propogated successfully now make it zero
            lazy[index] = 0; 
        }

        // no overlap l r low high low high l r
        if(r < low || high < l) return;

        // complete overlap l low high r
        if(l <= low and high <= r){
            sg[index] = (high - low + 1) - sg[index];

            if(low != high){
                lazy[2 * index + 1] = !lazy[2*index+1];
                lazy[2 * index + 2] = !lazy[2*index+2];
            }
            return;
        }
        
        int mid = (low + high) / 2;
        update(2 *index + 1, low, mid,l,r,val);
        update(2 *index + 2, mid + 1, high,l,r,val);
        sg[index] = sg[2*index + 1] + sg[2 * index + 2];
    }

    int query(int index, int low, int high, int l, int r){

        // only the new step is to update the tree if any update are remaining
        if(lazy[index] != 0){
            sg[index] += (high - low + 1) - lazy[index]; // total - prev will be the new heads

            // if there are children then we have to propogate downwards
            if(low != high){
                lazy[2 * index + 1] = !lazy[2*index+1];
                lazy[2 * index + 2] = !lazy[2*index+2];
            }

            // we have propogated successfully now make it zero
            lazy[index] = 0; 
        }


        //full overlap [l low high r]
        if(l <= low and high <= r) return sg[index];

        // no overlap l r low high  low high l r 
        if(r < low || high < l) return 0;

        // partial overlap go left and right
        int mid = (low + high) >> 1;    
        int left = query(2 * index + 1, low, mid, l, r);
        int right = query(2 * index + 2, mid + 1, high, l, r);
        return left + right;
    }
};



void solve() {
    
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