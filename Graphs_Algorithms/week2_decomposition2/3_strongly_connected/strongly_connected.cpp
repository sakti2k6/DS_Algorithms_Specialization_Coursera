#include <algorithm>
#include <iostream>
#include <vector>
#include <fstream>

using std::vector;
using std::pair;

void print (const vector<int>& post_visit) {
    std::cout << "{";
  for (int i=0; i< post_visit.size(); ++i)
      std::cout << post_visit[i] << "," ;
    std::cout << "}\n";
}

void DFS_explore (vector<vector<int>>& adj, vector<bool>& visited, int x, vector<int>& post_visit) {
    visited[x] = 1;
    for (size_t i = 0; i < adj[x].size(); ++i) {
        if (visited[adj[x][i]] == 0) 
            DFS_explore (adj,visited,adj[x][i],post_visit);
    }
    post_visit.push_back(x);
}


int number_of_strongly_connected_components(vector<vector<int> >& adj, vector<vector<int> >& adj_r) {
  int result = 0;
  vector<bool> visited(adj.size(),0);
  vector<int> post_visit;

  for (size_t i = 0; i < adj.size(); ++i) {
    if (visited[i] == 0) 
        DFS_explore(adj,visited,i,post_visit);
  }
  // print(post_visit); 
  // std::cout << post_visit.size() << "\n";
  visited.clear();
  visited.resize(adj.size(),0);
  vector<int> post_visit_r;
  for (int i = post_visit.size() - 1 ; i >= 0 ; --i) {
    if (visited[post_visit[i]] == 0) {
        DFS_explore(adj_r,visited,post_visit[i],post_visit_r);
        result += 1;
    }
  }

  return result;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
 // std::ifstream test1 ("test1.txt");
 // test1 >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > adj_r (n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    //test1 >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj_r[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj,adj_r);
}
