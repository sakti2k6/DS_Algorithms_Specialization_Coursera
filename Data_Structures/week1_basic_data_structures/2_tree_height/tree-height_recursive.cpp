#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

using std::vector;

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = nullptr;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int get_height (Node* node) {
   
    //std::cout << "Node.key:" << node->key << "\n";
    int n = node->children.size();
    if ( n == 0) 
        return 1;

    int maxHeight = 0;
    for (int i = 0; i < n; ++i) {
        int temp = get_height(node->children[i]);
        maxHeight = std::max(maxHeight,temp);
    }
    return 1 + maxHeight;
}
/*
void print_tree(Node *node) {

    int n = node->children.size();
    std::queue nodes;
    nodes.push(node);
    while(!nodes.empty()) {
        std::cout << node->key << std::endl;
        int n = node->children.size();
        for (auto e: node->children) {
            nodes.push(e);
        }
    }
}
*/
int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
/*  int maxHeight = 0;
  for (int leaf_index = 0; leaf_index < n; leaf_index++) {
    int height = 0;
    for (Node *v = &nodes[leaf_index]; v != NULL; v = v->parent)
      height++;
    maxHeight = std::max(maxHeight, height);
  } */

  Node root = *std::find_if(std::begin(nodes),std::end(nodes),[](const Node& e){ return e.parent == nullptr ; } );
 
  //std::cout << root.key << "\n";
  std::cout << get_height(&root) << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
