#include <bits/stdc++.h>

using namespace std;

#define slide push_back
#define ar array
#define ll long long
#define ld long double
#define sza(x) ((int)x.size())
#define all(a) (a).begin(), (a).end()

//this dfs will give nlogn as the TC.  every node visit in dfs O(n) * 16. 16 ~ O(logn)  ==  O(nlogn)
void dfs(int node, int par, vector<int> adj[], vector<vector<int>> &dp){
  dp[node][0] = par;
  for(int i = 1; i <= 16; ++i){
    dp[node][i] = dp[dp[node][i-1]][i-1];
  }
  for(auto it : adj[node]){
    if(it == par) continue;
    dfs(it,node,adj,dp);
  }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

    //creating the adjacency list
    int n = 7;
    vector<int> adj[n+1];
    for(int i = 0; i < n-1; ++i){
      int u, v;
      cin >> u >> v;
      adj[v].slide(u);
      adj[u].slide(v);
    }

    // for each node we will be storing the 17 parents means 2^16
    vector<vector<int>> dp(n+1,vector<int>(17,0));
    dfs(1,0,adj,dp);

    //now only we have to print the kth ancestor
    int node, k; // these two will be given to us
    cin >> node >> k;
    int bit = 0;
    while(k){
      if(k&1){
          node = dp[node][bit];
      }
      bit++;
      k = k >> 1;
    }
    cout << node << endl;
}