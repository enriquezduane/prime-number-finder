#pragma once

#include <memory>
#include <string>

class ITaskDivisionStrategy;
class IPrintStrategy;

enum class PrintMode { IMMEDIATE, BATCH };

enum class DivisionMode { RANGE, QUEUE };

class PrimeFinderFactory {
public:
    static std::shared_ptr<IPrintStrategy> createPrintStrategy(PrintMode mode);
    static std::shared_ptr<ITaskDivisionStrategy> createDivisionStrategy(DivisionMode mode);

    // Helper functions to parse modes from strings
    static PrintMode parsePrintMode(const std::string &mode);
    static DivisionMode parseDivisionMode(const std::string &mode);
};
