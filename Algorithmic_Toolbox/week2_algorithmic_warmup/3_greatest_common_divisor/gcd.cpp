#include <iostream>

int gcd_naive(int a, int b) {
  int current_gcd = 0;
  for (int d = 1; d <= a && d <= b; d++) {
    if (a % d == 0 && b % d == 0) {
 //     if (d > current_gcd) {
        current_gcd = d;
 //     }
    }
  }
  return current_gcd;
}

// Time complexity of gcd_euclidian algorithm is O(log (a+b))
int gcd_euclidian(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd_euclidian(b%a, a);
}

int main6() {
  int a, b;
  std::cin >> a >> b;
 // std::cout << gcd_naive(a, b) << std::endl;
  std::cout << gcd_euclidian(a, b) << std::endl;
  return 0;
}

