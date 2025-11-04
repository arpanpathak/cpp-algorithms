//
// Created by Arpan Pathak on 01/11/25.
//
#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

// The lock-free shared resource
// std::atomic<T> guarantees that all operations on this object
// (read, write, increment, decrement) are performed atomically.
std::atomic<int> counter{0};
int thread_unsafe_counter = 0;

// --- Thread function ---
void incrementer_thread(int increments) {
    for (int i = 0; i < increments; ++i) {
        // This operation is lock-free and thread-safe.
        // It performs a thread-safe read-modify-write cycle.
        counter.fetch_add(1);
        ++thread_unsafe_counter;
        // Note: The ++ prefix/postfix operators on std::atomic are also lock-free
        // but fetch_add(1) is often clearer about the operation.
    }
}

// --- Main execution ---
int main() {
    cout << "Starting Lock-Free Counter simulation..." << endl;

    int num_threads = 4;
    int increments_per_thread = 250000;
    int total_expected = num_threads * increments_per_thread;

    vector<thread> threads;

    // Create and start multiple threads
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(incrementer_thread, increments_per_thread);
    }

    // Wait for all threads to finish
    for (auto& t : threads) {
        t.join();
    }

    cout << "\n--- Results ---" << endl;
    cout << "Expected count: " << total_expected << endl;
    cout << "Actual count:   " << counter.load() << endl; // Use load() for a guaranteed atomic read
    cout << "Thread unsafe counting result: " << thread_unsafe_counter << endl;

    if (counter.load() == total_expected) {
        cout << "Result: Success! The lock-free counter is correct." << endl;
    } else {
        cout << "Result: Failure! (Should not happen with std::atomic)" << endl;
    }

    return 0;
}