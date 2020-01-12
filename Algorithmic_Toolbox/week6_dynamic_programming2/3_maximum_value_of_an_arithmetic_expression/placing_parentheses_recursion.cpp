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
typedef long long lint;

lint eval(lint a, lint b, char op) {
  if (op == '*') {
    return a * b;
  } else if (op == '+') {
    return a + b;
  } else if (op == '-') {
    return a - b;
  } else {
      //cout << "OP is " << op << endl;
    assert(0);
  }
}

pair<lint,lint> get_min_max(const pair<lint,lint>& left, const pair<lint,lint>& right, char op) {
    lint e1 = eval(left.first,  right.first,  op);
    lint e2 = eval(left.first,  right.second, op);
    lint e3 = eval(left.second, right.second, op);
    lint e4 = eval(left.second, right.first,  op);
    pair<lint,lint> result = std::minmax({e1,e2,e3,e4});
    return result;
}


pair<lint, lint>  get_maximum_value(const string &exp) {
    //cout << "String is: "  << exp << endl;
    int len = exp.length();
    //Base case. When substring size is less than 2, return the value.
    if (len < 2) {
        //cout << "Result: "  << (lint)stoi(exp) << endl;
        return make_pair((lint)stoi(exp),(lint)stoi(exp));
    }

    vector<pair<lint, lint>> results;
    int i = 0;
    while (i+2 < len ) {
        string left = exp.substr(0,i+1);
        string right = exp.substr(i+2);
        //cout << "left: "  << left << " right: " << right << endl;
        char op = exp[i+1];
        pair<lint,lint> each_result = get_min_max(get_maximum_value(left),get_maximum_value(right),op);
        results.push_back(each_result);
        i += 2;
    }
  
    //cout << "Vector: " ;
   // for ( auto& e: results ) 
        //cout << e.first << "," << e.second << "," ;
    //cout << endl ;
    pair<lint, lint> min_max_result;
    auto temp1 = *std::min_element (begin(results),end(results));
    min_max_result.first = temp1.first;
    auto temp2 = *std::max_element (begin(results),end(results), [](auto& a, auto& b){return a.second < b.second;});
    min_max_result.second = temp2.second;
    //cout << "Result: "  << min_max_result.first << "," << min_max_result.second << endl;
    return min_max_result;
}

int main() {
  string s;
  std::cin >> s;
 // s = "5-8+7*4-8+9";
  std::cout << get_maximum_value(s).second << '\n';
}
