#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::pair;
using namespace std;

void explore (vector<vector<int>>& adj, vector<int>& visited, int x, int y, bool& result) {
    visited[x] = 1;
    for (size_t i = 0; i < adj[x].size(); ++i) {
        if (adj[x][i] == y) {
            result = 1;
            return ;
        }
        if (visited[adj[x][i]] == 0)
            explore(adj,visited,adj[x][i],y,result);
    }
}


int reach(vector<vector<int> > &adj, int x, int y) {

    vector<int> visited(adj.size(),0);
    bool result = 0;
    explore(adj,visited,x,y,result);
    return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
