#include <iostream>
#include <cassert>
#include <vector>

using std::vector;
using namespace std;

int binary_search_impl(const vector<int>& a, int left, int right, int x) {
	if (left > right) 
		return -1;
	else {
		int middle = left + (right - left)/2 ;
		if (a[middle] == x) 
			return middle;
		else if (a[middle] > x) 
			return binary_search_impl(a,left,middle-1,x);
		else  // (a[middle] < x) 
			return binary_search_impl(a,middle+1,right,x);
	}
}

int binary_search(const vector<int> &a, int x) {
  int left = 0; 
  int right = (int)a.size()-1; 
// Recursive implementation
  return binary_search_impl(a,left,right,x);
 
 //Iterative Implementation
 /* 
  while ( left <= right) {
  	int middle = left + (right-left)/2;
	if (a[middle] == x)
		return middle;
	else if (a[middle] > x)
		right = middle - 1;
	else // (a[middle] < x)
		left = middle + 1;
  }

  return -1;
  */
}

int linear_search(const vector<int> &a, int x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
