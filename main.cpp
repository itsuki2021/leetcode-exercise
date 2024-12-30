#include <iostream>

#include "list.h"
#include "utils.hpp"

using namespace std;

using my_list::initList;
using my_list::ListNode;
using my_list::printList;

class Solution {
  public:
    ListNode *removeElements(ListNode *head, int val) {
        if (head == nullptr) {
            return head;
        }

        ListNode *pre = nullptr;
        ListNode *cur = head;

        while (cur != nullptr) {
            if (cur->val == val) {
                if (pre == nullptr) {
                    head = cur->next;
                    cur = head;
                } else {
                    pre->next = cur->next;
                    cur = cur->next;
                }
            } else {
                pre = cur;
                cur = cur->next;
            }
        }

        return head;
    }
};

int main() {
    ListNode *head = initList({6, 3, 4, 5, 6});
    int val = 6;

    auto sol = new Solution();
    auto ans = sol->removeElements(head, val);

    cout << "\nAnswer is:\n";
    printList(ans);
    // cout << ans << endl;
    // utils::printVec1D(ans);
    // utils::printVec2D(ans);

    delete sol;

    return 0;
}
