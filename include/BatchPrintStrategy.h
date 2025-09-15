#pragma once

#include "IPrintStrategy.h"
#include <iostream>
#include <mutex>
#include <vector>

class BatchPrintStrategy : public IPrintStrategy {
private:
    std::vector<int> collectedPrimes;
    std::mutex collectionMutex;

public:
    void printPrime(int prime, std::thread::id threadId,
                    std::chrono::system_clock::time_point timestamp) override;
    void finalize(const std::vector<int> &allPrimes) override;
};
