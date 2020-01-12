#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int dummy(int W, const vector<int> &w) {
  //write your code here
  int current_weight = 0;
  for (size_t i = 0; i < w.size(); ++i) {
    if (current_weight + w[i] <= W) {
      current_weight += w[i];
    }
  }
  return current_weight;
}


int optimal_weight_naive(int W,const vector<int>& w, int n) {
   // std::cout << "W: " << W << " n: " << n << "\n";
    if (n == 0 || W == 0) {
     //   std::cout << "if (n == 0 || W == 0) : 0" << "\n";
        return 0;
    }

    if (w[n-1] > W) {
        int temp = optimal_weight_naive(W,w,n-1);
    //    std::cout << "if (w[n-1] > W): " << temp << "\n"; 
        return temp;
    } else {
        int temp = std::max(w[n-1] + optimal_weight_naive(W-w[n-1],w,n-1), optimal_weight_naive(W,w,n-1));
      //  std::cout << "if (w[n-1] <= W): " << temp << "\n"; 
        return temp;
    }
}

int optimal_weight (int W,const vector<int>& w) {
    int n = w.size();
    vector<vector<int>> T(W+1,vector<int>(n+1));
    for (int i = 0; i < W+1; ++i) {
        for (int j = 0; j < n+1; ++j) {
            if (i == 0 || j == 0) 
                T[i][j] = 0;
            else if ( w[j-1] > i ) 
                T[i][j] = T[i][j-1];
            else if ( w[j-1] <= i ) 
                T[i][j] = std::max ( w[j-1] + T[i-w[j-1]][j-1], T[i][j-1] );
        }
    }
    
    return T[W][n];
}

int main() {
    
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  } 
   // int W = 10;
   // vector<int> w = {1,3,8};
  std::cout << optimal_weight(W, w) << '\n';
}
