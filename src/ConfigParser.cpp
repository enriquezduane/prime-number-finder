#include "ConfigParser.h"
#include <fstream>
#include <sstream>
#include <iostream>

Config ConfigParser::parseConfig(const std::string& filename) {
    Config config = getDefaultConfig();
    
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Config file '" << filename << "' not found. Using defaults." << std::endl;
        return config;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            continue;
        }
        
        // Simple TOML-like parsing
        size_t equalPos = line.find('=');
        if (equalPos == std::string::npos) {
            continue;
        }
        
        std::string key = line.substr(0, equalPos);
        std::string value = line.substr(equalPos + 1);
        
        // Trim whitespace
        key.erase(0, key.find_first_not_of(" \t"));
        key.erase(key.find_last_not_of(" \t") + 1);
        value.erase(0, value.find_first_not_of(" \t\""));
        value.erase(value.find_last_not_of(" \t\"") + 1);
        
        try {
            if (key == "threads") {
                config.threads = std::stoi(value);
            } else if (key == "upper_limit") {
                config.upperLimit = std::stoi(value);
            } else if (key == "print_mode") {
                config.printMode = value;
            } else if (key == "division_mode") {
                config.divisionMode = value;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing config value for '" << key << "': " << e.what() << std::endl;
        }
    }
    
    return config;
}

Config ConfigParser::getDefaultConfig() {
    return Config{}; // Uses default values from struct definition
}
