#include <iostream>
#include <vector>

using std::vector;
using namespace std;

int merge (vector<int>& a, int low, int mid, int high) {
    int invs = 0;
    
    vector<int> b(mid - low);
    for (int i = 0; i < b.size() ; ++i) 
        b[i] = a[low+i];
    
    vector<int> c(high - mid + 1);
    for (int i = 0; i < c.size() ; ++i) 
        c[i] = a[mid+i];
   
    int i = 0;
    int j = 0;
    int k = low;

    while(i < b.size() && j < c.size()) {
        if (b[i] <= c[j]) {
            a[k] = b[i];
            ++i;
        } else {
            a[k] = c[j];
            ++j;
            invs += mid - (i+low);
        }
        ++k;
    }

    while(i < b.size()) {
        a[k] = b[i];
        ++i;
        ++k;
    }
    while(j < c.size()) {
        a[k] = c[j];
        ++j;
        ++k;
    }

    return invs;
}

int get_number_of_inversions(vector<int>& a, int low,int high) {
    int invs = 0;
    if (low >= high) {
        return 0;
    }

    int mid = low + (high-low)/2;
    int invs_l = get_number_of_inversions(a,low,mid);
    int invs_r = get_number_of_inversions(a,mid+1,high);

    int invs_m = merge(a,low,mid+1,high);

    invs = invs_l + invs_r + invs_m;
    cout << "invs: " << invs << endl;
    return invs;
}

int main() {
    /*
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  */
    vector<int> a = {5,4,3,2,1,0};
  std::cout << get_number_of_inversions(a,0, a.size()-1) << '\n';
}
