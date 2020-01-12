#include <iostream>

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

int fibonacci_sum_squares_fast(const long long& n) {
  
  // pisano period for 10 is 300;
  int reduced_number = n % 300 ;
  
  if (reduced_number <= 1)
    return reduced_number;
  
  int previous = 0;
  int current = 1;
  
  for (long long i=2; i < reduced_number + 2; ++i) {
    int temp_previous = current;
    current = (previous + current) % 10;
    previous = temp_previous;
  }
  
  //std::cout << current << " " << previous << std::endl;
  return (current * previous) % 10;
}

int main123() {
    long long n = 0;
    std::cin >> n;
   // std::cout << fibonacci_sum_squares_naive(n);
    std::cout << fibonacci_sum_squares_fast(n) << '\n';
    return 0;
}

