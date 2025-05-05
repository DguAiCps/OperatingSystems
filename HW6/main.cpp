#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

#include "spinlock.h"
#include "sleep_mutex.h"

constexpr int ITER = 100000;
int counter = 0;

template<typename LockType>
void run_test(const std::string& name, LockType& lock_obj) {
    for (int n : {1, 2, 4, 8, 16}) {
        counter = 0;
        std::vector<std::thread> threads;

        auto start = std::chrono::high_resolution_clock::now();

        for (int i = 0; i < n; ++i) {
            threads.emplace_back([&lock_obj]() {
                for (int j = 0; j < ITER; ++j) {
                    lock_obj.lock();
                    ++counter;
                    lock_obj.unlock();
                }
            });
        }

        for (auto& t : threads)
            t.join();

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

        std::cout << "[" << name << "] Threads: " << n
                  << ", Time: " << duration << " ms, Counter: " << counter << std::endl;
    }
}

int main() {
    Spinlock spin;
    SleepMutex sleep;

    std::cout << "========== Spinlock ==========" << std::endl;
    run_test("Spinlock", spin);

    std::cout << "========== SleepMutex ==========" << std::endl;
    run_test("SleepMutex", sleep);

    return 0;
}

