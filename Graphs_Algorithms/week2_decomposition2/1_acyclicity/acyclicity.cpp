#include <iostream>
#include <vector>

using std::vector;

void explore(vector<vector<int> > &adj, vector<bool>& visited, vector<bool>& postvisit, int x, int& result) {
    if (result == 1)
        return;
    visited[x] = 1;
    for (size_t i = 0; i < adj[x].size(); ++i) {
        if (visited[adj[x][i]] == 0) {
            explore (adj,visited,postvisit,adj[x][i],result);
        } else if ( postvisit[adj[x][i]] == 0) {
                    result = 1;
                    return;
        }
    }

    postvisit[x] = 1;
}

int acyclic(vector<vector<int> > &adj) {
    vector<bool> visited(adj.size(),0);
    vector<bool> postvisit(adj.size(),0);
    int result = 0;
    for (size_t i = 0; i < adj.size(); ++i) {
        if (visited[i] == 0) {
            explore (adj,visited,postvisit,i,result);
        }
    }

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
  }
 // vector<vector<int> > adj = { {1}, {}, {1}, {2} };
  std::cout << acyclic(adj);
}
