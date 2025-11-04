//
// Created by Arpan Pathak on 27/08/25.
//

#include "SinarySearchTree.h"

int main() {
    BinarySearchTree<int> tree;
    tree.insertAll({20, 100 ,3, 30, 87});
    for (const auto &v : tree.inorder()) {
        std::cout << v << ",";
    }
    std::cout << std::endl;

    // std::cout << "2nd largest element = " << tree.kthLargest(2);

    return 0;
}