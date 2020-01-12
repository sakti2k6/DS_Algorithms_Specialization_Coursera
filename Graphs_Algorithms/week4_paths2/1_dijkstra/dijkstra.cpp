#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

int naive_distance (vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
    vector<int> spath (adj.size(),-1);
    queue<int> q;
    q.push(s);
    spath[s] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < adj[v].size(); ++i) {
            if (spath[adj[v][i]] == -1) {
                spath[adj[v][i]] = spath[v] + cost[v][i];
                q.push(adj[v][i]);
            } else if (spath[adj[v][i]] > (spath[v] + cost[v][i]) ) {
                spath[adj[v][i]] = spath[v] + cost[v][i];
                q.push(adj[v][i]);
            }
        }
    }
    return spath[t];
}

int dijkstra (vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
    vector<int> spath (adj.size(), -1);
    vector<bool> completed (adj.size(),0);
   
    priority_queue<pair<int,int>,vector<pair<int,int>>,std::greater<int>> q;
    spath[s] = 0;
    q.push(std::make_pair(spath[s],s));

    while(!q.empty()) {
        pair<int,int> v = q.top();
        q.pop();
        completed[v.second] = 1;
        for (int i = 0; i < adj[v.second].size(); ++i) {
            if (completed[adj[v.second][i]] == 0) {
                if ( (spath[adj[v.second][i]] == -1) || (spath[adj[v.second][i]] > spath[v.second] + cost[v.second][i]) ) {
                    spath[adj[v.second][i]] = spath[v.second] + cost[v.second][i];
                    q.push(spath[adj[v.second][i]], adj[v.second][i]);
                }
            }
        }
    }
    return spath[t];   
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << dijkstra(adj, cost, s, t);
}
