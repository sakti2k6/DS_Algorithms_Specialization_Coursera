#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using std::vector;
using namespace std;

bool isoptimal(const vector<int>& v, int index, int target) {
    if (target == 0) {
        return true;
    }
    if (index == v.size() || target < 0) {
        return false;
    }
    bool take = false;
    bool take_n = false;
    if (v[index] <=  target) {
        take = isoptimal(v, index+1, target-v[index]);
        take_n = isoptimal(v, index+1, target);
    } else if (v[index] > target) {
        take = false;
        take_n = isoptimal(v, index+1, target);
    }
    return take || take_n;
}



bool partition3(vector<int> &A) {
  //write your code here
    int n = A.size();
    std::sort(begin(A),end(A),greater<int>());
    int sum = std::accumulate(begin(A),end(A),0);
    int target;
    if (n < 3) {
        return 0;
    }
    if (sum % 3 == 0) {
        target = sum/3;
    } else {
        return 0;
    }

    bool result;
    int target1 = target, target2 = target, target3 = target;
    for (int i = 0; i < A.size(); ++i) {
        if (A[i] > target ) {
            return 0;
        } else {
            bool a1 = false, a2 = false, a3 = false;
            //cout << "target: " << target  << " target-A[i]: " << target-A[i] << "," << i << endl;
            a1 = isoptimal(A,i+1,target1-A[i]);
            if (a1) 
                target1 -= A[i];
            else {
                a2 = isoptimal(A,i+1,target2-A[i]);
                if (a2) 
                    target2 -= A[i];
                else
                    a3 = isoptimal(A,i+1,target3-A[i]);
                    if (a3) 
                        target3 -= A[i];
            }
            result = a1 || a2 || a3;
            //cout << "result: " << a1 << "," << a2  <<"," << a3 <<endl;
            if (result == false) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> A(n);
  for (size_t i = 0; i < A.size(); ++i) {
    std::cin >> A[i];
  }
  
  //vector<int> C = {17,59,34,57,17,23,67,1,18,2,59};
  //vector<int> B = {1,2,3,4,5,5,7,7,8,10,12,19,25};
  //vector<int> A = {2,3,2,1,4,1,6,2};
  std::cout << partition3(A) << '\n';
}
