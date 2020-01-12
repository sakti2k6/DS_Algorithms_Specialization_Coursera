#include <iostream>
#include <vector>
#include <unordered_map>

using std::vector;
using std::pair;
using std::unordered_map;

void explore(vector<vector<int> > &adj, vector<int>& visited, unordered_map<int,int>& postvisit, int& counter, int x, int& result) {
    //std::cout << "Counter: " << counter << " Index: " << x << " Result: " << result << "\n";
    if (result == 1)
        return;
    visited[x] = 1;
    for (size_t i = 0; i < adj[x].size(); ++i) {
        if (visited[adj[x][i]] == 0) {
            explore (adj,visited,postvisit,counter,adj[x][i],result);
        } else if ( postvisit.find(adj[x][i]) == postvisit.end() ) {
              // if ( postvisit[adj[x][i]] < postvisit[x]) {
                    //std::cout << "I got result 1" << "\n";
                    result = 1;
                    return;
              //  }
        }
    }
            postvisit.emplace(std::make_pair(x,++counter));
}

int acyclic(vector<vector<int> > &adj) {
    vector<int> visited(adj.size(),0);
    unordered_map<int,int> postvisit;
    int counter = 0;
    int result = 0;
    for (size_t i = 0; i < adj.size(); ++i) {
        if (visited[i] == 0) {
            //postvisit.clear();
            explore (adj,visited,postvisit,counter,i,result);
           // for (const auto& p: postvisit)
           //     std::cout << p.first << " => " << p.second << "\n";
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
