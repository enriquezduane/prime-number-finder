#pragma once

#include <vector>
#include <chrono>
#include <thread>

class IPrintStrategy {
public:
    virtual ~IPrintStrategy() = default;
    virtual void printPrime(int prime, std::thread::id threadId, 
                           std::chrono::system_clock::time_point timestamp) = 0;
    virtual void finalize(const std::vector<int>& allPrimes) = 0;
};
