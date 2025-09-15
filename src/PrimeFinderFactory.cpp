#include "PrimeFinderFactory.h"
#include "BatchPrintStrategy.h"
#include "ImmediatePrintStrategy.h"
#include "QueueDivisionStrategy.h"
#include "RangeDivisionStrategy.h"
#include <algorithm>
#include <stdexcept>

// Create print strategy based on mode.
std::shared_ptr<IPrintStrategy> PrimeFinderFactory::createPrintStrategy(PrintMode mode) {
    switch (mode) {
    case PrintMode::IMMEDIATE:
        return std::make_shared<ImmediatePrintStrategy>();
    case PrintMode::BATCH:
        return std::make_shared<BatchPrintStrategy>();
    default:
        throw std::invalid_argument("Unknown print mode");
    }
}

// Create division strategy based on mode.
std::shared_ptr<ITaskDivisionStrategy> PrimeFinderFactory::createDivisionStrategy(DivisionMode mode) {
    switch (mode) {
    case DivisionMode::RANGE:
        return std::make_shared<RangeDivisionStrategy>();
    case DivisionMode::QUEUE:
        return std::make_shared<QueueDivisionStrategy>();
    default:
        throw std::invalid_argument("Unknown division mode");
    }
}

// Parse print mode from string.
PrintMode PrimeFinderFactory::parsePrintMode(const std::string &mode) {
    std::string lowerMode = mode;
    std::transform(lowerMode.begin(), lowerMode.end(), lowerMode.begin(), ::tolower);

    if (lowerMode == "immediate") {
        return PrintMode::IMMEDIATE;
    } else if (lowerMode == "batch") {
        return PrintMode::BATCH;
    } else {
        throw std::invalid_argument("Invalid print mode: " + mode);
    }
}

// Parse division mode from string.
DivisionMode PrimeFinderFactory::parseDivisionMode(const std::string &mode) {
    std::string lowerMode = mode;
    std::transform(lowerMode.begin(), lowerMode.end(), lowerMode.begin(), ::tolower);

    if (lowerMode == "range") {
        return DivisionMode::RANGE;
    } else if (lowerMode == "queue") {
        return DivisionMode::QUEUE;
    } else {
        throw std::invalid_argument("Invalid division mode: " + mode);
    }
}
