#include <iostream>
#include <memory>

template <typename DataType>
struct ListNode {
    DataType data;
    std::unique_ptr<ListNode> next;
};

template <typename DataType>
class LinkedList {
private:
    std::unique_ptr<ListNode<DataType>> head;
    ListNode<DataType>* tail = nullptr;
    size_t size = 0;

public:
    // Basic operations to make the list usable
    void append(const DataType& data) {
        auto newNode = std::make_unique<ListNode<DataType>>();
        newNode->data = data;

        if (!head) {
            head = std::move(newNode);
            tail = head.get();
        } else {
            tail->next = std::move(newNode);
            tail = tail->next.get();
        }
        size++;
    }

    friend std::ostream& operator<<(std::ostream& os, const LinkedList<DataType>& list) {
        ListNode<DataType>* current = list.head.get();
        while (current) {
            os << current->data;
            if (current->next) {
                os << " -> ";
            }
            current = current->next.get();
        }
        return os;
    }

    // The two-pointer solution for removing the nth node from the end
    // Time: O(n), Space: O(1)
    void removeNthFromLast(int n) {
        if (!head || n <= 0) {
            return;
        }

        // Use a dummy node to handle the edge case of removing the head
        auto dummy = std::make_unique<ListNode<DataType>>();
        dummy->next = std::move(head);

        ListNode<DataType>* slow = dummy.get();
        ListNode<DataType>* fast = dummy.get();

        // Move fast pointer n+1 steps ahead to create the gap
        for (int i = 0; i < n; ++i) {
            if (!fast->next) { // n is greater than the list size
                head = std::move(dummy->next);
                return;
            }
            fast = fast->next.get();
        }

        // Move both pointers until fast reaches the end
        while (fast->next) {
            fast = fast->next.get();
            slow = slow->next.get();
        }

        // The 'slow' pointer is now at the node just before the one to be removed
        std::unique_ptr<ListNode<DataType>> temp = std::move(slow->next);
        slow->next = std::move(temp->next);

        // Update head to reflect changes
        head = std::move(dummy->next);
        size--;
    }
};

int main() {
    LinkedList<int> list;
    list.append(1);
    list.append(2);
    list.append(3);
    list.append(4);
    list.append(5);
    std::cout << "Original list: " << list << std::endl;

    list.removeNthFromLast(2);
    std::cout << "After removing 2nd from last: " << list << std::endl;

    list.removeNthFromLast(1);
    std::cout << "After removing 1st from last: " << list << std::endl;

    list.removeNthFromLast(2);
    std::cout << "After removing 2nd from last: " << list << std::endl;

    list.removeNthFromLast(2);
    std::cout << "After removing 2nd from last: " << list << std::endl;

    return 0;
}