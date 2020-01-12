#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
    vector<char> color(adj.size(), 'r');
    queue<int> q;
    for (int i = 0; i < adj.size(); ++i) {
        if (color[i] == 'r') {
            q.push(i);
            color[i] = 'w';
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int j = 0; j < adj[v].size(); ++j) {
                   if(color[adj[v][j]] == 'r')  {
                       color[adj[v][j]] = (color[v] == 'w') ? 'b' : 'w' ;
                       q.push(adj[v][j]);
                   }
                   else if (color[adj[v][j]] == color[v]) 
                       return 0;
                }
            }
        }
    }
    return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
