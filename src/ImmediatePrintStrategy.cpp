#include "ImmediatePrintStrategy.h"
#include <sstream>
#include <ctime>

void ImmediatePrintStrategy::printPrime(int prime, std::thread::id /* threadId */, 
                                       std::chrono::system_clock::time_point timestamp) {
    std::lock_guard<std::mutex> lock(printMutex);
    
    // Convert timestamp to readable format
    auto time_t = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::this_thread::get_id();
    
    std::cout << "[IMMEDIATE] Thread " << ss.str() 
              << " found prime: " << prime 
              << " at " << std::ctime(&time_t);
}

void ImmediatePrintStrategy::finalize(const std::vector<int>& allPrimes) {
    std::lock_guard<std::mutex> lock(printMutex);
    std::cout << "[IMMEDIATE] Total primes found: " << allPrimes.size() << std::endl;
}
