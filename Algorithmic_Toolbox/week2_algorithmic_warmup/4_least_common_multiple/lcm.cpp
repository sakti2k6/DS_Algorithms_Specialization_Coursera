#include <iostream>

long long lcm_naive(int a, int b) {
  for (long l = 1; l <= (long long) a * b; ++l)
    if (l % a == 0 && l % b == 0)
      return l;

  return (long long) a * b;
}

int gcd_fast(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd_fast(b%a, a);
}

long long int lcm_my_naive(int a, int b){
    for (long int i=1; i < a+1; ++i) {
        if ((long long int)(b*i) % a == 0)
            return (long long int)b*i;
    }
    return 0;
}

long long int lcm_fast(int a, int b) {
    return (a/gcd_fast(a, b)) * (long long int)b;
}

int main61() {
  int a, b;
  std::cin >> a >> b;
  std::cout << lcm_fast(a, b) << std::endl;
//  std::cout << lcm_my_naive(a, b) << std::endl;
 // std::cout << lcm_naive(a, b) << std::endl;
  return 0;
}
