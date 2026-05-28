// User function Template for C++

class Solution {
  public:
    vector<int> bellmanFord(int V, vector<vector<int>>& edges, int src) {
        vector<int> distance(V,1e8);
        distance[src] = 0;
        bool negcycle = false;
        for(int i = 0; i < V; ++i){
            for(auto &it : edges){
                int u = it[0], v = it[1] , w = it[2];
                if(distance[u] != 1e8 and distance[u] + w < distance[v]){
                    if(i == V-1){
                        negcycle = true;
                        break;
                    }
                    distance[v] = distance[u] + w;
                }
            }
        }
        if(negcycle) return {-1};
        return distance;
    }
};
