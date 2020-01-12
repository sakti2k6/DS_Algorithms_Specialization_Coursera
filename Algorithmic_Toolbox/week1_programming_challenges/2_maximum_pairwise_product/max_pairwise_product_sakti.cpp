//
//  main.cpp
//  Algorithm_Toolbox_Course
//
//  Created by Sakti on 5/16/19.
//  Copyright © 2019 Sakti. All rights reserved.
//

#include <iostream>
#include <vector>

using namespace std;

long int MaxPairWiseProduct(const vector<int>& vec) {
    int max1{};
    int max2{};
    for (const int& e : vec) {
        if (e > max1) {
            max2 = max1;
            max1 = e;
        } else if (e > max2) {
            max2 = e;
        }
    }
    return (long int)max1*max2;
}


int main(int argc, const char * argv[]) {
    // insert code here...
    int n;
    std::cin >> n;
    std::vector<int> vec(n);
    for (int i=0; i < n; ++i)
        std::cin >> vec[i];
    std::cout << MaxPairWiseProduct(vec) << std::endl;
    return 0;
}
