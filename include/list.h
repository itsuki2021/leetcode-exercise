#pragma once
#include <iostream>
#include <vector>

namespace my_list {

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode *initList(const std::vector<int> &values);

void printList(ListNode *head);

} // namespace my_list
