#pragma once

#include <iostream>
#include <string>

class ColorUtils {
public:
    // ANSI Color Codes
    static const std::string RESET;
    static const std::string BOLD;

    // Text Colors
    static const std::string RED;
    static const std::string GREEN;
    static const std::string YELLOW;
    static const std::string BLUE;
    static const std::string MAGENTA;
    static const std::string CYAN;
    static const std::string WHITE;
    static const std::string GRAY;

    // Background Colors
    static const std::string BG_RED;
    static const std::string BG_GREEN;
    static const std::string BG_YELLOW;
    static const std::string BG_BLUE;
    static const std::string BG_MAGENTA;
    static const std::string BG_CYAN;

    // Bright Colors
    static const std::string BRIGHT_RED;
    static const std::string BRIGHT_GREEN;
    static const std::string BRIGHT_YELLOW;
    static const std::string BRIGHT_BLUE;
    static const std::string BRIGHT_MAGENTA;
    static const std::string BRIGHT_CYAN;
    static const std::string BRIGHT_WHITE;

    // Helper functions
    static std::string colorize(const std::string &text, const std::string &color);
    static std::string bold(const std::string &text);
    static std::string error(const std::string &text);
    static std::string success(const std::string &text);
    static std::string warning(const std::string &text);
    static std::string info(const std::string &text);
    static std::string highlight(const std::string &text);
    static std::string prime(const std::string &text);
    static std::string thread(const std::string &text);
    static std::string timestamp(const std::string &text);

    // Check if colors should be enabled (can be disabled for non-terminal output)
    static bool isColorEnabled();
    static void setColorEnabled(bool enabled);

private:
    static bool colorEnabled;
};
