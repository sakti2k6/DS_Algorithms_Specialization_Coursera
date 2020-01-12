#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::swap;

/*int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[r], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort(a, l, m - 1);
  randomized_quick_sort(a, m + 1, r);
}*/

vector<int> partition3(vector<int>& a, int l, int r) {
    //Pivot element is the rightmost one
    int pivot = a[r];
    
    int m1 = l;
    for (int i = l; i < r; ++i) {
        if (a[i] < pivot) {
            if (i != m1)
                swap(a[i],a[m1]);
            ++m1;
        }
    }

    swap(a[m1],a[r]);
    //std::cout << "Count: " << count << "\n";

    int m2 = m1 + 1 ;
    for (int i = m1+1; i <= r; ++i) {
        if (a[i] == pivot){
            swap(a[i],a[m2]);
            ++m2;
        }
    }
    
    vector<int> index;
    index.push_back(m1);
    index.push_back(m2);
    return index;
}

void randomized_quick_sort3(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[r], a[k]);
  vector<int> index;
  index.reserve(2);
  index = partition3(a, l, r);

  randomized_quick_sort3(a, l, index[0]-1);
  randomized_quick_sort3(a, index[1], r);

}

int main() {
/*  
  vector<int> a(10);
  for (size_t i = 0; i < a.size(); ++i) {
    a[i] = 2;
  } 
  a[3] = 51;
  a[9] = 11;

  randomized_quick_sort3(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }
 std::cout << "\nsort3 results are\n";
*/
  

  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  } 

  randomized_quick_sort3(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }

}
