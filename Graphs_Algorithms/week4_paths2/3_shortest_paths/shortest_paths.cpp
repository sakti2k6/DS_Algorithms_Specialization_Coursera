#include <iostream>
#include <limits>
#include <vector>
#include <queue>
#include <unordered_set>
#include <fstream>

using std::vector;
using std::queue;
using std::pair;
using std::unordered_set;

void printq (queue<int> q) {
    std::cout << "Queue is: ";
    while (!q.empty()) {
        std::cout << q.front() << " " ;
        q.pop();
    }
    std::cout << "\n";
}

void printv (vector<long long> vec) {
    for (int i=0; i < vec.size(); ++i) 
        std::cout << "vec[" << i << "]:" << vec[i] << "\n";
}

queue<int> relax_edge(vector<vector<int> > &adj, vector<vector<int> > &cost,vector<long long>& dist) {
    long long POS_INFINITY = std::numeric_limits<long long>::max();
    queue<int> negcycle;
    for (int i = 0; i < adj.size(); ++i) {
        if (dist[i] != POS_INFINITY) {
            for (int j = 0; j < adj[i].size(); ++j) {
                if (dist[adj[i][j]] == POS_INFINITY) {
                    dist[adj[i][j]] = dist[i] + cost[i][j];
                } else if (dist[adj[i][j]] > (dist[i] + cost[i][j])) {
                    dist[adj[i][j]] = dist[i] + cost[i][j];
                    negcycle.push(adj[i][j]);
                }
            }
        }
    }

    //printq(negcycle);
    return negcycle;
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &dist) {
    long long NEG_INFINITY = std::numeric_limits<long long>::min();
    dist[s] = 0;
    for (int i = 0 ; i < adj.size(); ++i) {
       relax_edge(adj,cost,dist); 
    }

    //printv(dist);
    queue<int> negcycle = relax_edge(adj,cost,dist);
    //std::cout << negcycle.size() << "\n"; 
    //printq(negcycle);
    unordered_set<int> vertices;
    while(!negcycle.empty()) {
        int v = negcycle.front();
        negcycle.pop();
        
        if (vertices.find(v) == vertices.end()) {
            vertices.insert(v);
        }
            dist[v] = NEG_INFINITY;
            for (int i = 0; i < adj[v].size(); ++i) {
                if (vertices.find(adj[v][i]) == vertices.end()) {
                    negcycle.push(adj[v][i]);
                    vertices.insert(adj[v][i]);
                    dist[adj[v][i]] = NEG_INFINITY;
                }
            }
        }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  //std::ifstream test1("test1.txt");
  //test1 >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    //test1 >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  //test1 >> s;
  s--;
  vector<long long> dist(n, std::numeric_limits<long long>::max());
  shortest_paths(adj, cost, s, dist);
  long long POS_INFINITY = std::numeric_limits<long long>::max();
  long long NEG_INFINITY = std::numeric_limits<long long>::min();
  //  std::cout << "POS_INFINITY: " << POS_INFINITY << "\n";
  //  std::cout << "NEG_INFINITY: " << NEG_INFINITY << "\n";
  for (int i = 0; i < n; i++) {
    if (dist[i] == POS_INFINITY) {
      std::cout << "*\n";
    } else if (dist[i] == NEG_INFINITY) {
      std::cout << "-\n";
    } else {
      std::cout << dist[i] << "\n";
    }
  }
}
