#include <iostream>
#include <vector>
#include<algorithm>
#include<iterator>

using namespace std;

int get_change(int m) {
   
  // Given spare coins  
  vector<int> coins = {1,3,4};

  //Create a vector to store spares for all values till m
  vector<int> table(m+1);
  
  table[0] = 0;
  for (size_t i = 1; i <= m; ++i) {
      vector<int> temp;
      for(int j = 0; j < 3; ++j) {  //Iterate through all 3 spare coins
          if (i == coins[j]) 
              temp.push_back(1); //it takes only 1 spare coin to change the spare coin value.
          else if (i > coins[j]) 
              temp.push_back(table[i-coins[j]] + table[coins[j]]); 

      }
        table[i] = *std::min_element(std::begin(temp),std::end(temp));
        //cout << "table[" << i << "]:" << table[i] << "\n";
  }

  return table[m];
}

int main() {
  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}
