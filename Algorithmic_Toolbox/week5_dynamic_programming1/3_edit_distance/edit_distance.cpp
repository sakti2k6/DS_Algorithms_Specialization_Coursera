#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using namespace std;

int edit_distance(const string &str1, const string &str2) {
    int m = str1.size() + 1;
    int n = str2.size() + 1;
    vector<int> temp(n,0);
    vector<vector<int>> T (m, temp);
    for (int j=0; j < n; ++j)
        T[0][j] = j;
    for (int i=0; i < m; ++i)
        T[i][0] = i;

    for (int i = 1; i < m ; ++ i) {
        for (int j = 1; j < n; ++j) {
            int c = (str1[i-1] != str2[j-1]);
            T[i][j] = min({1+T[i][j-1], 1+T[i-1][j], c+T[i-1][j-1]});
        }
    }

    return T[m-1][n-1];
}

int main() {
  string str1;
  string str2;
  std::cin >> str1 >> str2;
  std::cout << edit_distance(str1, str2) << std::endl;
  return 0;
}
