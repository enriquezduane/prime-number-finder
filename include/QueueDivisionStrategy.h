#pragma once

#include "ITaskDivisionStrategy.h"

class QueueDivisionStrategy : public ITaskDivisionStrategy {
public:
    std::vector<int> findPrimes(int upperLimit, int numThreads, 
                               std::shared_ptr<IPrintStrategy> printStrategy) override;
};
