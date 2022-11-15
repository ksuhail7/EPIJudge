#include <memory>

#include "binary_tree_node.h"
#include "test_framework/generic_test.h"
using std::unique_ptr;

bool IsTreeBST(const unique_ptr<BinaryTreeNode<int>>& node, int minValue, int maxValue) {
    if(node == nullptr) return true;
    if(node->data > maxValue || node->data < minValue) return false;
    return IsTreeBST(node->left, minValue, node->data) && IsTreeBST(node->right, node->data, maxValue);
}
bool IsBinaryTreeBST(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  return IsTreeBST(tree, INT_MIN, INT_MAX);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_a_bst.cc", "is_tree_a_bst.tsv",
                         &IsBinaryTreeBST, DefaultComparator{}, param_names);
}
