#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;

int lcs3(vector<int> &a, vector<int> &b, vector<int> &c) {
    int m = a.size();
    int n = b.size();
    int p = c.size();
    vector<vector<vector<int>>> T(m+1,vector<vector<int>>(n+1,vector<int>(p+1))); 

    for (int i=0; i <= m; ++i) {
        for (int j=0; j<=n; ++j) {
            for (int k=0; k<=p; ++k){
                //base case
                if (i == 0 || j == 0 || k == 0) 
                    T[i][j][k] = 0;
                else {
                    int t = (a[i-1] == b[j-1]) && (a[i-1] == c[k-1]);
                    vector<int> temp = { t + T[i-1][j-1][k-1], T[i-1][j][k], T[i][j-1][k], T[i][j][k-1] };
                    T[i][j][k] = *std::max_element(begin(temp), end(temp));
                }
            }
        }
    }
  /* 
    for (int i=0; i <= m; ++i) {
        for (int j=0; j<=n; ++j) {
            for (int k=0; k<=p; ++k){
           //     std::cout << T[i][j][k] << " " ;
            }
        }
    }
    */
    return T[m][n][p];
}


int main() {
  
  size_t an;
  std::cin >> an;
  vector<int> a(an);
  for (size_t i = 0; i < an; i++) {
    std::cin >> a[i];
  }
  size_t bn;
  std::cin >> bn;
  vector<int> b(bn);
  for (size_t i = 0; i < bn; i++) {
    std::cin >> b[i];
  }
  size_t cn;
  std::cin >> cn;
  vector<int> c(cn);
  for (size_t i = 0; i < cn; i++) {
    std::cin >> c[i];
  }
  std::cout << lcs3(a, b, c) << std::endl;
  
   /* 
  vector<int> d = {8,3,2,1,7};
  vector<int> e = {8,2,1,3,8,10,7};
  vector<int> f = {6,8,3,1,4,7};
  std::cout << lcs3(d, e, f) << std::endl;
  vector<int> a = {1,2,3};
  vector<int> b = {2,1,3};
  vector<int> c = {1,3,5};
  std::cout << lcs3(a, b, c) << std::endl;
  */
}
