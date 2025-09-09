#pragma once

#include <string>

struct Config {
    int threads = 4;
    int upperLimit = 1000;
    std::string printMode = "immediate";    // "immediate" or "batch"
    std::string divisionMode = "range";     // "range" or "queue"
};

class ConfigParser {
public:
    static Config parseConfig(const std::string& filename);
private:
    static Config getDefaultConfig();
};
