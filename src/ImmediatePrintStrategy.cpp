#include "ImmediatePrintStrategy.h"
#include "ColorUtils.h"
#include <format>
#include <sstream>

// Print prime immediately with thread info and timestamp.
void ImmediatePrintStrategy::printPrime(int prime, std::thread::id /* threadId */,
                                        std::chrono::system_clock::time_point timestamp) {
    std::lock_guard<std::mutex> lock(printMutex);

    // Convert timestamp to readable format.
    auto time_t = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::this_thread::get_id();

    std::cout << ColorUtils::info("[IMMEDIATE]") << " Thread " << ColorUtils::thread(ss.str())
              << " found prime: " << ColorUtils::prime(std::to_string(prime)) << " at "
              << ColorUtils::timestamp(
                     std::format("{:%a %b %d %H:%M:%S %Y}", std::chrono::system_clock::from_time_t(time_t)))
              << std::endl;
}

// Print final summary with total count.
void ImmediatePrintStrategy::finalize(const std::vector<int> &allPrimes) {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << ColorUtils::success("[IMMEDIATE] Total primes found: " + std::to_string(allPrimes.size()))
              << std::endl;
}
