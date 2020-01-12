#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>

using std::vector;
using namespace std;

vector<int> optimal_sequence_1(int n) {
  std::vector<int> sequence;
  while (n >= 1) {
    sequence.push_back(n);
    if (n % 3 == 0) {
      n /= 3;
    } else if (n % 2 == 0) {
      n /= 2;
    } else {
      n = n - 1;
    }
  }
  reverse(sequence.begin(), sequence.end());
  return sequence;
}

void printvec (const vector<int>& vec) {
    for(const auto& e: vec) 
            cout << e << " " ;
    cout << "\n";
}

vector<int> optimal_sequence (int n) {
    vector<vector<int>> sequence;
    vector<int> steps;
    sequence.reserve(n+1);
    steps.reserve(n+1);
    sequence[1] = {1};
    steps[1] = 1;
    for (int i = 2; i <= n; ++i) {
        vector<vector<int>> temp_seq;
        vector<int> temp_steps;
        if (i%3 == 0) {
            temp_seq.push_back(sequence[i/3]);
            temp_steps.push_back(steps[i/3] + 1);
        }
        
        if (i%2 == 0) {
            temp_seq.push_back(sequence[i/2]);
            temp_steps.push_back(steps[i/2] + 1);
        }
        
        temp_seq.push_back(sequence[i-1]);
        temp_steps.push_back(steps[i-1] + 1);

        auto iter = std::min_element(begin(temp_steps),end(temp_steps));
        steps[i] = *iter;

        //Find index of min element;
        int index = iter - begin(temp_steps);
        sequence[i] = temp_seq[index];
        sequence[i].push_back(i);
       // printvec(sequence[i]); 
    } 
  //  cout << "Final Sequence: " << sequence[n] << "\n";
    return sequence[n];
}


int main() {
  int n;
  std::cin >> n;
  vector<int> sequence = optimal_sequence(n);
  std::cout << sequence.size() - 1 << std::endl;
  for (size_t i = 0; i < sequence.size(); ++i) {
    std::cout << sequence[i] << " ";
  }
 // cout << "\n";
}
