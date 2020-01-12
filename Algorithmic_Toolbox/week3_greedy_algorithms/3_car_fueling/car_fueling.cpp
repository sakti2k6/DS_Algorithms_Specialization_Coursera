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
    stops.emplace_back(dist);
    int size = stops.size();

    int i = 0;
    while (currCapacity < dist) {
        if ((stops[i] > currCapacity) && (prevStation == 0) ) {
            return -1;
        }
        if (stops[i] == currCapacity) {
            prevStation = 0;
            currCapacity = stops[i] + tank;
            ++numRefills; 
            ++i;
        } else if (stops[i] > currCapacity) {
            prevStation = 0;
            currCapacity = stops[i-1] + tank;
            ++numRefills;
        } else {
            ++prevStation;
            ++i;
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
