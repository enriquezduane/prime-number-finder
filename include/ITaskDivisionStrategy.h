#pragma once

#include <vector>
#include <memory>

class IPrintStrategy;

class ITaskDivisionStrategy {
public:
    virtual ~ITaskDivisionStrategy() = default;
    virtual std::vector<int> findPrimes(int upperLimit, int numThreads, 
                                       std::shared_ptr<IPrintStrategy> printStrategy) = 0;
};
