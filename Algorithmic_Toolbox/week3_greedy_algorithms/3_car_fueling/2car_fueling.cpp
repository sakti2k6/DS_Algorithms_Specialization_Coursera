#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    int currCapacity = tank;
    int prevStation = 0;
    int numRefills = 0;
    stops.emplace_back(dist);
    int size = stops.size();
    for (int i = 0; i < size;  ++i) {
        if ((currCapacity < stops[i]) && (prevStation == 0) ) {
            return -1;
        }
        if (currCapacity == stops[i] && i != size-1) {
            prevStation = 0;
            currCapacity = stops[i] + tank;
            ++numRefills; 
        } else if (currCapacity < stops[i]) {
            prevStation = 0;
            currCapacity = stops[i-1] + tank;
            ++numRefills;
        } else {
            ++prevStation;
        }
    }

        return numRefills;
}


int main() {

    for (int i=0; i<101; ++i) {
    int d = rand() % 100000 + 1;
    int m = rand() % 400 + 1;
    int n = rand() % 300 + 1;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        stops[i] = rand() % d;
    
    std::sort(begin(stops), end(stops));
    cout << "Final Distance(d): " << d << "\n";
    cout << "Tank  Capacity(m): " << m << "\n";
    cout << "No of Stops(n): " << n << "\n";
  //  for (const int& e: stops)
    //    cout << e << " ";
    cout << "\n";

    
    cout << compute_min_refills(d, m, stops) << "\n";
    }

    return 0;
}
