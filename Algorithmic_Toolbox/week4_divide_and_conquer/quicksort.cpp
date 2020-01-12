#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void swap(int* a , int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition_last(vector<int>& vec,int low,int high) {
    
    //Pivot element = last element
    int pivot = vec[high];

    //Find the sorted index position for pivot element
    int index = low;
    for (int i = low ; i < high; ++i) {
        if (vec[i] <= pivot) {
            if (i != index)
                swap(&vec[i],&vec[index]);
            ++index;
        }
    }

    //Put the pivot element at its sorted position
    swap(&vec[high],&vec[index]);

    return index ;
}

int partition_first(vector<int>& vec,int low,int high) {
    
    //Pivot element = first element
    int pivot = vec[low];

    //Find the sorted index position for pivot element
    int index = high;
    for (int i = high ; i > low; --i) {
        if (vec[i] >= pivot) {
            if (i != index)
                swap(&vec[i],&vec[index]);
            --index;
        }
    }

    //Put the pivot element at its sorted position
    swap(&vec[low],&vec[index]);

    return index ;
}

void quicksort (vector<int>& vec, int low, int high) {
    
    //If there is one element or aray index goes out of bound, return
    if (low >= high) 
        return;

    int sortedIndex;

    sortedIndex = partition_first(vec,low,high);

    //Call quicksort to on the left and right side of sortedIndex

    quicksort(vec,low,sortedIndex-1);
    quicksort(vec,sortedIndex+1,high);

}

void printvec(const vector<int>& vec) {
    for (const int& e: vec)
        cout << e << " " ;
    cout << endl;
}

int main() {
    vector<int> vec = {6, 4, 8, 2, 5, 7};
   // vector<int> vec = {5,4,3,2,1,0,5,5};
    int low = 0;
    int high = vec.size() - 1;
    printvec(vec);
    quicksort(vec,low,high);
    printvec(vec);
    return 0;
}
