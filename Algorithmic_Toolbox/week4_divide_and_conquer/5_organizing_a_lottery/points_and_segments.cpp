#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using std::vector;
using namespace std;

vector<int> fast_count_segments(vector<int>& starts, vector<int>& ends, vector<int>& points) {
    vector<pair<int,string>> segments;
    segments.reserve(starts.size() + ends.size() + points.size());
    for (size_t i = 0; i < starts.size(); ++i) 
        segments.push_back(make_pair(starts[i],"0start"));

    unordered_map<int,int> points_map;
    for (size_t i = 0; i < points.size(); ++i) {
        if (points_map.find(points[i]) == points_map.end()) {
            segments.push_back(make_pair(points[i],"1point"));
            points_map[points[i]] = 0;
        }
    }

    for (size_t i = 0; i < starts.size(); ++i) 
        segments.push_back(make_pair(ends[i],"2end"));

    //Sort based on type of element, start-point-end order;
    //sort( begin(segments), end(segments), [](const auto& a, const auto& b) {return a.second < b.second ;} );
    //Do std::stable_sort" sorts based on 1st element of pair (does by default) so that ordering of elements is maintained.
    stable_sort( begin(segments), end(segments));

    int cnt = 0;
    for (size_t i = 0; i < segments.size(); ++i) {
        if (segments[i].second == "0start") 
            cnt += 1;

        else if (segments[i].second == "1point") 
            points_map[segments[i].first] += cnt;

        else if (segments[i].second == "2end") 
            cnt -= 1;
    }

    vector<int> cnts(points.size());
    for(size_t i = 0; i < points.size() ; ++i) 
        cnts[i] = points_map[points[i]];

    return cnts;
}

vector<int> naive_count_segments(vector<int> starts, vector<int> ends, vector<int> points) {
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
  vector<int> cnt = fast_count_segments(starts, ends, points);
  for (size_t i = 0; i < cnt.size(); i++) {
    std::cout << cnt[i] << ' ';
  }
}
