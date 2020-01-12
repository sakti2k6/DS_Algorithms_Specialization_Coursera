#include <iostream>
#include <vector>

using std::vector;

int lcs2(vector<int> &a, vector<int> &b) {
    int m = a.size() + 1;
    int n = a.size() + 1;
    vector<int> temp(n);
    vector<vector<int>> T(m,temp);

    //Base case. All T[0][i] and T[j][0] are 0 each. i.e there are no common substrings.

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            int c = (a[i-1] == b[j-1]);
          //  T[i][j] = std::max({c+T[i-1][j-1], T[i-1][j], T[i][j-1]});
              int temp = std::max(c+T[i-1][j-1], T[i-1][j]);
              T[i][j] = std::max(temp, T[i][j-1]);
        }
    }

  return T[m-1][n-1];
}

int main() {
  size_t n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> a[i];
  }

  size_t m;
  std::cin >> m;
  vector<int> b(m);
  for (size_t i = 0; i < m; i++) {
    std::cin >> b[i];
  }

  std::cout << lcs2(a, b) << std::endl;
}
