#include <iostream>
#include <vector>
#include <algorithm>

/*
Problem Description
Task. Given an undirected graph and two distinct vertices 𝑢 and 𝑣, check if there is a path between 𝑢 and 𝑣.
Input Format. An undirected graph with 𝑛 vertices and 𝑚 edges. The next line contains two vertices 𝑢
and 𝑣 of the graph.
Constraints. 2 ≤ 𝑛 ≤ 103; 1 ≤ 𝑚 ≤ 103; 1 ≤ 𝑢, 𝑣 ≤ 𝑛; 𝑢 ̸= 𝑣.
Output Format. Output 1 if there is a path between 𝑢 and 𝑣 and 0 otherwise.

Sample 1.
Input:
4 2
1 2
3 2
1 4
Output:
0

Time: O(V+E)
*/

using std::vector;
using std::pair;
using namespace std;

void explore (vector<vector<int>>& adj, vector<int>& visited, int x, int y) {
    visited[x] = 1;
    for (size_t i = 0; i < adj[x].size(); ++i) {
        if (adj[x][i] == y) {
            return true ;
        }
        if (visited[adj[x][i]] == 0) {
            bool r = explore(adj,visited,adj[x][i],y);
            if (r) return true;
        }
    }

    return false;
}


int reach(vector<vector<int> > &adj, int x, int y) {

    vector<int> visited(adj.size(),0);
    return explore(adj,visited,x,y);
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
