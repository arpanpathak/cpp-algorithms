#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

// --- Shared Resources (Kept Global as requested) ---
const unsigned int MAX_BUFFER_SIZE = 5;
queue<int> buffer;

struct SynchronizationContext {
    mutex mtx;
    condition_variable cond_var;
};

SynchronizationContext sync_ctx;

// --- Producer function ---
void producer(int items_to_produce) {
    for (int i = 0; i < items_to_produce; ++i) {
        // Use the wrapped mutex
        unique_lock<mutex> lock(sync_ctx.mtx);

        // 1. WAIT: Efficiently wait if the buffer is full
        sync_ctx.cond_var.wait(lock, [] {
            return buffer.size() < MAX_BUFFER_SIZE;
        });

        // 2. PRODUCE
        buffer.push(i);
        cout << "Producing item: " << i << ". Buffer size: " << buffer.size() << endl;

        // 3. SIGNAL: Notify waiting consumers
        sync_ctx.cond_var.notify_one();

        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// --- Consumer function ---
void consumer(int items_to_consume) {
    for (int i = 0; i < items_to_consume; ++i) {
        // Use the wrapped mutex
        unique_lock<mutex> lock(sync_ctx.mtx);

        // 1. WAIT: Efficiently wait if the buffer is empty
        sync_ctx.cond_var.wait(lock, [] {
            return !buffer.empty();
        });

        // 2. CONSUME
        const int item = buffer.front(); buffer.pop();
        cout << "  Consuming item: " << item << ". Buffer size: " << buffer.size() << endl;

        // 3. SIGNAL: Notify waiting producers
        sync_ctx.cond_var.notify_one();

        this_thread::sleep_for(chrono::milliseconds(500));
    }
}

// --- Main execution ---
int main() {
    cout << "Starting Producer-Consumer simulation with wrapped synchronization..." << endl;

    int total_items = 15;

    // Create and start the threads
    thread producer_thread(producer, total_items);
    thread consumer_thread(consumer, total_items);

    // Wait for both threads to finish
    producer_thread.join();
    consumer_thread.join();

    cout << "Simulation finished." << endl;
    return 0;
}
