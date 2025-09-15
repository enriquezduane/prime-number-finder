#include "QueueDivisionStrategy.h"
#include "ColorUtils.h"
#include "IPrintStrategy.h"
#include "PrimeUtils.h"
#include <atomic>
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// Define static mutex for console output protection.
std::mutex QueueDivisionStrategy::consoleMutex;

// Find primes using queue division strategy with atomic counter.
std::vector<int> QueueDivisionStrategy::findPrimes(int upperLimit, int numThreads,
                                                   std::shared_ptr<IPrintStrategy> printStrategy) {
    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << ColorUtils::highlight("[QUEUE DIVISION]") << " Finding primes up to "
                  << ColorUtils::bold(std::to_string(upperLimit)) << " using "
                  << ColorUtils::bold(std::to_string(numThreads)) << " threads with "
                  << ColorUtils::info("atomic counter") << std::endl;
    }

    std::vector<int> allPrimes;
    std::vector<std::thread> threads;
    std::mutex primesMutex;
    std::atomic<int> counter{2}; // Start from 2 (first prime).

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter, upperLimit, printStrategy, &allPrimes, &primesMutex]() {
            {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << ColorUtils::thread(
                                 "[THREAD " +
                                 std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) %
                                                10000) +
                                 "]")
                          << " Starting " << ColorUtils::info("queue-based processing") << std::endl;
            }

            int threadPrimeCount = 0;

            while (true) {
                int current = counter.fetch_add(1);
                if (current > upperLimit)
                    break;

                // Check if current number is prime.
                if (PrimeUtils::isPrime(current)) {
                    auto timestamp = std::chrono::system_clock::now();
                    printStrategy->printPrime(current, std::this_thread::get_id(), timestamp);

                    std::lock_guard<std::mutex> lock(primesMutex);
                    allPrimes.push_back(current);
                    threadPrimeCount++;
                }
            }

            {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << ColorUtils::thread(
                                 "[THREAD " +
                                 std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) %
                                                10000) +
                                 "]")
                          << " Found " << ColorUtils::success(std::to_string(threadPrimeCount)) << " primes"
                          << std::endl;
            }
        });
    }

    // Wait for all threads to complete.
    for (auto &thread : threads) {
        thread.join();
    }

    printStrategy->finalize(allPrimes);
    return allPrimes;
}
