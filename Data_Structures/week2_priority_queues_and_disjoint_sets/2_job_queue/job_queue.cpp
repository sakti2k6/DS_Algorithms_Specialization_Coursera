#include <iostream>
#include <vector>
#include <algorithm>
#include<queue>
#include<functional>

using std::vector;
using std::cin;
using std::cout;
using namespace std;

template<typename T> 
using min_heap = std::priority_queue<T,vector<T>,std::greater<T>>;

struct threads {
    public:
    long long time;
    int index;
    
    threads(long long time_, int index_) :
        time(time_), index(index_) {};
    
    bool operator> (const threads& t) const {
        if (time == t.time) 
            return index > t.index;
        else
            return time > t.time;
    }
};

class JobQueue {
 private:
  int num_threads_;
  vector<int> jobs_;

  vector<int> assigned_threads_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_threads_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_threads_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }

  void AssignJobs() {
    // TODO: replace this code with a faster algorithm.
    assigned_threads_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    vector<long long> next_free_time(num_threads_, 0);
    for (int i = 0; i < jobs_.size(); ++i) {
      int duration = jobs_[i];
      int next_thread = 0;
      for (int j = 0; j < num_threads_; ++j) {
        if (next_free_time[j] < next_free_time[next_thread])
          next_thread = j;
      }
      assigned_threads_[i] = next_thread;
      start_times_[i] = next_free_time[next_thread];
      next_free_time[next_thread] += duration;
    }
  }

  void AssignJobs_optimized() {
    assigned_threads_.resize(jobs_.size());
    start_times_.resize(jobs_.size());
    min_heap<threads> threads_status;
    for (int i = 0; i < num_threads_ ; ++i) {
        threads_status.emplace(threads(0,i));
    }

    for (int i = 0; i < jobs_.size(); ++i) {
      int index = threads_status.top().index;
      long long time = threads_status.top().time;

      assigned_threads_[i] = index;
      start_times_[i] = time;

      threads_status.pop();
      threads_status.emplace(threads(time+jobs_[i],index));
    }

  }

 public:
  void Solve() {
    ReadData();
    //AssignJobs();
    AssignJobs_optimized();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
