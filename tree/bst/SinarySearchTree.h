//
// Created by Arpan Pathak on 27/08/25.
//

#include <memory>
#include <vector>
#include <utility>
#include <queue>
#include <algorithm>
#include <iostream>
#include <stdexcept>

/**
 * @brief A templated Binary Search Tree implementation using unique_ptr for memory management.
 *
 * @tparam T The type of elements stored in the tree. Must support comparison operators.
 */
template <typename T>
class BinarySearchTree {
    struct TreeNode {
        T value;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;

        explicit TreeNode(T val) : value(std::move(val)), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<TreeNode> root;
    size_t size_{0};

public:
    BinarySearchTree() = default;

    /**
     * @brief Inserts a value into the BST.
     * @param value The value to insert.
     */
    void insert(T value) {
        root = insert(std::move(root), std::move(value));
        size_++;
    }

    void insertAll(const std::vector<T> &allValues) {
        for (auto& val: allValues) {
            insert(val);
        }
    }

    /**
     * @brief Removes a value from the BST.
     * @param value The value to remove.
     * @return true if the value was found and removed, false otherwise.
     */
    bool remove(const T& value) {
        if (!contains(value)) return false;
        root = remove(std::move(root), value);
        size_--;
        return true;
    }

    /**
     * @brief Checks if a value exists in the BST.
     * @param value The value to search for.
     * @return true if the value exists, false otherwise.
     */
    bool contains(const T& value) const {
        return search(root.get(), value);
    }

    /**
     * @brief Returns the smallest value greater than or equal to the given value.
     * @param value The reference value.
     * @return The ceiling value.
     * @throws std::runtime_error if no ceiling exists.
     */
    T ceiling(const T& value) const {
        auto result = ceiling(root.get(), value);
        if (!result) throw std::runtime_error("No ceiling exists for given value");

        return result->value;
    }

    /**
     * @brief Returns the largest value less than or equal to the given value.
     * @param value The reference value.
     * @return The floor value.
     * @throws std::runtime_error if no floor exists.
     */
    T floor(const T& value) const {
        auto result = floor(root.get(), value);
        if (!result) throw std::runtime_error("No floor exists for given value");
        return result->value;
    }

    /**
     * @brief Returns the minimum value in the BST.
     * @return The minimum value.
     * @throws std::runtime_error if the tree is empty.
     */
    T min() const {
        if (!root) throw std::runtime_error("Tree is empty");
        return minNode(root.get())->value;
    }

    /**
     * @brief Returns the maximum value in the BST.
     * @return The maximum value.
     * @throws std::runtime_error if the tree is empty.
     */
    T max() const {
        if (!root) throw std::runtime_error("Tree is empty");
        return maxNode(root.get())->value;
    }

    /**
     * @brief Returns the number of elements in the BST.
     * @return The size of the tree.
     */
    size_t size() const { return size_; }

    /**
     * @brief Checks if the BST is empty.
     * @return true if empty, false otherwise.
     */
    bool empty() const { return size_ == 0; }

    /**
     * @brief Returns elements in sorted order (in-order traversal).
     * @return Vector of elements in ascending order.
     */
    std::vector<T> inorder() const {
        std::vector<T> result;
        result.reserve(size_);
        inorder(root.get(), result);
        return result;
    }

    /**
     * @brief Returns elements in pre-order traversal.
     * @return Vector of elements in pre-order.
     */
    std::vector<T> preorder() const {
        std::vector<T> result;
        result.reserve(size_);
        preorder(root.get(), result);
        return result;
    }

    /**
     * @brief Returns elements in post-order traversal.
     * @return Vector of elements in post-order.
     */
    std::vector<T> postorder() const {
        std::vector<T> result;
        result.reserve(size_);
        postorder(root.get(), result);
        return result;
    }

    /**
     * @brief Returns elements in level-order (breadth-first) traversal.
     * @return Vector of elements in level-order.
     */
    std::vector<T> levelorder() const {
        std::vector<T> result;
        if (!root) return result;

        std::queue<const TreeNode*> q;
        q.push(root.get());

        while (!q.empty()) {
            const TreeNode* current = q.front();
            q.pop();
            result.push_back(current->value);

            if (current->left) q.push(current->left.get());
            if (current->right) q.push(current->right.get());
        }

        return result;
    }

    /**
     * @brief Returns the height of the tree.
     * @return The height (number of edges from root to deepest leaf).
     */
    size_t height() const {
        return height(root.get());
    }

    /**
     * @brief Checks if the BST is valid (maintains BST properties).
     * @return true if valid, false otherwise.
     */
    bool isValid() const {
        return isValid(root.get(), nullptr, nullptr);
    }

    /**
     * @brief Returns the k-th smallest element (0-indexed).
     * @param k The index (0 = smallest, 1 = second smallest, etc.)
     * @return The k-th smallest element.
     * @throws std::out_of_range if k is out of bounds.
     */
    T kthSmallest(size_t k) const {
        if (k >= size_) throw std::out_of_range("k is out of bounds");
        return kthSmallest(root.get(), k)->value;
    }

    /**
     * @brief Returns the k-th largest element (0-indexed).
     * @param k The index (0 = largest, 1 = second largest, etc.)
     * @return The k-th largest element.
     * @throws std::out_of_range if k is out of bounds.
     */
    T kthLargest(size_t k) const {
        if (k >= size_) throw std::out_of_range("k is out of bounds");
        return kthLargest(root.get(), k)->value;
    }

private:
    // Recursive helper methods

    std::unique_ptr<TreeNode> insert(std::unique_ptr<TreeNode> node, T value) {
        if (!node) {
            return std::make_unique<TreeNode>(std::move(value));
        }

        if (value < node->value) {
            node->left = insert(std::move(node->left), std::move(value));
        } else {
            node->right = insert(std::move(node->right), std::move(value));
        }

        return node;
    }

    std::unique_ptr<TreeNode> remove(std::unique_ptr<TreeNode> node, const T& value) {
        if (!node) return nullptr;

        if (value < node->value) {
            node->left = remove(std::move(node->left), value);
        } else if (value > node->value) {
            node->right = remove(std::move(node->right), value);
        } else {
            // Node found, handle three cases:
            if (!node->left) {
                return std::move(node->right);
            } else if (!node->right) {
                return std::move(node->left);
            } else {
                // Node has two children: replace with inorder successor
                TreeNode* minRight = minNode(node->right.get());
                node->value = minRight->value;
                node->right = remove(std::move(node->right), minRight->value);
            }
        }

        return node;
    }

    bool search(const TreeNode* node, const T& value) const {
        if (!node) return false;
        if (value == node->value) return true;

        return value < node->value ? search(node->left.get(), value)
                                   : search(node->right.get(), value);
    }

    const TreeNode* ceiling(const TreeNode* node, const T& value) const {
        if (!node) return nullptr;

        if (value == node->value) {
            return node;
        } else if (value > node->value) {
            return ceiling(node->right.get(), value);
        } else {
            auto leftCeil = ceiling(node->left.get(), value);
            return leftCeil ? leftCeil : node;
        }
    }

    const TreeNode* floor(const TreeNode* node, const T& value) const {
        if (!node) return nullptr;

        if (value == node->value) {
            return node;
        } else if (value < node->value) {
            return floor(node->left.get(), value);
        } else {
            auto rightFloor = floor(node->right.get(), value);
            return rightFloor ? rightFloor : node;
        }
    }

    TreeNode* minNode(TreeNode* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    TreeNode* maxNode(TreeNode* node) const {
        while (node && node->right) {
            node = node->right.get();
        }
        return node;
    }

    const TreeNode* minNode(const TreeNode* node) const {
        while (node && node->left) {
            node = node->left.get();
        }
        return node;
    }

    const TreeNode* maxNode(const TreeNode* node) const {
        while (node && node->right) {
            node = node->right.get();
        }
        return node;
    }

    void inorder(const TreeNode* node, std::vector<T>& result) const {
        if (!node) return;
        inorder(node->left.get(), result);
        result.push_back(node->value);
        inorder(node->right.get(), result);
    }

    void preorder(const TreeNode* node, std::vector<T>& result) const {
        if (!node) return;
        result.push_back(node->value);
        preorder(node->left.get(), result);
        preorder(node->right.get(), result);
    }

    void postorder(const TreeNode* node, std::vector<T>& result) const {
        if (!node) return;
        postorder(node->left.get(), result);
        postorder(node->right.get(), result);
        result.push_back(node->value);
    }

    size_t height(const TreeNode* node) const {
        if (!node) return 0;
        return 1 + std::max(height(node->left.get()), height(node->right.get()));
    }

    bool isValid(const TreeNode* node, const TreeNode* min, const TreeNode* max) const {
        if (!node) return true;

        if ((min && node->value <= min->value) || (max && node->value >= max->value)) {
            return false;
        }

        return isValid(node->left.get(), min, node) &&
               isValid(node->right.get(), node, max);
    }

    const TreeNode* kthSmallest(const TreeNode* node, size_t& k) const {
        if (!node) return nullptr;

        const TreeNode* left = kthSmallest(node->left.get(), k);
        if (left) return left;

        if (k-- == 0) return node;

        return kthSmallest(node->right.get(), k);
    }

    const TreeNode* kthLargest(const TreeNode* node, size_t& k) const {
        if (!node) return nullptr;

        const TreeNode* right = kthLargest(node->right, k);
        if (right) return right;

        if (k-- == 0) return node;

        return kthLargest(node->left.get(), k);
    }

};
