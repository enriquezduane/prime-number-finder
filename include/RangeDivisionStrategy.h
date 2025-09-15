#pragma once

#include "ITaskDivisionStrategy.h"
#include <mutex>

class RangeDivisionStrategy : public ITaskDivisionStrategy {
private:
    static std::mutex consoleMutex;

public:
    std::vector<int> findPrimes(int upperLimit, int numThreads,
                                std::shared_ptr<IPrintStrategy> printStrategy) override;
};
