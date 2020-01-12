#include<iostream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

int main() {
    vector<int> vec = {5,4,3,1,9,8,2,7};
    vector<int> vec2 = {5,4,3,51,9,8,2,7};
    auto iter = min_element(begin(vec),end(vec));
    int index = iter - begin(vec);
    cout  << "," << *iter << "\n";
    cout  << vec2[index] << "\n";

    vector<vector<int>> vec3;
    vec3.push_back({19,2,4});
   // for (const auto& e: vec3)
      //  cout << vec3[0][2] << "\n";

    int a = min({8,6,5});
    cout << "a " << a << "\n";
    vector<int> temp(7);
    vector<vector<int>> T(5,temp);
    cout << T[0][5] << "\n";
}
