#include <iostream>
#include <vector>
#include <algorithm>
#include <limits> 

using namespace std;

/**
 * @brief Implements a Segment Tree supporting Range Min/Sum Queries and Range/Point Updates.
 * Uses Lazy Propagation for O(log N) range update and O(log N) query time.
 * @tparam T The type of element stored, defaults to long long for safety against overflow.
 */
template<class T = long long> class SegmentTree
{
private:
    vector<T> A;
    
    struct Node {
        T mx, mn, sum;
        Node(T m = numeric_limits<T>::min(), T n = numeric_limits<T>::max(), T s = 0) 
            : mx(m), mn(n), sum(s) {}
    };
    
    vector<Node> tree;
    vector<T> lazy; 
    int arraySize;

    /**
     * @brief Applies pending lazy tag to current node and pushes it down to children.
     * Must be called before accessing node's value or recurring to children.
     * Time Complexity: O(1)
     * @param pos Current node index in the tree array.
     * @param low Start index of the current segment in the original array.
     * @param high End index of the current segment in the original array.
     */
    void push_down(int pos, int low, int high)
    {
        if (lazy[pos] != 0) {
            T delta = lazy[pos];
            T segment_length = high - low + 1;
            
            // Apply the pending update (delta) to the current node's aggregates
            tree[pos].sum += delta * segment_length;
            tree[pos].mn += delta;
            tree[pos].mx += delta;
            
            // Pass the update to children if it's not a leaf
            if (low != high) {
                lazy[2 * pos + 1] += delta;
                lazy[2 * pos + 2] += delta;
            }
            
            lazy[pos] = 0;
        }
    }

    /**
     * @brief Recursively constructs the segment tree from the initial array.
     * Time Complexity: O(N)
     * @param low Start index of the current segment in the original array.
     * @param high End index of the current segment in the original array.
     * @param pos Current node index in the tree array.
     */
    void construct(int low, int high, int pos)
    {
        if (low == high) {
            tree[pos].mn = tree[pos].mx = tree[pos].sum = A[low];
            return;
        }

        int mid = low + (high - low) / 2;
        construct(low, mid, 2 * pos + 1);    
        construct(mid + 1, high, 2 * pos + 2);

        tree[pos].mx = std::max(tree[2 * pos + 1].mx, tree[2 * pos + 2].mx);
        tree[pos].mn = std::min(tree[2 * pos + 1].mn, tree[2 * pos + 2].mn);
        tree[pos].sum = tree[2 * pos + 1].sum + tree[2 * pos + 2].sum;
    }

    /**
     * @brief Recursively performs Range Minimum Query.
     * Time Complexity: O(log N)
     * @param qlow Query range start index.
     * @param qhigh Query range end index.
     * @param low Current segment start index.
     * @param high Current segment end index.
     * @param pos Current node index.
     * @return The minimum value in the query range.
     */
    T rangeMinQuery(int qlow, int qhigh, int low, int high, int pos)
    {
        push_down(pos, low, high);

        if (qlow <= low && qhigh >= high) 
            return tree[pos].mn;
        if (qlow > high || qhigh < low) 
            return numeric_limits<T>::max();
            
        int mid = low + (high - low) / 2;
        
        return std::min(
            rangeMinQuery(qlow, qhigh, low, mid, 2 * pos + 1),
            rangeMinQuery(qlow, qhigh, mid + 1, high, 2 * pos + 2)
        );
    }
    
    /**
     * @brief Recursively performs Range Sum Query.
     * Time Complexity: O(log N)
     * @param qlow Query range start index.
     * @param qhigh Query range end index.
     * @param low Current segment start index.
     * @param high Current segment end index.
     * @param pos Current node index.
     * @return The sum of values in the query range.
     */
    T rangeSumQuery(int qlow, int qhigh, int low, int high, int pos)
    {
        push_down(pos, low, high);

        if (qlow <= low && qhigh >= high) 
            return tree[pos].sum;
        if (qlow > high || qhigh < low) 
            return 0;
            
        int mid = low + (high - low) / 2;
        
        return rangeSumQuery(qlow, qhigh, low, mid, 2 * pos + 1) +
               rangeSumQuery(qlow, qhigh, mid + 1, high, 2 * pos + 2);
    }

    /**
     * @brief Recursively performs Range Update using Lazy Propagation.
     * Time Complexity: O(log N)
     * @param qlow Update range start index.
     * @param qhigh Update range end index.
     * @param delta Value to add to all elements in the range.
     * @param low Current segment start index.
     * @param high Current segment end index.
     * @param pos Current node index.
     */
    void rangeUpdateUtil(int qlow, int qhigh, T delta, int low, int high, int pos)
    {
        push_down(pos, low, high);

        if (qlow <= low && qhigh >= high) {
            T segment_length = high - low + 1;
            
            // Apply update to current node
            tree[pos].sum += delta * segment_length;
            tree[pos].mn += delta;
            tree[pos].mx += delta;

            // Mark children as lazy
            if (low != high) {
                lazy[2 * pos + 1] += delta;
                lazy[2 * pos + 2] += delta;
            }
            return; 
        }

        if (qlow > high || qhigh < low) {
            return;
        }

        int mid = low + (high - low) / 2;
        rangeUpdateUtil(qlow, qhigh, delta, low, mid, 2 * pos + 1);    
        rangeUpdateUtil(qlow, qhigh, delta, mid + 1, high, 2 * pos + 2); 

        // Merge children's results
        tree[pos].sum = tree[2 * pos + 1].sum + tree[2 * pos + 2].sum;
        tree[pos].mn = std::min(tree[2 * pos + 1].mn, tree[2 * pos + 2].mn);
        tree[pos].mx = std::max(tree[2 * pos + 1].mx, tree[2 * pos + 2].mx);
    }

    /**
     * @brief Recursively performs a single point update.
     * Time Complexity: O(log N)
     * @param idx Index of the element to update.
     * @param val The value to add/subtract (delta).
     * @param low Current segment start index.
     * @param high Current segment end index.
     * @param pos Current node index.
     */
    void pointUpdateUtil(int idx, T val, int low, int high, int pos)
    {
        push_down(pos, low, high);

        if (low == high)
        {
            // Leaf node: Update array and node values
            A[idx] += val;
            tree[pos].sum += val;
            tree[pos].mn = tree[pos].mx = tree[pos].sum;
            return;
        }
        
        int mid = low + (high - low) / 2;
        
        if (idx <= mid)
        {
            pointUpdateUtil(idx, val, low, mid, 2 * pos + 1);
        }
        else
        {
            pointUpdateUtil(idx, val, mid + 1, high, 2 * pos + 2);
        }
        
        // Merge children's results
        tree[pos].sum = tree[2 * pos + 1].sum + tree[2 * pos + 2].sum;
        tree[pos].mn = std::min(tree[2 * pos + 1].mn, tree[2 * pos + 2].mn);
        tree[pos].mx = std::max(tree[2 * pos + 1].mx, tree[2 * pos + 2].mx);
    }


public:
    /**
     * @brief Constructor for the SegmentTree. Calculates space based on the next power of 2.
     * @param AR Reference to the initial data vector.
     */
    SegmentTree(vector<T> &AR)
    {
        A = AR;
        arraySize = A.size();
        
        // Space-Optimized Sizing Logic
        int N = arraySize;
        int size_needed = 1;

        if ((N & (N - 1)) == 0) { // If N is a power of 2
            size_needed = 2 * N - 1;
        } else {
            // Find the smallest power of 2 >= N
            int power_of_2 = 1;
            while (power_of_2 < N) {
                power_of_2 <<= 1;
            }
            size_needed = 2 * power_of_2 - 1;
        }

        tree.resize(size_needed, Node()); 
        lazy.resize(size_needed, 0); 
        
        construct(0, arraySize - 1, 0);
    }

    /**
     * @brief Public method for Range Sum Query.
     * Time Complexity: O(log N)
     * @param qlow Query range start index.
     * @param qhigh Query range end index.
     * @return Sum of elements in the range [qlow, qhigh].
     */
    T rangeSum(int qlow, int qhigh)
    {
        return rangeSumQuery(qlow, qhigh, 0, arraySize - 1, 0);
    }
    
    /**
     * @brief Public method for Range Min Query.
     * Time Complexity: O(log N)
     * @param qlow Query range start index.
     * @param qhigh Query range end index.
     * @return Minimum element in the range [qlow, qhigh].
     */
    T rangeMin(int qlow, int qhigh)
    {
        return rangeMinQuery(qlow, qhigh, 0, arraySize - 1, 0);
    }
    
    /**
     * @brief Public method for Range Update (adds delta to all elements in the range).
     * Time Complexity: O(log N)
     * @param qlow Update range start index.
     * @param qhigh Update range end index.
     * @param delta Value to add to all elements.
     */
    void rangeUpdate(int qlow, int qhigh, T delta)
    {
        rangeUpdateUtil(qlow, qhigh, delta, 0, arraySize - 1, 0);
    }

    /**
     * @brief Public method to update a single point in the array.
     * Time Complexity: O(log N)
     * @param idx Index of the element to update (0-based).
     * @param delta The value to add/subtract.
     */
    void pointUpdate(int idx, T delta)
    {
        pointUpdateUtil(idx, delta, 0, arraySize - 1, 0);
    }
};
