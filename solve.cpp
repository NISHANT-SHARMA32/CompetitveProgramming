<<<<<<< HEAD
/*
Author: Nishant Sharma
Created: 2026-05-24 17:29:47
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

void solve() {
    int n; cin >> n;
    int low = INT_MAX, high = INT_MIN;
    for(int i = 0; i < n; ++i){
        int temp; cin >> temp;
        low = min(temp, low);
        high = max(temp, high);
    }  
    cout << (high - low + 1) / 2 << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int tc = 1;
    cin >> tc;
    for (int t = 1; t <= tc; t++) {
        solve();
    }
}
=======
vector<int> dijkstra(int V, vector<vector<int>> &edges, int src) {
        vector<vector<int>> adj[V];
        for(auto &it : edges){
            int u = it[0], v = it[1], w = it[2];
            
            adj[u].push_back({v,w});
            adj[v].push_back({u,w});
        }
        
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        vector<int> distance(V,1e9);
        
        distance[src] = 0;
        pq.push({0,src});
        
        while(!pq.empty()){
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            
            for(auto &it : adj[node]){
                int newNode = it[0];
                int weight = it[1];
                
                if(dis + weight < distance[newNode]){
                    distance[newNode] = dis + weight;
                    pq.push({distance[newNode],newNode});
                }
            }
        }
        
        return distance;
}   
>>>>>>> 39c13439e8e021c1e59ca60c981e221b0ef59446
