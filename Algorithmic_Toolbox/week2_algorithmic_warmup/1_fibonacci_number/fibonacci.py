# Uses python3
def calc_fib(n):
    if (n <= 1):
        return n

    return calc_fib(n - 1) + calc_fib(n - 2)

n = int(input())
#print(calc_fib(n))

def calc_fib_fast(n):
    array = [];
    i = 0
    array.append(0)
    array.append(1)
    
    for i in range(2,n+1):
        array.append(array[i-1] + array[i-2]);
        
    return array[n];

print(calc_fib_fast(n))