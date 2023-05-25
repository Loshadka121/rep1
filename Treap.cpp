#include <iostream>
#include <vector>

struct Node {
  int key;
  int prior;

  Node* left = nullptr;
  Node* right = nullptr;
  Node* parent = nullptr;
};

Node* BuildTreap(std::vector<std::pair<int, int>> values, Node** del_arr) {
  Node* root = nullptr;
  Node* last_inserted = nullptr;

  for (size_t i = 0; i < values.size(); ++i) {
    std::pair<int, int> value = values[i];
    Node* new_node = new Node{value.first, value.second};
    Node* curr = last_inserted;
    while (curr != nullptr and value.second < curr->prior) {
      curr = curr->parent;
    }

    if (curr == nullptr) {
      new_node->left = root;
      if (root != nullptr) {
        root->parent = new_node;
      }
      root = new_node;
    } else {
      new_node->left = curr->right;
      if (curr->right != nullptr) {
        curr->right->parent = new_node;
      }
      curr->right = new_node;
      new_node->parent = curr;
    }
    last_inserted = new_node;
    del_arr[i] = new_node;
  }
  return root;
}

void TreapOut(Node* node) {
  if (node != nullptr) {
    TreapOut(node->left);
    std::cout << (node->parent != nullptr ? node->parent->key : 0) << " ";
    std::cout << (node->left != nullptr ? node->left->key : 0) << " ";
    std::cout << (node->right != nullptr ? node->right->key : 0) << "\n";
    TreapOut(node->right);
  }
}

void DeleteTreap(int n, Node** del_arr) {
  for (int i = 0; i < n; ++i) {
    delete del_arr[i];
  }
}

int main() {
  int n;
  std::cin >> n;
  std::vector<std::pair<int, int>> values;
  int num, prior;
  for (int i = 0; i < n; ++i) {
    std::cin >> num >> prior;
    std::pair<int, int> p = {i + 1, prior + 1};
    values.push_back(p);
  }

  Node** del_arr = new Node*[n];

  Node* root = BuildTreap(values, del_arr);

  std::cout << "YES\n";
  TreapOut(root);

  DeleteTreap(n, del_arr);
  delete[] del_arr;
  return 0;
}
