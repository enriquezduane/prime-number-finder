#include "QueueDivisionStrategy.h"
#include "IPrintStrategy.h"
#include <thread>
#include <vector>
#include <atomic>
#include <chrono>
#include <iostream>

std::vector<int> QueueDivisionStrategy::findPrimes(int upperLimit, int numThreads, 
                                                   std::shared_ptr<IPrintStrategy> printStrategy) {
    std::cout << "[QUEUE DIVISION] Hello World! Simulating queue division with " 
              << numThreads << " threads for range 1-" << upperLimit << std::endl;
    
    std::vector<int> allPrimes;
    std::vector<std::thread> threads;
    std::mutex primesMutex;
    std::atomic<int> counter{1};
    
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back([&counter, upperLimit, printStrategy, &allPrimes, &primesMutex]() {
            std::cout << "[THREAD " << std::this_thread::get_id() 
                      << "] Starting queue-based processing" << std::endl;
            
            std::vector<int> threadPrimes;
            
            while (true) {
                int current = counter.fetch_add(1);
                if (current > upperLimit) break;
                
                // Simulate prime checking (just check for 2, 3, 5, 7 for demo)
                if (current == 2 || current == 3 || current == 5 || current == 7) {
                    auto timestamp = std::chrono::system_clock::now();
                    printStrategy->printPrime(current, std::this_thread::get_id(), timestamp);
                    
                    std::lock_guard<std::mutex> lock(primesMutex);
                    allPrimes.push_back(current);
                }
                
                // Simulate some work
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    printStrategy->finalize(allPrimes);
    return allPrimes;
}
