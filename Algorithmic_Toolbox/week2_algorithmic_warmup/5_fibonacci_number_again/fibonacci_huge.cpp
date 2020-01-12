#include <iostream>

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;

    for (long long i = 0; i < n + 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % m;
}

long int get_pisano_period (const int& m) {
  int previous = 0;
  int current = 1;
  long int i = 1;
  do {
    int temp_previous = current;
    current = (previous + current) % m;
    previous = temp_previous;
    if (previous == 0 && current == 1)
      return i;
    else
      ++i;
  } while (true) ;
}

int find_Fn_mod_m (const long long& n, const int& m) {
  
  long int pisano_period = get_pisano_period(m);
  int fibindex = n % pisano_period;
  
  if (fibindex <= 1)
    return fibindex;
  
  int previous = 0;
  int current = 1;
  
  for (int i = 2; i <fibindex + 1; ++i ) {
    int temp_previous = current;
    current = (current + previous) % m;
    previous = temp_previous;
  }
  
  return current;
}

int main122() {
  long long n;
  int m;
  std::cin >> n >> m;
  //std::cout << get_fibonacci_huge_naive(n, m) << '\n';
  //std::cout << get_pisano_period(m) << '\n';
  std::cout << find_Fn_mod_m(n, m) << '\n';
  return 0;
}
