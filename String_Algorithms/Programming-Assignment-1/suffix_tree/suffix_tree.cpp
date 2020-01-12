#include <iostream>
#include <map>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::unordered_map;

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
  vector<string> result;
  return result;
}

struct Node {
    int index;
    int start{};
    int end{};
    Node* edge1;
    Node* edge2;
    Node() {
        index = -1;
        edge1 = nullptr;
        edge2 = nullptr;
    }
};

class trie {
    public:
    
    Node root;
    trie() {};

    void insert(const string& text) {
        int n = text.size() - 1;
        for (int i = 0 ; i < text.size(); ++i) {

            int j = 0;
            int k = i;
            Node* curr = &root;
            if (curr->edge1 != nullptr && text[j] == text[k]) {
                while (text[j] == text[k]) {
                    ++j;
                    ++k;
                }

                Node* prev = curr->edge1;
                prev.start = j;
                Node* newnode = new Node();
                newnode->start = j
            } 

            Node* newnode = new Node();
            newnode->start = k;
            newnode->end = n;
            newnode->index = i;
            curr->edge1 = newnode;
        }
    }

    void build(const vector<string>& patterns) {
        for (int i = 0; i < patterns.size(); ++i) {
            insert(patterns[i]);
        }
    }

    int search(const string& text, int index) {
        Node* curr = &root;
        int i = index;
        while (curr->index != 0) {
            if (curr->edge.count(text[i])) {
                curr = curr->edge[text[i]];
                ++i;
            } else {
                return -1;
            }
        }
        return index;
    }

    vector <int> solve (const string& text, const vector<string>& patterns)
    {
        build(patterns);
	    vector <int> result;
        for (int i = 0; i < text.size(); ++i) {
            int temp = search(text, i);
            if (temp != -1) 
                result.push_back(temp);
        }
    	return result;
    }
};


int main() {
  string text;
  cin >> text;
  vector<string> edges = ComputeSuffixTreeEdges(text);
  for (int i = 0; i < edges.size(); ++i) {
    cout << edges[i] << endl;
  }
  return 0;
}
