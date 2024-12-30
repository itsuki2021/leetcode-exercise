#include "list.h"

namespace my_list {

ListNode *initList(const std::vector<int> &values) {
    if (values.empty()) {
        return nullptr;
    }

    ListNode *head = new ListNode(values[0]);
    ListNode *current = head;

    for (std::size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }

    return head;
}

void printList(ListNode *head) {
    if (head == nullptr) {
        std::cout << "Empty list" << std::endl;
        return;
    }

    ListNode *current = head;
    while (current != nullptr) {
        std::cout << current->val;
        if (current->next != nullptr) {
            std::cout << " -> ";
        }
        current = current->next;
    }
    std::cout << std::endl;
}

} // namespace my_list
