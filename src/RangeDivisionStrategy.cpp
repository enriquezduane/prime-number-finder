#include "RangeDivisionStrategy.h"
#include "ColorUtils.h"
#include "IPrintStrategy.h"
#include "PrimeUtils.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

// Define static mutex for console output protection.
std::mutex RangeDivisionStrategy::consoleMutex;

// Find primes using range division strategy.
std::vector<int> RangeDivisionStrategy::findPrimes(int upperLimit, int numThreads,
                                                   std::shared_ptr<IPrintStrategy> printStrategy) {
    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << ColorUtils::highlight("[RANGE DIVISION]") << " Finding primes up to "
                  << ColorUtils::bold(std::to_string(upperLimit)) << " using "
                  << ColorUtils::bold(std::to_string(numThreads)) << " threads" << std::endl;
    }

    std::vector<int> allPrimes;
    std::vector<std::thread> threads;
    std::mutex primesMutex;

    // Calculate range per thread.
    int rangePerThread = upperLimit / numThreads;
    int remainder = upperLimit % numThreads;

    for (int i = 0; i < numThreads; ++i) {
        int start = i * rangePerThread + 1;
        int end = (i + 1) * rangePerThread;
        if (i == numThreads - 1) {
            end += remainder; // Last thread handles remainder.
        }

        threads.emplace_back([start, end, printStrategy, &allPrimes, &primesMutex]() {
            {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << ColorUtils::thread(
                                 "[THREAD " +
                                 std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) %
                                                10000) +
                                 "]")
                          << " Processing range "
                          << ColorUtils::warning(std::to_string(start) + "-" + std::to_string(end))
                          << std::endl;
            }

            // Find all primes in this thread's range.
            std::vector<int> threadPrimes = PrimeUtils::findPrimesInRange(start, end);

            // Report each prime found.
            for (int prime : threadPrimes) {
                auto timestamp = std::chrono::system_clock::now();
                printStrategy->printPrime(prime, std::this_thread::get_id(), timestamp);

                // Add to global collection.
                std::lock_guard<std::mutex> lock(primesMutex);
                allPrimes.push_back(prime);
            }

            {
                std::lock_guard<std::mutex> lock(consoleMutex);
                std::cout << ColorUtils::thread(
                                 "[THREAD " +
                                 std::to_string(std::hash<std::thread::id>{}(std::this_thread::get_id()) %
                                                10000) +
                                 "]")
                          << " Found " << ColorUtils::success(std::to_string(threadPrimes.size()))
                          << " primes in range "
                          << ColorUtils::warning(std::to_string(start) + "-" + std::to_string(end))
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
