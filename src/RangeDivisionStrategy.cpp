#include "RangeDivisionStrategy.h"
#include "IPrintStrategy.h"
#include <thread>
#include <vector>
#include <chrono>
#include <iostream>

std::vector<int> RangeDivisionStrategy::findPrimes(int upperLimit, int numThreads, 
                                                   std::shared_ptr<IPrintStrategy> printStrategy) {
    std::cout << "[RANGE DIVISION] Hello World! Simulating range division with " 
              << numThreads << " threads for range 1-" << upperLimit << std::endl;
    
    std::vector<int> allPrimes;
    std::vector<std::thread> threads;
    std::mutex primesMutex;
    
    // Calculate range per thread
    int rangePerThread = upperLimit / numThreads;
    int remainder = upperLimit % numThreads;
    
    for (int i = 0; i < numThreads; ++i) {
        int start = i * rangePerThread + 1;
        int end = (i + 1) * rangePerThread;
        if (i == numThreads - 1) {
            end += remainder; // Last thread handles remainder
        }
        
        threads.emplace_back([start, end, printStrategy, &allPrimes, &primesMutex]() {
            std::cout << "[THREAD " << std::this_thread::get_id() 
                      << "] Processing range " << start << "-" << end << std::endl;
            
            // Simulate finding a few "primes" (just for hello world demo)
            std::vector<int> threadPrimes;
            if (start <= 2 && end >= 2) threadPrimes.push_back(2);
            if (start <= 3 && end >= 3) threadPrimes.push_back(3);
            if (start <= 5 && end >= 5) threadPrimes.push_back(5);
            if (start <= 7 && end >= 7) threadPrimes.push_back(7);
            
            for (int prime : threadPrimes) {
                auto timestamp = std::chrono::system_clock::now();
                printStrategy->printPrime(prime, std::this_thread::get_id(), timestamp);
                
                std::lock_guard<std::mutex> lock(primesMutex);
                allPrimes.push_back(prime);
            }
            
            // Simulate some work
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    printStrategy->finalize(allPrimes);
    return allPrimes;
}
