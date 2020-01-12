#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include<algorithm>

using std::vector;
using std::string;
using std::max;
using std::min;
using namespace std;
typedef long long int lng;
using plong = pair<long long, long long>;

lng eval(lng a, lng b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
    assert(0);
  }
}

pair<lng,lng> get_min_max(const pair<lng,lng>& left, const pair<lng,lng>& right, char op) {
    lng e1 = eval(left.first,  right.first,  op);
    lng e2 = eval(left.first,  right.second, op);
    lng e3 = eval(left.second, right.second, op);
    lng e4 = eval(left.second, right.first,  op);
    pair<lng,lng> result = std::minmax({e1,e2,e3,e4});
    return result;
}


void  get_maximum_value(const string &exp) {
    int len = exp.length();
    int size = len/2 + 1;

    lng minval[size][size];
    lng maxval[size][size];

    for (int i = 0; i < size; ++i) {
        for (int j = low; j < size; ++j) {
            //Base case for substring of size 1
            if ( i == j ) 
                T[i][j] = exp[i];
            else {
                int k = 0;
                while (k < )
            } 

    }

}

int main() {
  string s;
  //std::cin >> s;
  s = "5-8+7*4-8+9";
  return 0;
 // std::cout << get_maximum_value(s).second << '\n';
}
