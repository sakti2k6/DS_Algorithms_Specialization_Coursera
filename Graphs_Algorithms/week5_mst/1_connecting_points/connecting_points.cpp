#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <functional>
#include <numeric>
#include <fstream>

using std::vector;
using std::pair;
const int MAX_VAL = -1 ;

double line_length (int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow (x1 - x2, 2) + std::pow (y1 - y2 , 2));
}

double minimum_distance(vector<int>& x, vector<int>& y) {
    double result = 0;
    int V = x.size();
    vector<bool> visited (V,0);
    vector<double> weight(V,MAX_VAL);

    std::priority_queue< pair<double,int>, vector< pair<double,int> >,std::greater< pair<double,int> > > minq;
    weight[0] = 0;
    minq.push(std::make_pair(0,0));
    while(!minq.empty()) {
        int v = minq.top().second;
        
        minq.pop();
        visited[v] = 1;
        for (int i = 0; i < V; ++i) {
            if (visited[i] == 0) {
                double wt = line_length(x[v],y[v],x[i],y[i]);
                if ( (weight[i] == MAX_VAL) || (weight[i] > wt) ) {
                    weight[i] = wt;
                    minq.push(std::make_pair(wt,i));
                }
            }
        }
    }
    
    result = std::accumulate(weight.begin(), weight.end(),0.0);
    return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  //std::ifstream test1("test1.txt");
  //test1 >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
    //test1 >> x[i] >> y[i] ;
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
