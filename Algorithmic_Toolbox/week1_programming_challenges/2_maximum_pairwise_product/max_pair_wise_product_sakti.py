#python3
# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

def MaxPairWiseProduct(mylist) :
    max1 = 0;
    max2 = 0;
    for i in range(len(mylist)):
        if (mylist[i] > max1):
            max2 = max1
            max1 = mylist[i]
        elif (mylist[i] > max2):
            max2 = mylist[i]
    
    return max1*max2

if __name__ == '__main__':
    input_n = int(input())
    input_numbers = [int(x) for x in input().split()]    
    print(MaxPairWiseProduct(input_numbers))