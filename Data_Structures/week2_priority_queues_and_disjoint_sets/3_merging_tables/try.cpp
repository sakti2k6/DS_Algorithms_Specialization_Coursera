#include<iostream>
#include<vector>
#include<algorithm>
#include<functional>

using std::vector;
using std::cin;
using std::cout;

struct table {
    int id{};
    long long val{};
    table(int _id, int _val) :
        id(_id), val(_val) {}
};

class merge_tables {
    public:
    
    vector<table> parents;
    vector<int> ranks;
    long long maxval = 0;

    void makeset(int index, int val) {
        parents.push_back(table(index,val));
        ranks.push_back(0);
        if (val > maxval) 
            maxval = val;
    }

    int find(int i) {
        if (i != parents[i].id) {
            int result = find(parents[i].id);
            parents[i].id = result;
        } 
            return parents[i].id ;
    }

    void join(int l, int r) {
        
        int l_id = find(l);
        int r_id = find(r);
        
        if (l_id == r_id ) {
            cout << maxval << "\n";
            return;
        }

        if (ranks[l_id] < ranks[r_id]) {
            parents[l_id].id = r_id;
            parents[r_id].val += parents[l_id].val;
            parents[l_id].val = 0;
            if (parents[r_id].val > maxval) {
                maxval = parents[r_id].val;
            }
            cout << maxval << "\n";
        } else {
            parents[r_id].id = l_id;
            parents[l_id].val += parents[r_id].val;
            parents[r_id].val = 0;
            if (parents[l_id].val > maxval) {
                maxval = parents[l_id].val;
            }
            cout << maxval << "\n";
            if (ranks[l_id] == ranks[r_id])
                ranks[l_id] += 1;
        }
    }
    
};

int main() {
  /*  vector<int> vec(5,1);
    vector<int> dest = {3,2,1,5,5};
    vector<int> src = {5,4,4,4,3}; 
    vector<int> vec = {10,0,5,0,3,3}; 
    vector<int> dest = {6,6,5,4};
    vector<int> src = {6,5,4,3}; */
    merge_tables tb;
	int n, m;
	cin >> n >> m;

    for (int i = 0; i < n ; ++i) {
        int temp;
        cin >> temp;
        tb.makeset(i,temp);
    }
    
    for (int i = 0; i < m ; ++i) {
        int dest,src;
        cin >> dest >> src;
        tb.join(dest-1,src-1);
    }
    return 0;
};
