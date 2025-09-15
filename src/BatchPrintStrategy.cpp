#include "BatchPrintStrategy.h"
#include "ColorUtils.h"
#include <algorithm>

// Collect prime for batch printing.
void BatchPrintStrategy::printPrime(int prime, std::thread::id /* threadId */,
                                    std::chrono::system_clock::time_point /* timestamp */) {
    std::lock_guard<std::mutex> lock(collectionMutex);
    collectedPrimes.push_back(prime);
    // In batch mode, collect primes instead of printing immediately.
}

// Print all primes at once in sorted order.
void BatchPrintStrategy::finalize(const std::vector<int> &allPrimes) {
    std::cout << ColorUtils::info("[BATCH]") << " All threads completed. Found primes:" << std::endl;

    // Sort the primes for consistent output.
    std::vector<int> sortedPrimes = allPrimes;
    std::sort(sortedPrimes.begin(), sortedPrimes.end());

    for (size_t i = 0; i < sortedPrimes.size(); ++i) {
        std::cout << ColorUtils::prime(std::to_string(sortedPrimes[i]));
        if (i < sortedPrimes.size() - 1) {
            std::cout << ", ";
        }
        if ((i + 1) % 10 == 0) {
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
    std::cout << ColorUtils::success("[BATCH] Total primes found: " + std::to_string(sortedPrimes.size()))
              << std::endl;
}
