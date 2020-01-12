#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::vector;

// Find all occurrences of the pattern in the text and return a
// vector with all positions in the text (starting from 0) where 
// the pattern starts in the text.
vector<int> find_pattern_naive(const string& pattern, const string& text) {
  vector<int> result;
  int m = pattern.size();
  int n = text.size();
  int j = 0;
  for (int i = 0; i < n; ++i) {
  //  cout << i << " " << j << "\n";
    if (text[i] == pattern[j]) {
        j += 1;
    } else {
        i -= j ;
        j = 0;
    }

    if (j == m) {
        j = 0;
        i = i - m + 1;
        result.push_back(i);
    }
  }
  return result;
}

vector<int> compute_prefix_function(const string& pattern) {
    int m = pattern.size();
    vector<int> pf(m,0);
    int j = 0;
    for (int i = 1; i < m; ++i) {
        while(j > 0 && pattern[i] != pattern[j]) {
            j = pf[j-1];
        }

        if (pattern[i] == pattern[j]) {
            j += 1;
            pf[i] = j;
        }
    }

  //  for (int i = 0; i < m; ++i) {
  //      cout << pf[i] << " ";
  //  }
  //  cout << "\n";
    return pf;
}


vector<int> find_pattern_kmp (const string& pattern, const string& text) {
    vector<int> result;
    int m = pattern.size();
    int n = text.size();

    vector<int> pf = compute_prefix_function(pattern);
    int j = 0;
    for (int i = 0 ; i < n; ++i) {
        while (j > 0 && text[i] != pattern[j]) {
            j = pf[j-1];
        }

        if (text[i] == pattern[j]) {
            j += 1;
        }

        if (j == m) {
            result.push_back(i-m+1);
            j = pf[j-1];
        }
    }

    return result;
}


int main() {
  string pattern, text;
  cin >> pattern;
  cin >> text;
  vector<int> result = find_pattern_kmp(pattern, text);
  for (int i = 0; i < result.size(); ++i) {
    printf("%d ", result[i]);
  }
  printf("\n");
  return 0;
}
