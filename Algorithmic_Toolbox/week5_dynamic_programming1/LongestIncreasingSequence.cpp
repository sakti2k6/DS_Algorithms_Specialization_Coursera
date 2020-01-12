#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void printvec (const vector<int>& vec) {
    for(const auto& e: vec) 
            cout << e << " " ;
    cout << "\n";
}

int find_max(vector<vector<int>> vec) {
    int index = 0;
    int maxnum = vec[0].size();
    for (size_t i = 0 ; i < vec.size() ; ++i) {
        if (vec[i].size() > maxnum) {
            index = i;
            maxnum = vec[i].size();
        }
        cout << "vec[" << i << "]:" << vec[i].size() << "\n"; 
        printvec(vec[i]);
    }
    return index;
}

vector<int> get_lis(vector<int>& seq) {
    vector<vector<int>> lis(seq.size());
    lis[0] = {seq[0]};
    for (int j = 1; j < seq.size(); ++j) {
        int maxseq = 0;
        for (int i = j-1; i >= 0; --i) {
            if (seq[i] < seq[j]) {
                if (lis[i].size() > maxseq) {
                    lis[j] = lis[i];
                    maxseq = lis[i].size();
                }
            }
        }

        lis[j].push_back({seq[j]});
     //   printvec(lis[j]);
    }
   
    cout << "Size of lis:" << lis.size() << "\n";
  //  vector<int> a = *std::max_element(begin(lis),end(lis),[](const vector<int>& a,const vector<int>& b){cout << a.size() << "," << b.size() << endl;return a.size() < b.size();});
    vector<int> a = lis[find_max(lis)];
  //  printvec(a);
    return a;
}




int main() {
    vector<int> seq = {7,2,1,3,8,4,9,1,2,6,5,9,3,8,1};
    vector<int> lis = get_lis(seq);
    printvec(lis);
    return 0;
}
