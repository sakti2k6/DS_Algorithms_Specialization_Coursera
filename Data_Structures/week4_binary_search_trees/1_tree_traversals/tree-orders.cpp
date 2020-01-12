#include <iostream>
#include <vector>
#include <algorithm>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

 // int n = 5;
 // vector <int> key = {4,2,5,1,3};
 // vector <int> left = {1,3,-1,-1,-1};
 // vector <int> right = {2,4,-1,-1,-1};

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }

  void in_order_traversal (vector<int>& result, int index) {
    if (index == -1) return;
    int left_i = left[index];
    int right_i = right[index];
    in_order_traversal(result,left_i);
    result.push_back(key[index]);
    in_order_traversal(result,right_i);
  }
  
  vector <int> in_order() {
    vector<int> result;
    in_order_traversal(result,0);
    return result;
  }

  void pre_order_traversal (vector<int>& result, int index) {
    if (index == -1) return;
    int left_i = left[index];
    int right_i = right[index];
    result.push_back(key[index]);
    pre_order_traversal(result,left_i);
    pre_order_traversal(result,right_i);
  }

  vector <int> pre_order() {
    vector<int> result;    
    pre_order_traversal(result,0);
    return result;
  }

  void post_order_traversal (vector<int>& result, int index) {
    if (index == -1) return;
    int left_i = left[index];
    int right_i = right[index];
    post_order_traversal(result,left_i);
    post_order_traversal(result,right_i);
    result.push_back(key[index]);
  }

  vector <int> post_order() {
    vector<int> result;
    post_order_traversal(result,0);
    return result;
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main_with_large_stack_space() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }
#endif

  return main_with_large_stack_space();
}

