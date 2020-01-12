#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include <cmath>
#include <functional>
#include <fstream>

using std::vector;
using std::pair;

struct node {
    int weight;
    int parent;
    int rank;
    node (int _weight, int _parent, int _rank) : 
        weight (_weight), parent(_parent), rank(_rank) {}
};

class union_find {
    public:
        vector<node> dataset;
        
        union_find() {}
        
        void makeset (int i) {
            dataset.push_back(node(-1,i,0));
        }

        int find(int i) {
            if (i != dataset[i].parent) {
                int p = find(dataset[i].parent);
                dataset[i].parent = p;
            }
            return dataset[i].parent;
        }

        void merge(int i, int j) {
            int p_i = find(i);
            int p_j = find(j);

            if (p_i == p_j) 
                return;

            if (dataset[p_i].rank > dataset[p_j].rank) {
                dataset[p_j].parent = p_i;
            } else {
                dataset[p_i].parent = p_j ;
                if (dataset[p_i].rank == dataset[p_j].rank) {
                    dataset[p_j].rank += 1;
                }
            }

        }

};

struct edge {
    double length;
    int start;
    int end;
    edge (double _length, int _start, int _end) :
        length(_length), start(_start), end(_end) {}
    
    bool operator < (const edge& i) const {
        return (length < i.length);
    }
};

double find_length(int x1, int y1, int x2, int y2) {
    return std::sqrt ( std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2) );
}

double clustering(vector<int> x, vector<int> y, int k) {
    vector<edge> all_edges;

    for (int i = 0; i < x.size(); ++i) {
        for (int j = 0; j < x.size(); ++j) {
            if (i != j) {
                double len = find_length(x[i],y[i],x[j],y[j]);
                all_edges.push_back(edge(len,i,j));
            }
        }
    }
    
    std::sort(all_edges.begin(), all_edges.end());
    
    union_find clusters;
    for (int i = 0; i < x.size(); ++i) {
        clusters.makeset(i);
    }

    vector<double> distance;

    for (int i = 0; i < all_edges.size(); ++i) {
        int u = all_edges[i].start;
        int v = all_edges[i].end;
        double w = all_edges[i].length;

        if (clusters.find(u) != clusters.find(v)) {
            clusters.merge(u,v);
            distance.push_back(w);
        }
    }
    
    return distance[distance.size() - (k-1)];
} 

int main() {
  size_t n;
  int k;
  std::cin >> n;
  //std::ifstream test1("test1.txt");
  //test1 >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
    //test1 >> x[i] >> y[i];
  }
  std::cin >> k;
  //test1 >> k;
  std::cout << std::setprecision(10) << clustering(x, y, k) << std::endl;
}
