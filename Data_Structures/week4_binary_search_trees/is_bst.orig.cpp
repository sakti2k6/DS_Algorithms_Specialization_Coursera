#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

typedef long long int lint;

struct Node {
  lint key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order_traversal (const vector<Node>& tree,vector<lint>& data, int index, bool& result) {
   // cout << "result top: " << result << " Index: " << index << endl ;
    if (result == 0 || index == -1) {
    //    cout << "RETURNING " << "result top: " << result << " Index: " << index << endl ;
        return;
    }
 //   cout << "RESULT TOP: " << result << endl ;
    int left_i = tree[index].left;
    int right_i = tree[index].right;
    in_order_traversal (tree,data,left_i,result);
    lint key = tree[index].key;
    data.push_back(key);
    if (data.size() > 1 && result == 1) {
        if (data[data.size()-1] < data[data.size()-2]) 
            result = 0;
    }
   // cout << "result left: " << result << endl ;
    in_order_traversal (tree,data,right_i,result);
    if (data.size() > 1 && result == 1) {
        if (data[data.size()-1] < data[data.size()-2]) 
            result = 0;
    }
//    cout << "result right: " << result << endl ;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  vector<lint> data;
  bool result = 1;
  if (tree.size() == 0) return true;
  in_order_traversal(tree,data,0,result);
//  for (const int& e: data) 
//      cout << e << " " ;
//  cout << endl;
//  cout << result << endl;
  return result ;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    lint key;
    int left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
/*
  int nodes = 3;
  vector<Node> tree;
  tree.push_back(Node(-887440904,1,-1));
  tree.push_back(Node(-887440905,2,-1));
  tree.push_back(Node(-1364870,-1,-1));
  tree.push_back(Node(2,1,2));
  tree.push_back(Node(1,-1,-1));
  tree.push_back(Node(3,-1,-1)); */
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
