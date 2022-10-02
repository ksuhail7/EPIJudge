#include "list_node.h"
#include "test_framework/generic_test.h"
shared_ptr<ListNode<int>> MergeTwoSortedLists(shared_ptr<ListNode<int>> L1,
                                              shared_ptr<ListNode<int>> L2) {
  // TODO - you fill in here.
	// L1: 2 > 5 > 7
	// L2: 3 > 11

	// L_merged: 2 > 3 > 5 > 7 > 11 > null


	shared_ptr<ListNode<int>> newHead = nullptr, it = nullptr;

    while(L1 != nullptr && L2 != nullptr)
    {
	    if(L1->data >= L2->data)
	    {
		    if(newHead == nullptr)
		    {
				newHead = L2;
		    } else
		    {
				it->next = L2;
		    }
			it = L2;
			L2 = L2->next;
			it->next = nullptr;
	    } else
	    {
		    if(newHead == nullptr)
		    {
				newHead = L1;
		    } else
		    {
				it->next = L1;
		    }
			it = L1;
			L1 = L1->next;
			it->next = nullptr;
	    }
    }

	if(L1 != nullptr)
	{
		if (newHead != nullptr)
			it->next = L1;
		else
			newHead = L1;
	}
	if(L2 != nullptr)
	{
		if (newHead != nullptr)
			it->next = L2;
		else
			newHead = L2;
	}
	return newHead;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"L1", "L2"};
  return GenericTestMain(args, "sorted_lists_merge.cc",
                         "sorted_lists_merge.tsv", &MergeTwoSortedLists,
                         DefaultComparator{}, param_names);
}
