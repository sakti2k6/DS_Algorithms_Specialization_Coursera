#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>

using std::vector;
using namespace std;

int get_majority_element(vector<int> &a, int left, int right) {
	map<int,int> dict;
	for (const int& e: a) {
		if (dict.count(e))   { //If element e exists as key
			auto iter = dict.find(e);
			iter->second += 1;
			if (iter->second > right/2) 
				return 1;
		} else {
			dict.insert(pair<int,int>(e,1));
		}
	}

	return 0;	
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << get_majority_element(a, 0, a.size() ) << '\n';
}
