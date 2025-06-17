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