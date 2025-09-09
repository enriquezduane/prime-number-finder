#include <iostream>
#include <chrono>
#include <ctime>
#include "ConfigParser.h"
#include "PrimeFinderFactory.h"
#include "ITaskDivisionStrategy.h"
#include "IPrintStrategy.h"

void printTimestamp(const std::string& label) {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::cout << "[" << label << "] " << std::ctime(&time_t);
}

int main() {
    printTimestamp("PROGRAM START");
    
    std::cout << "=== Prime Number Finder - Hello World Scaffolding ===" << std::endl;
    
    // Parse configuration
    Config config = ConfigParser::parseConfig("config.toml");
    
    std::cout << "Configuration:" << std::endl;
    std::cout << "  Threads: " << config.threads << std::endl;
    std::cout << "  Upper Limit: " << config.upperLimit << std::endl;
    std::cout << "  Print Mode: " << config.printMode << std::endl;
    std::cout << "  Division Mode: " << config.divisionMode << std::endl;
    std::cout << std::endl;
    
    try {
        // Create strategies using factory
        auto printStrategy = PrimeFinderFactory::createPrintStrategy(
            PrimeFinderFactory::parsePrintMode(config.printMode)
        );
        
        auto divisionStrategy = PrimeFinderFactory::createDivisionStrategy(
            PrimeFinderFactory::parseDivisionMode(config.divisionMode)
        );
        
        // Execute prime finding
        std::cout << "Starting prime finding..." << std::endl;
        auto primes = divisionStrategy->findPrimes(config.upperLimit, config.threads, printStrategy);
        
        std::cout << std::endl << "Execution completed successfully!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        printTimestamp("PROGRAM END (ERROR)");
        return 1;
    }
    
    printTimestamp("PROGRAM END");
    return 0;
}
