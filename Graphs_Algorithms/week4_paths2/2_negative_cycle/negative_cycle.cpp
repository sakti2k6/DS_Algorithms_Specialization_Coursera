#include <iostream>
#include <vector>
#include <limits>

using std::vector;
const int INFINITY = std::numeric_limits<int>::max();

bool relax_edge(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<int>& dist) {
    bool out = 0;
    for (int i = 0; i < adj.size(); ++i) {
        for (int j = 0; j < adj[i].size(); ++j) {
            if (dist[adj[i][j]] > (dist[i] + cost[i][j])) {
                dist[adj[i][j]] = dist[i] + cost[i][j];
                out = 1;
            }
        }
    }

    return out;
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
    int V = adj.size();

    vector<int> dist(V,INFINITY);
    dist[0] = 0;
     
    for (int i = 0 ; i < V-1; ++i) {
       relax_edge(adj,cost,dist); 
    }

    bool is_cycle = relax_edge(adj,cost,dist);

    return is_cycle;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
