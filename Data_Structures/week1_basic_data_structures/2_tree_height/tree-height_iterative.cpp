#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

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


int get_height (Node* root) {
   
    int maxHeight = 0;
    int cnt = 1;
    std::queue<Node*> myq;
    myq.push(root);
    while(!myq.empty()) {
        auto cnode = myq.front();
        //std::cout << "Node.key:" << cnode->key << "\n";

        for (int i = 0; i < cnode->children.size(); ++i) 
            myq.push(cnode->children[i]);
        
        myq.pop();
        --cnt;
        if (cnt == 0) {
            ++maxHeight;
            cnt = myq.size();
        }
    }

    return maxHeight;
}

int main() {
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

  Node root = *std::find_if(std::begin(nodes),std::end(nodes),[](const Node& e){ return e.parent == nullptr ; } );
 
  //std::cout << root.key << "\n";
  std::cout << get_height(&root) << std::endl;
  return 0;
}

