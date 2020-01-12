#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <numeric>
#include <cmath>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;

void print(const vector<int>& vec) {
    for(int i=0; i < vec.size(); ++i) 
        cout << vec[i] << " ";
    cout << "\n";
}

void printp(const vector<pair<int,int>>& vec) {
    for(int i=0; i < vec.size(); ++i) 
        cout << vec[i].first << " " << vec[i].second << " ,";
    cout << "\n";
}

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
    int n = text.size();
    vector<int> result(n);
    vector<int> idx(n);

    std::iota(idx.begin(),idx.end(),0);

    //print(idx);
    std::sort(idx.begin(),idx.end(),[&text](int i, int j) {return text[i] < text[j];});
    //print(idx);

    vector<int> ranks(n);
    int count = -1;
    char curr = '\0';
    for (int i = 0; i < n; ++i) {
        if (curr != text[idx[i]]) {
            count += 1;
            curr = text[idx[i]];
        }
        ranks[idx[i]] = count;
    }

   // print(ranks);
    int l = 0;
    while (std::pow(2,l) < n) {
        int k = pow(2,l);
        vector<pair<int,int>> prefix(n);
        for (int i = 0; i < n; ++i) {
            prefix[i].first = ranks[i];
            prefix[i].second = ranks[(i+k)%n];
        }

      //  printp(prefix);
        idx.clear();
        idx.resize(n);
        std::iota(idx.begin(),idx.end(),0);
        std::sort(idx.begin(),idx.end(),[&prefix](int i, int j) {
                if (prefix[i].first == prefix[j].first)
                    return prefix[i].second < prefix[j].second;
                else 
                    return prefix[i].first < prefix[j].first;
                });
    
    /*    std::sort(idx.begin(),idx.end(),[&prefix](int i, int j) {
                    return prefix[i].second < prefix[j].second;
                  //  return prefix[i].first < prefix[j].first;
                });
        print(idx);

        std::sort(idx.begin(),idx.end(),[&prefix](int i, int j) {
                    return prefix[i].first < prefix[j].first;
                }); */
    
     //   print(idx);
      /*  std::sort(prefix.begin(),prefix.end(),[](pair<int,int>& i, pair<int,int>& j) {
                if (i.first == j.first)
                    return i.second < j.second;
                else 
                    return i.first < j.first;
                }); */
      /*  std::sort(prefix.begin(),prefix.end(),[](pair<int,int>& i, pair<int,int>& j) {
                    return i.second < j.second;
                });
        printp(prefix);
        std::sort(prefix.begin(),prefix.end(),[](pair<int,int>& i, pair<int,int>& j) {
                    return i.first < j.first;
                }); */
      //  printp(prefix);
    ranks.clear();
    ranks.resize(n,0);
    int count = -1;
    pair<int,int> tpair;
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            tpair = prefix[idx[i]];
            count += 1;
        } else if (tpair != prefix[idx[i]]) {
            tpair = prefix[idx[i]];
            count += 1;
        }

        ranks[idx[i]] = count;
    }

    l += 1;
   // print(ranks);

    }

    for (int i = 0; i < n; ++i) {
        result[ranks[i]] = i;
    }

    return result;
}

int main() {
  string text;
  cin >> text;
  vector<int> suffix_array = BuildSuffixArray(text);
  for (int i = 0; i < suffix_array.size(); ++i) {
    cout << suffix_array[i] << ' ';
  }
  cout << endl;
  return 0;
}
