#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using std::vector;
using std::unordered_map;
using std::string;
using std::cin;
using std::cout;
using std::endl;

int const Letters =    4;
int const NA      =   -1;

struct Node {
    int index;
    unordered_map<char,Node*> edge;
    Node() {
        index = -1;
    }
};

class trie {
    public:
    
    Node root;
    trie() {};

    void insert(const string& s) {
            int j = 0;
            Node* curr = &root;
            while (curr->edge.count(s[j]) != 0) {
                curr = curr->edge[s[j]] ;
                ++j;
            }

            while (j < s.size()) {
                Node* newnode = new Node();
                curr->edge[s[j]] = newnode;
                curr = newnode;
                ++j;
            }

            curr->index = 0;
    }

    void build(const vector<string>& patterns) {
        for (int i = 0; i < patterns.size(); ++i) {
            insert(patterns[i]);
        }
    }

    int search(const string& text, int index) {
        Node* curr = &root;
        int i = index;
        while ( curr->edge.count(text[i]) ) {
                curr = curr->edge[text[i]];
                ++i;
        }
        return (curr->index == 0) ? index : -1;
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

/*
struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}
*/


int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

    trie t;
	vector <int> ans;
	ans = t.solve (text,patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
