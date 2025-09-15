#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "../include/ConfigParser.h"
#include "../include/PrimeFinderFactory.h"
#include "../include/PrimeUtils.h"
#include "../include/RangeDivisionStrategy.h"
#include "../include/QueueDivisionStrategy.h"
#include "../include/ImmediatePrintStrategy.h"
#include "../include/BatchPrintStrategy.h"
#include <algorithm>

TEST_CASE("Config Parser - Default Values") {
    Config defaultConfig = ConfigParser::parseConfig("nonexistent.toml");
    
    CHECK(defaultConfig.threads == 4);
    CHECK(defaultConfig.upperLimit == 1000);
    CHECK(defaultConfig.printMode == "immediate");
    CHECK(defaultConfig.divisionMode == "range");
}

TEST_CASE("Factory - Print Strategy Creation") {
    SUBCASE("Immediate Print Strategy") {
        auto strategy = PrimeFinderFactory::createPrintStrategy(PrintMode::IMMEDIATE);
        CHECK(strategy != nullptr);
    }
    
    SUBCASE("Batch Print Strategy") {
        auto strategy = PrimeFinderFactory::createPrintStrategy(PrintMode::BATCH);
        CHECK(strategy != nullptr);
    }
}

TEST_CASE("Factory - Division Strategy Creation") {
    SUBCASE("Range Division Strategy") {
        auto strategy = PrimeFinderFactory::createDivisionStrategy(DivisionMode::RANGE);
        CHECK(strategy != nullptr);
    }
    
    SUBCASE("Queue Division Strategy") {
        auto strategy = PrimeFinderFactory::createDivisionStrategy(DivisionMode::QUEUE);
        CHECK(strategy != nullptr);
    }
}

TEST_CASE("Factory - Mode Parsing") {
    SUBCASE("Print Mode Parsing") {
        CHECK(PrimeFinderFactory::parsePrintMode("immediate") == PrintMode::IMMEDIATE);
        CHECK(PrimeFinderFactory::parsePrintMode("IMMEDIATE") == PrintMode::IMMEDIATE);
        CHECK(PrimeFinderFactory::parsePrintMode("batch") == PrintMode::BATCH);
        CHECK(PrimeFinderFactory::parsePrintMode("BATCH") == PrintMode::BATCH);
        
        CHECK_THROWS(PrimeFinderFactory::parsePrintMode("invalid"));
    }
    
    SUBCASE("Division Mode Parsing") {
        CHECK(PrimeFinderFactory::parseDivisionMode("range") == DivisionMode::RANGE);
        CHECK(PrimeFinderFactory::parseDivisionMode("RANGE") == DivisionMode::RANGE);
        CHECK(PrimeFinderFactory::parseDivisionMode("queue") == DivisionMode::QUEUE);
        CHECK(PrimeFinderFactory::parseDivisionMode("QUEUE") == DivisionMode::QUEUE);
        
        CHECK_THROWS(PrimeFinderFactory::parseDivisionMode("invalid"));
    }
}

TEST_CASE("Prime Utils - Individual Prime Testing") {
    SUBCASE("Edge Cases") {
        CHECK_FALSE(PrimeUtils::isPrime(-1));
        CHECK_FALSE(PrimeUtils::isPrime(0));
        CHECK_FALSE(PrimeUtils::isPrime(1));
        CHECK(PrimeUtils::isPrime(2));
        CHECK(PrimeUtils::isPrime(3));
        CHECK_FALSE(PrimeUtils::isPrime(4));
    }
    
    SUBCASE("Known Primes") {
        std::vector<int> knownPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};
        for (int prime : knownPrimes) {
            CHECK(PrimeUtils::isPrime(prime));
        }
    }
    
    SUBCASE("Known Composites") {
        std::vector<int> composites = {4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24, 25};
        for (int composite : composites) {
            CHECK_FALSE(PrimeUtils::isPrime(composite));
        }
    }
    
    SUBCASE("Larger Primes") {
        CHECK(PrimeUtils::isPrime(97));
        CHECK(PrimeUtils::isPrime(101));
        CHECK(PrimeUtils::isPrime(103));
        CHECK(PrimeUtils::isPrime(997));
        CHECK_FALSE(PrimeUtils::isPrime(999)); // 999 = 3 * 333
    }
}

TEST_CASE("Prime Utils - Range Finding") {
    SUBCASE("Small Range") {
        auto primes = PrimeUtils::findPrimesInRange(1, 10);
        std::vector<int> expected = {2, 3, 5, 7};
        CHECK(primes == expected);
    }
    
    SUBCASE("Range Starting from Prime") {
        auto primes = PrimeUtils::findPrimesInRange(11, 20);
        std::vector<int> expected = {11, 13, 17, 19};
        CHECK(primes == expected);
    }
    
    SUBCASE("Empty Range") {
        auto primes = PrimeUtils::findPrimesInRange(1, 1);
        CHECK(primes.empty());
    }
    
    SUBCASE("Invalid Range") {
        auto primes = PrimeUtils::findPrimesInRange(10, 5);
        CHECK(primes.empty());
    }
}

TEST_CASE("Prime Utils - Known Primes Reference") {
    SUBCASE("First 25 Primes") {
        auto primes = PrimeUtils::getKnownPrimes(100);
        std::vector<int> first25 = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        
        CHECK(primes.size() >= 25);
        for (size_t i = 0; i < 25; ++i) {
            CHECK(primes[i] == first25[i]);
        }
    }
    
    SUBCASE("Edge Case - Limit 2") {
        auto primes = PrimeUtils::getKnownPrimes(2);
        std::vector<int> expected = {2};
        CHECK(primes == expected);
    }
    
    SUBCASE("Edge Case - Limit 1") {
        auto primes = PrimeUtils::getKnownPrimes(1);
        CHECK(primes.empty());
    }
}

TEST_CASE("Strategy Correctness - Range Division") {
    SUBCASE("Small Range Correctness") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(30, 2, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(30);
        
        // Sort both vectors for comparison
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes == expectedPrimes);
    }
    
    SUBCASE("No Duplicates in Range Division") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(50, 4, printStrategy);
        
        // Check for duplicates
        std::sort(foundPrimes.begin(), foundPrimes.end());
        auto uniqueEnd = std::unique(foundPrimes.begin(), foundPrimes.end());
        CHECK(uniqueEnd == foundPrimes.end());
    }
}

TEST_CASE("Strategy Correctness - Queue Division") {
    SUBCASE("Small Range Correctness") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        QueueDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(30, 2, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(30);
        
        // Sort both vectors for comparison
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes == expectedPrimes);
    }
    
    SUBCASE("No Duplicates in Queue Division") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        QueueDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(50, 3, printStrategy);
        
        // Check for duplicates
        std::sort(foundPrimes.begin(), foundPrimes.end());
        auto uniqueEnd = std::unique(foundPrimes.begin(), foundPrimes.end());
        CHECK(uniqueEnd == foundPrimes.end());
    }
}

TEST_CASE("Edge Cases - Both Strategies") {
    SUBCASE("Upper Limit Less Than 2") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy rangeStrategy;
        QueueDivisionStrategy queueStrategy;
        
        auto rangePrimes = rangeStrategy.findPrimes(1, 2, printStrategy);
        auto queuePrimes = queueStrategy.findPrimes(1, 2, printStrategy);
        
        CHECK(rangePrimes.empty());
        CHECK(queuePrimes.empty());
    }
    
    SUBCASE("Upper Limit is Prime") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy rangeStrategy;
        QueueDivisionStrategy queueStrategy;
        
        int primeLimit = 17;
        auto rangePrimes = rangeStrategy.findPrimes(primeLimit, 2, printStrategy);
        auto queuePrimes = queueStrategy.findPrimes(primeLimit, 2, printStrategy);
        auto expected = PrimeUtils::getKnownPrimes(primeLimit);
        
        std::sort(rangePrimes.begin(), rangePrimes.end());
        std::sort(queuePrimes.begin(), queuePrimes.end());
        
        CHECK(rangePrimes == expected);
        CHECK(queuePrimes == expected);
        CHECK(std::find(rangePrimes.begin(), rangePrimes.end(), primeLimit) != rangePrimes.end());
        CHECK(std::find(queuePrimes.begin(), queuePrimes.end(), primeLimit) != queuePrimes.end());
    }
}

TEST_CASE("Large Number Tests - Prime Utils") {
    SUBCASE("Large Individual Primes") {
        // Test some known large primes
        CHECK(PrimeUtils::isPrime(1009));    // 169th prime
        CHECK(PrimeUtils::isPrime(1013));    // 170th prime
        CHECK(PrimeUtils::isPrime(7919));    // 1000th prime
        CHECK(PrimeUtils::isPrime(9973));    // 1229th prime
        CHECK(PrimeUtils::isPrime(15013));   // Large prime
        CHECK(PrimeUtils::isPrime(25013));   // Larger prime
        
        // Test some large composites
        CHECK_FALSE(PrimeUtils::isPrime(1001));  // 7 * 11 * 13
        CHECK_FALSE(PrimeUtils::isPrime(9999));  // 3^2 * 11 * 101
        CHECK_FALSE(PrimeUtils::isPrime(10001)); // 73 * 137
        CHECK_FALSE(PrimeUtils::isPrime(25000)); // 2^3 * 5^5
    }
    
    SUBCASE("Large Range Finding") {
        // Test finding primes in range 1000-1100
        auto primes = PrimeUtils::findPrimesInRange(1000, 1100);
        auto expected = PrimeUtils::getKnownPrimes(1100);
        
        // Filter expected to range 1000-1100
        std::vector<int> expectedInRange;
        for (int prime : expected) {
            if (prime >= 1000 && prime <= 1100) {
                expectedInRange.push_back(prime);
            }
        }
        
        CHECK(primes.size() == expectedInRange.size());
        CHECK(primes == expectedInRange);
        
        // Should include known primes in this range
        CHECK(std::find(primes.begin(), primes.end(), 1009) != primes.end());
        CHECK(std::find(primes.begin(), primes.end(), 1013) != primes.end());
        CHECK(std::find(primes.begin(), primes.end(), 1019) != primes.end());
    }
    
    SUBCASE("Very Large Known Primes Reference") {
        auto primes = PrimeUtils::getKnownPrimes(5000);
        
        // Should have correct count (there are 669 primes up to 5000)
        CHECK(primes.size() == 669);
        
        // Should include known large primes
        CHECK(std::find(primes.begin(), primes.end(), 4999) != primes.end()); // Large prime
        CHECK(std::find(primes.begin(), primes.end(), 4993) != primes.end()); // Another large prime
        CHECK(std::find(primes.begin(), primes.end(), 4987) != primes.end()); // Another large prime
        
        // Should be sorted
        CHECK(std::is_sorted(primes.begin(), primes.end()));
    }
}

TEST_CASE("Large Number Strategy Tests - Range Division") {
    SUBCASE("Medium Scale - 1000 Range") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(1000, 4, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(1000);
        
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes.size() == 168); // There are 168 primes up to 1000
        CHECK(foundPrimes == expectedPrimes);
        
        // Verify no duplicates
        auto uniqueEnd = std::unique(foundPrimes.begin(), foundPrimes.end());
        CHECK(uniqueEnd == foundPrimes.end());
    }
    
    SUBCASE("Large Scale - 5000 Range") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(5000, 8, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(5000);
        
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes.size() == 669); // There are 669 primes up to 5000
        CHECK(foundPrimes == expectedPrimes);
        
        // Verify specific large primes are found
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 4999) != foundPrimes.end());
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 4993) != foundPrimes.end());
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 4987) != foundPrimes.end());
    }
    
    SUBCASE("High Thread Count") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy strategy;
        
        // Use many threads to test thread safety
        auto foundPrimes = strategy.findPrimes(2000, 16, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(2000);
        
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes.size() == 303); // There are 303 primes up to 2000
        CHECK(foundPrimes == expectedPrimes);
    }
}

TEST_CASE("Large Number Strategy Tests - Queue Division") {
    SUBCASE("Medium Scale - 1000 Range") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        QueueDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(1000, 4, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(1000);
        
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes.size() == 168); // There are 168 primes up to 1000
        CHECK(foundPrimes == expectedPrimes);
        
        // Verify no duplicates
        auto uniqueEnd = std::unique(foundPrimes.begin(), foundPrimes.end());
        CHECK(uniqueEnd == foundPrimes.end());
    }
    
    SUBCASE("Large Scale - 5000 Range") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        QueueDivisionStrategy strategy;
        
        auto foundPrimes = strategy.findPrimes(5000, 8, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(5000);
        
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes.size() == 669); // There are 669 primes up to 5000
        CHECK(foundPrimes == expectedPrimes);
        
        // Verify specific large primes are found
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 4999) != foundPrimes.end());
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 4993) != foundPrimes.end());
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 4987) != foundPrimes.end());
    }
    
    SUBCASE("High Thread Count with Queue") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        QueueDivisionStrategy strategy;
        
        // Use many threads to test atomic counter performance
        auto foundPrimes = strategy.findPrimes(2000, 16, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(2000);
        
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes.size() == 303); // There are 303 primes up to 2000
        CHECK(foundPrimes == expectedPrimes);
    }
}

TEST_CASE("Stress Tests - Both Strategies") {
    SUBCASE("Strategy Consistency - Large Range") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy rangeStrategy;
        QueueDivisionStrategy queueStrategy;
        
        // Test that both strategies produce identical results for large ranges
        auto rangePrimes = rangeStrategy.findPrimes(3000, 6, printStrategy);
        auto queuePrimes = queueStrategy.findPrimes(3000, 6, printStrategy);
        auto expected = PrimeUtils::getKnownPrimes(3000);
        
        std::sort(rangePrimes.begin(), rangePrimes.end());
        std::sort(queuePrimes.begin(), queuePrimes.end());
        
        // Both should match expected
        CHECK(rangePrimes.size() == expected.size());
        CHECK(queuePrimes.size() == expected.size());
        CHECK(rangePrimes.size() == 430); // There are 430 primes up to 3000
        
        // Both strategies should produce identical results
        CHECK(rangePrimes == queuePrimes);
        CHECK(rangePrimes == expected);
    }
    
    SUBCASE("Memory and Performance - Very Large Range") {
        auto printStrategy = std::make_shared<BatchPrintStrategy>();
        RangeDivisionStrategy strategy;
        
        // Test with a very large range to ensure memory efficiency
        auto foundPrimes = strategy.findPrimes(10000, 12, printStrategy);
        auto expectedPrimes = PrimeUtils::getKnownPrimes(10000);
        
        std::sort(foundPrimes.begin(), foundPrimes.end());
        
        CHECK(foundPrimes.size() == expectedPrimes.size());
        CHECK(foundPrimes.size() == 1229); // There are 1229 primes up to 10000
        CHECK(foundPrimes == expectedPrimes);
        
        // Verify largest primes are correctly found
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 9973) != foundPrimes.end()); // 1229th prime
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 9967) != foundPrimes.end());
        CHECK(std::find(foundPrimes.begin(), foundPrimes.end(), 9949) != foundPrimes.end());
    }
}