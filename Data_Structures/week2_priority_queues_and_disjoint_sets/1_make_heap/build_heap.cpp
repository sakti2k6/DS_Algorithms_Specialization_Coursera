#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
      cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
  }

  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }

  void shiftdown(int i) {
      int n = data_.size();
      int nextI = i;

      if (left(i) < n && data_[left(i)] < data_[nextI]) 
          nextI = left(i);
      
      if (right(i) < n && data_[right(i)] < data_[nextI]) 
          nextI = right(i);
      
      if (i != nextI) {
          swaps_.push_back(make_pair(i,nextI));
          std::swap (data_[i],data_[nextI]);
          shiftdown(nextI);
      }
  }

  int left(int i) {
      return 2*i+1;
  }
  int right(int i) {
      return 2*i+2;
  }

  void GenerateSwaps() {
    swaps_.clear();
    //find 1st parent node which has child;
    int p = data_.size()/2 - 1;
    for (int i = p; i >= 0; --i) 
          shiftdown(i);
    }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
