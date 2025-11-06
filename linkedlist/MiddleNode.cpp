//
// Created by Arpan Pathak on 06/11/25.
//
struct ListNode {
    int data;
    ListNode* next;
};

ListNode* middleNode(ListNode* head) {
    ListNode *slow = head, *fast = head;

    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}
