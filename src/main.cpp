#include <chrono>
#include <format>
#include <iostream>

#include "ColorUtils.h"
#include "ConfigParser.h"
#include "IPrintStrategy.h"
#include "ITaskDivisionStrategy.h"
#include "PrimeFinderFactory.h"

// Print timestamp with label.
void printTimestamp(const std::string &label) {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::cout << ColorUtils::bold("[" + label + "]") << " "
              << ColorUtils::timestamp(
                     std::format("{:%a %b %d %H:%M:%S %Y}", std::chrono::system_clock::from_time_t(time_t)))
              << std::endl;
}

int main() {
    printTimestamp("PROGRAM START");

    std::cout << ColorUtils::bold("=== ") << ColorUtils::highlight("Prime Number Finder")
              << ColorUtils::bold(" ===") << std::endl;

    // Parse and display configuration.
    Config config = ConfigParser::parseConfig("config.toml");

    std::cout << ColorUtils::info("Configuration:") << std::endl;
    std::cout << "  Threads: " << ColorUtils::bold(std::to_string(config.threads)) << std::endl;
    std::cout << "  Upper Limit: " << ColorUtils::bold(std::to_string(config.upperLimit)) << std::endl;
    std::cout << "  Print Mode: " << ColorUtils::highlight(config.printMode) << std::endl;
    std::cout << "  Division Mode: " << ColorUtils::highlight(config.divisionMode) << std::endl;
    std::cout << std::endl;

    // Execute prime finding with error handling.
    try {
        // Create strategies using factory.
        auto printStrategy =
            PrimeFinderFactory::createPrintStrategy(PrimeFinderFactory::parsePrintMode(config.printMode));

        auto divisionStrategy = PrimeFinderFactory::createDivisionStrategy(
            PrimeFinderFactory::parseDivisionMode(config.divisionMode));

        // Execute prime finding.
        std::cout << ColorUtils::info("Starting prime finding...") << std::endl;
        auto primes = divisionStrategy->findPrimes(config.upperLimit, config.threads, printStrategy);

        std::cout << std::endl << ColorUtils::success("Execution completed successfully!") << std::endl;

    } catch (const std::exception &e) {
        std::cerr << ColorUtils::error("Error: " + std::string(e.what())) << std::endl;
        printTimestamp("PROGRAM END (ERROR)");
        return 1;
    }

    printTimestamp("PROGRAM END");
    return 0;
}
