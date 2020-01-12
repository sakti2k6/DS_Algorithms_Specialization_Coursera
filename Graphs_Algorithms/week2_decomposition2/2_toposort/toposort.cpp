#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::pair;

void dfs_explore(vector<vector<int> > &adj, vector<bool> &visited, vector<int> &order, int x) {
  visited[x] = 1;
  for (size_t i = 0; i < adj[x].size(); ++i) {
    if (visited[adj[x][i]] == 0) {
        dfs_explore(adj,visited,order,adj[x][i]);
    }
  }
  order.push_back(x);
}     

vector<int> toposort(vector<vector<int> > adj) {
  vector<bool> visited(adj.size(), 0);
  vector<int> order;
  for (size_t i = 0; i < adj.size(); ++i) {
    if (visited[i] == 0)
        dfs_explore(adj,visited,order,i);
  }
  std::reverse (order.begin(),order.end());
  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
