#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::max;

int compute_min_refills(int dist, int tank, vector<int> & stops) {
    int currCapacity = tank;
    int prevStation = 0;
    int numRefills = 0;
   // stops.emplace_back(dist);
    for (int i = 0; i < stops.size();  ++i) {
        if ((currCapacity < stops[i]) && (prevStation == 0) ) {
            return -1;
        }
        if (currCapacity == stops[i]) {
            prevStation = 0;
            currCapacity = stops[i] + tank;
            ++numRefills; 
        } else if (currCapacity < stops[i]) {
            prevStation = 0;
            currCapacity = stops[i-1] + tank;
            ++numRefills;
        } else {
            ++prevStation;
            if (i == (stops.size() - 1)) {
                if (currCapacity >= dist) {
                    return numRefills;
                } else if (stops[i] + tank >= dist) {
                    ++numRefills;
                    return numRefills;
                } else {
                    return -1;
                }
            }
        }
    }

        return numRefills;
}


int main() {
    int d = 0;
    cin >> d;
    int m = 0;
    cin >> m;
    int n = 0;
    cin >> n;

    vector<int> stops(n);
    for (size_t i = 0; i < n; ++i)
        cin >> stops.at(i);

    cout << compute_min_refills(d, m, stops) << "\n";

    return 0;
}
