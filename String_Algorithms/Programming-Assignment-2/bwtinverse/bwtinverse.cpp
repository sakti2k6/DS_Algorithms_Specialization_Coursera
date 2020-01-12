#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::unordered_map;

void printv (const vector<pair<char,int>>& vec) {
    for (const auto& e: vec) {
        cout << e.first << " " << e.second << "\n";
    }
}

string InverseBWT(const string& bwt) {
    string text = "";
    vector<pair<char,int>> bwt_string;
    vector<pair<char,int>> bwt_sort;
    unordered_map<char,int> myset;

    for (int i = 0; i < bwt.size(); ++i) {
        pair<char,int> t_pair;
        if (myset.find(bwt[i]) != myset.end()) {
            myset[bwt[i]] +=  1;
            t_pair = std::make_pair(bwt[i],myset[bwt[i]]);
        } else {
            myset[bwt[i]] =  0;
            t_pair = std::make_pair(bwt[i],0);
        }
        
        bwt_string.push_back(t_pair);
        bwt_sort.push_back(t_pair);
    }

    std::sort(bwt_sort.begin(), bwt_sort.end(), [](const auto& p1, const auto& p2) {
                if (p1.first == p2.first) 
                    return p1.second < p2.second;
                else 
                    return p1.first < p2.first;
                });

    cout << "Printing unsorted vec" << "\n" ;
    printv(bwt_string);
    cout << "Printing sorted vec" << "\n" ;
    printv(bwt_sort);

    return text;
}

int main() {
  string bwt;
  cin >> bwt;
  cout << InverseBWT(bwt) << endl;
  return 0;
}
