#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int n;
    vector<int> key;
    vector<int> left;
    vector<int> right;
    ;

    /*Node() : key(0), left(-1), right(-1) {}
    Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}*/

    void read_data() {
        cin >> n;
        key.resize(n);
        left.resize(n);
        right.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> key[i] >> left[i] >> right[i];
        }
    }

    vector<int> in_order(int i, vector<int>& result) {
          //if left child of node is nill -> print out left child
          if (left[i] != -1 && left[left[i]] == -1 && right[left[i]] == -1) {
              result.push_back(key[left[i]]);
          }
          else if (left[i] != -1) {
              in_order(left[i], result);
          }
          //Print out node after traversing all left subtree
          result.push_back(key[i]);
          //if right child of node is nill -> print out right child
          if (right[i] != -1 && left[right[i]] == -1 && right[right[i]] == -1) {
              result.push_back(key[right[i]]);
          }
          else if (right[i] != -1) {
              in_order(right[i], result);
          }
          return result;
    }

  
};

bool IsBinarySearchTree(Node& tree) {
    vector<int> keys(tree.n);
    vector<int> traverse;
    // Implement correct algorithm here
    if (tree.n == 0) {
        return true;
    }
    else {
        traverse = tree.in_order(0, traverse);
        for (int i = 0; i < traverse.size(); i++) {
            cout << traverse[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < tree.n; i++) {
            keys[i] = tree.key[i];
        }
        sort(keys.begin(), keys.end());
    }
    return keys == traverse;
}



int main() {
    Node tree;
    tree.read_data();
    if (IsBinarySearchTree(tree)) {
        cout << "CORRECT" << endl;
    } 
    else {
        cout << "INCORRECT" << endl;
    }
    return 0;
}
