#include <iostream>
#include <vector>

using std::vector;

int lcs2(const vector<int> &a, const vector<int> &b) {
    int m = a.size() + 1;
    int n = b.size() + 1;
    vector<int> temp(n);
    vector<vector<int>> T(m,temp);

    //Base case. All T[0][i] and T[j][0] are 0 each. i.e there are no common substrings.
    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            int t = (a[i-1] == b[j-1])  ;
            T[i][j] = std::max({t+T[i-1][j-1], T[i-1][j], T[i][j-1]});
        }
    }
    

  for (auto& e: T) {
    for(auto& f: e) 
        std::cout << f << " ";
    std::cout << "\n" ;
    }
  

  vector<int> c(T[m-1][n-1]);
  int i = m-1;
  int j = n-1;
  int k = T[m-1][n-1] - 1;
  while(i > 0 && j > 0) {
    if (a[i-1] == b[j-1]) {
        c[k] = a[i-1];
        --i;
        --j;
        --k;
    } else if (T[i][j] == T[i][j-1]) 
        --j;
    else if (T[i][j] == T[i-1][j]) 
        --i;
   // std::cout << "i:" << i << " j:" << j << "\n";
  }
    
   for (const int& e: c)
     std::cout << e << "," ;
   std::cout << "\n";

  return c.size();
}


int main() {
  /* 
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
  */
    
  vector<int> d = {8,3,2,1,7};
  vector<int> e = {8,2,1,3,8,10,7};
  vector<int> f = {6,8,3,1,4,7};
  //std::cout << lcs3(d, e, f) << std::endl;
  vector<int> a = {1,2,3};
  vector<int> b = {2,1,3};
  vector<int> c = {1,3,5};
  std::cout << lcs2(a, b) << std::endl;
  
}
