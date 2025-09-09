#pragma once

#include "IPrintStrategy.h"
#include <mutex>
#include <iostream>
#include <iomanip>

class ImmediatePrintStrategy : public IPrintStrategy {
private:
    std::mutex printMutex;

public:
    void printPrime(int prime, std::thread::id threadId, 
                   std::chrono::system_clock::time_point timestamp) override;
    void finalize(const std::vector<int>& allPrimes) override;
};
