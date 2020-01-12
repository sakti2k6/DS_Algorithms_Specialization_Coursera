#include <iostream>

int get_fibonacci_last_digit_naive(int n) {
    if (n <= 1)
        return n;

    int previous = 0;
    int current  = 1;

    for (int i = 0; i < n - 1; ++i) {
        int tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

int get_fibonacci_last_digit_fast(int n) {
    if (n <= 1)
        return n;
    
    int previous = 0;
    int current = 1;
    
    for (int i=2; i < n+1; ++i) {
        int temp_previous = current;
        current = (previous + current) % 10;
        previous = temp_previous;
    }
    
    return current;
}

int main5() {
    int n;
    std::cin >> n;
   // int c1 = get_fibonacci_last_digit_naive(n);
    int c = get_fibonacci_last_digit_fast(n);
    std::cout << c << '\n';
   // std::cout << c << " " << c1 << '\n';
    return 0;
    }
