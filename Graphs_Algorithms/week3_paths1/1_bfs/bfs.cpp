#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
    vector<int> dist (adj.size(),-1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < adj[v].size(); ++i) {
            if (dist[adj[v][i]] == -1) {
                q.push(adj[v][i]);
                dist[adj[v][i]] = dist[v] + 1;
                if(adj[v][i] == t) 
                    return dist[t];
            }
        }
    }

    return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  //std::ifstream test1 ("test1.txt");
  //test1 >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    //test1 >> x >> y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  //test1 >> s >> t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
