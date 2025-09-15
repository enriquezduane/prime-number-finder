#pragma once

#include <memory>
#include <vector>

class IPrintStrategy;

class ITaskDivisionStrategy {
public:
    virtual ~ITaskDivisionStrategy() = default;
    virtual std::vector<int> findPrimes(int upperLimit, int numThreads,
                                        std::shared_ptr<IPrintStrategy> printStrategy) = 0;
};
