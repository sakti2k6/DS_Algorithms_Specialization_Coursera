#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;

string BWT(const string& text) {
    string result = "";
    int n = text.size();

    //Create Suffixes of the text
    vector<pair<string,int>> suffixes;
    for (int i = 0; i < n; ++i) {
        suffixes.push_back(std::make_pair(text.substr(i),i));
    }
  
    std:sort(std::begin(suffixes), std::end(suffixes));
    for (int i = 0; i < n; ++i) {
        int s_id = suffixes[i].second;
        if (s_id == 0) {
            result.push_back(text[n-1]);
        } else {
            result.push_back(text[s_id - 1]);
        }
    }

    return result;
}

int main() {
  string text;
  cin >> text;
  cout << BWT(text) << endl;
  return 0;
}
