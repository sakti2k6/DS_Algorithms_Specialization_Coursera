#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using std::map;
using std::vector;
using std::string;
using std::ifstream;


typedef map<char, int> edges;
typedef vector<edges> trie_test;

struct node {
    char c{};
    int val{};
    vector<node*> edges;
};

class trie {
    public:
    node root;
    int count;

    trie() {
        root.c = '\0';
        root.val = 0;
        count = 0;
    }

    node* search (const string& s, node* snode,int& i) {
        node* current = snode;

        while (i < s.size()) {
            node* newnode = search_c(s[i],current);
            if (newnode == nullptr) {
                return current;
            } 
            current = newnode;
            ++i;
        }

        return current;
    }

    node* search_c (char ch, node* start) {
        for (int i = 0; i < start->edges.size(); ++i) {
            if (start->edges[i]->c == ch) {
                return start->edges[i]; 
            }
        }
        return nullptr;
    }

    void insert(string& s) {
        int pos = 0;
        node* fnode = search(s, &root, pos);
        if (pos == s.size()) {
            std::cout << "Error: String is prefix" << std::endl;
            return;
        } 
        while (pos < s.size()) {
            node* newnode = new node();
            count += 1;
            int old = fnode->val; 
            newnode->c = s[pos];
            newnode->val = count ;
            fnode->edges.push_back(newnode);
            fnode = newnode;
            pos += 1;
            //std::cout << "fnode->val: " << fnode->val << " count: " << count << " newnode->c: " << newnode->c << " new_node->val: " << newnode->val << "\n";
            //std::cout << old << "->" << newnode->val << ":" << newnode->c << "\n";
        }
    }

    void print(node* root) {
        if (root->edges.size() == 0) {
            return;
        }

        for (int i = 0; i < root->edges.size(); ++i) {
            node* curr = root->edges[i];
            std::cout << root->val << "->" << curr->val << ":" << curr->c << "\n";
            print(curr);
        }
    }
};


trie_test build_trie(vector<string> & patterns) {
    trie_test t;
    return t;
}

int main() {
  size_t n;
  //std::cin >> n;
  ifstream test1 ("sample2");
  test1 >> n;
    
  trie mytrie;
  for (int i = 0; i < n; ++i) {
    string s;
    //std::cin >> s;
    test1 >> s;
    mytrie.insert(s);
  }
  
  mytrie.print(&mytrie.root);

/*
  vector<string> patterns;
  for (size_t i = 0; i < n; i++) {
    string s;
    //std::cin >> s;
    test1 >> s;
    patterns.push_back(s);
  }

  trie_test t = build_trie(patterns);
  for (size_t i = 0; i < t.size(); ++i) {
    for (const auto & j : t[i]) {
      std::cout << i << "->" << j.second << ":" << j.first << "\n";
    }
  }
*/

  int* ptr = new int(5);
  return 0;
}
