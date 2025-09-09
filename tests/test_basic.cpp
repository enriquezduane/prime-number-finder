#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "../include/ConfigParser.h"
#include "../include/PrimeFinderFactory.h"

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
