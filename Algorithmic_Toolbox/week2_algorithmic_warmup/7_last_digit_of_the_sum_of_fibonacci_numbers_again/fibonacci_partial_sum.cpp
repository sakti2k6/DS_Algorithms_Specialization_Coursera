#include <iostream>
#include <vector>
using std::vector;

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;

    long long current = 0;
    long long next  = 1;

    for (long long i = 0; i <= to; ++i) {
        if (i >= from) {
            sum += current;
        }

        long long new_current = next;
        next = next + current;
        current = new_current;
    }

    return sum % 10;
}

int get_fibonacci_last_digit_fast(const long long& n) {

  // pisano period for 10 is 300;
  int reduced_number = n % 300 ;
  
  if (reduced_number <= 1)
    return reduced_number;
  
  int previous = 0;
  int current = 1;
  
  for (long long i = 2; i < reduced_number + 1; ++i) {
    int temp_previous = current;
    current = (current + previous) % 10;
    previous = temp_previous;
  }
  
  return current % 10;
}

int get_last_digit_of_fibonacci_sum_fast (const long long& n) {
  
  // pisano period for 10 is 300;
  int reduced_number = n % 300 ;
  
  if (reduced_number <= 1)
    return reduced_number;
  
  int previous = 0;
  int current = 1;
  
  for (long long i = 2; i < reduced_number + 3; ++i) {
    int temp_previous = current;
    current = (current + previous) % 10;
    previous = temp_previous;
  }
  
  return ((current + 10) - 1) % 10;
}

int get_fibonacci_partial_sum_fast(const long long& from, const long long& to) { 
  if ( from == 0)
    return get_last_digit_of_fibonacci_sum_fast(to) % 10;
  else if (from == to) 
    return get_fibonacci_last_digit_fast(to);	
  else   	
    return (get_last_digit_of_fibonacci_sum_fast(to) + 10 - get_last_digit_of_fibonacci_sum_fast(from-1)) % 10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    //std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
    std::cout << get_fibonacci_partial_sum_fast(from, to) << '\n';
    return 0;
}

