#pragma once

#include "ITaskDivisionStrategy.h"

class RangeDivisionStrategy : public ITaskDivisionStrategy {
public:
    std::vector<int> findPrimes(int upperLimit, int numThreads, 
                               std::shared_ptr<IPrintStrategy> printStrategy) override;
};
