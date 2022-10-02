#include "binary_tree_node.h"
#include "test_framework/generic_test.h"

int IsBalancedHelper(const unique_ptr<BinaryTreeNode<int>>& root)
{
	if (root == nullptr) return true;

	int h_left = IsBalancedHelper(root->left);
	int h_right = IsBalancedHelper(root->right);
	if((h_left != -1 && h_right != -1) && abs(h_left - h_right) <= 1)
	{
		return 1 + std::max(h_left, h_right);
	} else
	{
		return -1;
	}


}
bool IsBalanced(const unique_ptr<BinaryTreeNode<int>>& tree) {
  // TODO - you fill in here.
  return IsBalancedHelper(tree) != -1;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"tree"};
  return GenericTestMain(args, "is_tree_balanced.cc", "is_tree_balanced.tsv",
                         &IsBalanced, DefaultComparator{}, param_names);
}
