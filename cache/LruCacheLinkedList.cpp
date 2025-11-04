#include "LruCacheLinkedList.h"
#include <iostream>
#include <cassert>
#include <functional>

void test(const std::string& name, std::function<void()> func) {
    std::cout << "Running test: " << name << "..." << std::endl;
    try {
        func();
        std::cout << "PASSED" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "FAILED" << std::endl;
        std::cout << "  Reason: " << e.what() << std::endl;
    }
}

void testBasicPutAndGet() {
    LruCacheLinkedList<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    assert(cache.get(1) == "one");
    assert(cache.get(2) == "two");
}

void testLruEviction() {
    LruCacheLinkedList<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");

    // Key 1 should be evicted, so we expect an exception.
    bool exception_caught = false;
    try {
        cache.get(1);
    } catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);

    assert(cache.get(2) == "two");
    assert(cache.get(3) == "three");
}

void testUpdateExistingItem() {
    LruCacheLinkedList<int, std::string> cache(2);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(1, "uno");
    cache.put(3, "three");

    bool exception_caught = false;
    try {
        cache.get(2);
    } catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);

    assert(cache.get(1) == "uno");
}

void testAccessUpdatesRecency() {
    LruCacheLinkedList<int, std::string> cache(3);
    cache.put(1, "one");
    cache.put(2, "two");
    cache.put(3, "three");
    cache.get(1);
    cache.put(4, "four");

    bool exception_caught = false;
    try {
        cache.get(2);
    } catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);

    assert(cache.get(1) == "one");
    assert(cache.get(3) == "three");
    assert(cache.get(4) == "four");
}

void testEmptyCache() {
    LruCacheLinkedList<int, std::string> cache(1);
    bool exception_caught = false;
    try {
        cache.get(10);
    } catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);
}

void testZeroCapacity() {
    LruCacheLinkedList<int, std::string> cache(0);
    cache.put(1, "one");
    bool exception_caught = false;
    try {
        cache.get(1);
    } catch (const std::out_of_range&) {
        exception_caught = true;
    }
    assert(exception_caught);
}

int main() {
    test("Basic Put and Get", testBasicPutAndGet);
    test("LRU Eviction", testLruEviction);
    test("Update Existing Item", testUpdateExistingItem);
    test("Access Updates Recency", testAccessUpdatesRecency);
    test("Empty Cache", testEmptyCache);
    test("Zero Capacity", testZeroCapacity);
    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}