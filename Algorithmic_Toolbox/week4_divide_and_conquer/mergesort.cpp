#include<iostream>
#include<algorithm>
#include<vector>
#include<iterator>

using namespace std;

void printvec(const vector<int>& vec) {
    for (const int& e: vec)
        cout << e << " " ;
    cout << endl;
}

vector<int> merge(vector<int> a, int low, int mid, int high) {
    vector<int> a;
    return a;
}

void mergesort(vector<int>& a,int low,int high) {
    if (low >= high) 
        return;
    
    int mid = low + (high-low)/2 ;

    mergesort(a,low,mid);
    mergesort(a,mid+1,high);
    merge(a,low,mid,high);
}

int main() {
    vector<int> a = {9,8,7,6,5,4,3,2,1};
    printvec(a);
    mergesort(a,0,a.size()-1);
    printvec(a);
    
}
