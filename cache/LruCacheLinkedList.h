#include <list>
#include <unordered_map>
#include <stdexcept>

template <typename Key, typename Value>
class LruCacheLinkedList {
private:
    // A struct to hold the cached value and the list iterator.
    // This improves readability over using std::pair.
    struct CacheEntry {
        Value value;
        typename std::list<Key>::iterator list_iterator;
    };

public:
    // Constructor to set the maximum capacity of the cache.
    explicit LruCacheLinkedList(const size_t capacity) : _capacity(capacity) {}

    /**
     * @brief Gets the value associated with a key from the cache.
     *
     * If the key is found, it moves the item's position to the most recently
     * used (MRU) position and returns the value. Throws an exception if not found.
     *
     * @param key The key to look up.
     * @return The value associated with the key.
     * @throws std::out_of_range if the key is not in the cache.
     */
    Value get(const Key& key) {
        // Find the key in the hash map.
        auto it = _cache.find(key);

        // If the key is not found, throw an exception.
        if (it == _cache.end()) {
            throw std::out_of_range("Key not found in cache.");
        }

        // Access the CacheEntry struct for the list iterator.
        // The list iterator points to the key's current position in _orders.
        typename std::list<Key>::iterator list_it = it->second.list_iterator;

        // Use std::list::splice to move the element to the front in O(1) time.
        // This makes it the most recently used item.
        _orders.splice(_orders.begin(), _orders, list_it);

        // Return the cached value from the struct.
        return it->second.value;
    }

    /**
     * @brief Inserts or updates a key-value pair in the cache.
     *
     * If the key already exists, its value is updated and it is moved to the
     * most recently used position. If the cache is at capacity and the key
     * is new, the least recently used (LRU) item is evicted.
     *
     * @param key The key to insert or update.
     * @param value The value associated with the key.
     */
    void put(const Key& key, const Value& value) {
        // Find the key in the hash map.
        auto it = _cache.find(key);

        // If the key already exists, update its value and position.
        if (it != _cache.end()) {
            // Move the existing key to the front of the list.
            _orders.splice(_orders.begin(), _orders, it->second.list_iterator);

            // Update the value in the hash map.
            it->second.value = value;
            return;
        }

        // The key is new. Check if the cache is at its capacity.
        if (_cache.size() >= _capacity) {
            // Evict the least recently used item.
            // Check for edge case of 0 capacity
            if (_orders.empty()) {
                return;
            }
            // 1. Get the key from the back of the linked list.
            Key lru_key = _orders.back();
            // 2. Erase the key from the hash map.
            _cache.erase(lru_key);
            // 3. Remove the key from the linked list.
            _orders.pop_back();
        }

        // Insert the new key at the front of the linked list (most recently used).
        _orders.emplace_front(key);

        // Insert the new key-value pair into the hash map.
        // The value is a CacheEntry struct containing the value and an iterator
        // to the key's new position in the list.
        _cache.insert({key, {value, _orders.begin()}});
    }

private:
    // A doubly-linked list to store the keys in order of usage.
    // The most recently used key is at the front, and the least recently used is at the back.
    std::list<Key> _orders;

    // A hash map to store the key-value pairs and a reference (iterator)
    // to their location in the linked list for O(1) lookup and removal.
    std::unordered_map<Key, CacheEntry> _cache;
    size_t _capacity;
};
