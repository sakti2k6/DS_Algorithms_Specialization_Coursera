#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using std::vector;
using namespace std;
/*
struct segment {
    public:
    int start;
    int end;
    segment() {};
    segment(int _start, int _end) : start(_start),end(_end) {};
};
*/
void printseg(const vector<vector<int>>& seg) {
    for (const auto& e: seg)
        cout << e[0] << "," << e[1] << endl;
}

vector<int> fast_count_segments(vector<int>& starts, vector<int>& ends, vector<int>& points) {
  vector<int> cnt(points.size());
  //vector<vector<int>> segs(starts.size(),vector<int>(2));
  vector<pair<int, int>> segs;//(starts.size(),vector<int>(2));
//vector<vector<int>> segs;
  for (int i = 0; i < starts.size(); ++i) {
      //segs.emplace_back(vector<int> {starts[i],ends[i]});
      segs.emplace_back(make_pair(starts[i],ends[i]));
     // cout << segs[i].end << endl;
  }

 // printseg(segs);
  sort(begin(segs),end(segs),[](const auto& a, const auto& b){return a.first < b.first ;});
  //stable_sort(begin(segs),end(segs)); //[](const vector<int>& a, const vector<int>& b){return a[0] < b[0] ;});
  //printseg(segs);

  for (size_t i = 0; i < points.size(); ++i) {
      for (size_t j = 0; j < segs.size() ; ++j) {
          if (!(segs[j].first > points[i] || segs[j].second < points[i])) {
             // break;
          //} else {

          cnt[i] += 1; //segs[j][0] <= points[i] && points[i] <= segs[j][1]; 
          }
          
      }
  }

  return cnt;
}

vector<int> naive_count_segments(vector<int>& starts, vector<int>& ends, vector<int>& points) {
  vector<int> cnt(points.size());
  for (size_t i = 0; i < points.size(); i++) {
    for (size_t j = 0; j < starts.size(); j++) {
      cnt[i] += starts[j] <= points[i] && points[i] <= ends[j];
    }
  }
  return cnt;
}

int main() {

  int n, m;
  std::cin >> n >> m;
  vector<int> starts(n), ends(n);
  for (size_t i = 0; i < starts.size(); i++) {
    std::cin >> starts[i] >> ends[i];
  }
  vector<int> points(m);
  for (size_t i = 0; i < points.size(); i++) {
    std::cin >> points[i];
  } 
  
  /*
    vector<int> starts(50000,-100);
    vector<int> ends(50000,100);
    vector<int> points(50000,-100000000);
    vector<int> starts = {-10};
    vector<int> ends = {10};
    vector<int> points = {-100,100,0}; */
  //use fast_count_segments
  //vector<int> cnt = naive_count_segments(starts, ends, points);
  vector<int> cnt = naive_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
