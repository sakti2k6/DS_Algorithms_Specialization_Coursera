#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using std::string;
typedef signed long long ull;
using namespace std;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

int num(const char& c) {
    int r = (c -'0') % 101;
    //cout << c << " " << r << endl;
    return r;
}

bool IsEqual(const string& a, const string& b,int k) {
    for (size_t i=0; i < a.size(); ++i) {
        if (a[i] != b[i+k]) return false;
    }
    return true;
}

ull power(int base, int exp) {
    if (exp == 0) 
        return 1;
    if (exp % 2 == 0) {
        return (ull)power(base,exp/2) * (ull)power(base,exp/2);
    } else {
        return base * (ull)power(base,exp/2) * (ull)power(base, exp/2);
    }
}


std::vector<int> rabin_karp_algo(const Data& input) {
    const string& s = input.pattern, t = input.text;
    int m = s.size();
    int n = t.size();
    int base = 128;
    std::vector<int> ans;
    //Find possible number of keys
    int keys = t.size() - s.size();
    //Get the next bigger prime as the modulus for generating hash
    int p = ((keys/6) + 1) * 6 + 1;
    p = 101;
    //precompute h = power(base,m-1) % p
    int h = 1;
    for (int i = 0; i < m-1 ; ++i) 
        h = (h * base) % p;
  //  cout << "h:"<< h << endl;
    //precompute hash of input pattern
    int hs = 0;
    int ht = 0;
    for (size_t i = 0; i < s.size(); ++i) {
       hs = (hs * base + s[i] ) % p;
       ht = (ht * base + t[i] ) % p;
    }

//  cout << "hs:" << hs << " ht:" << ht << endl;
    for (size_t i = 0; i <= n - m; ++i) {
        if (hs == ht) {
            if (IsEqual (s,t,i)) 
                ans.push_back(i);
        } 
        if (i < n - m) {
            ht = ((ht - h*t[i]) * base + t[i+m]) % p ; 
            if (ht < 0) 
                ht += p;
//            cout << "hs:" << hs << " ht:" << ht << endl;
        } 
    }
    return ans;
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    for (size_t i = 0; i + s.size() <= t.size(); ++i)
        if (t.substr(i, s.size()) == s)
            ans.push_back(i);
    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    Data d;
    d.pattern = "ab";
    d.text = "babdabf";
    //print_occurrences(get_occurrences(d));
    print_occurrences(rabin_karp_algo(read_input()));
    return 0;
}
