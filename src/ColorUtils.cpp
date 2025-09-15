#include "ColorUtils.h"
#include <unistd.h>

// Initialize static color enabled flag.
bool ColorUtils::colorEnabled = true;

// ANSI color code constants.
const std::string ColorUtils::RESET = "\033[0m";
const std::string ColorUtils::BOLD = "\033[1m";

// Basic text colors.
const std::string ColorUtils::RED = "\033[31m";
const std::string ColorUtils::GREEN = "\033[32m";
const std::string ColorUtils::YELLOW = "\033[33m";
const std::string ColorUtils::BLUE = "\033[34m";
const std::string ColorUtils::MAGENTA = "\033[35m";
const std::string ColorUtils::CYAN = "\033[36m";
const std::string ColorUtils::WHITE = "\033[37m";
const std::string ColorUtils::GRAY = "\033[90m";

// Background colors.
const std::string ColorUtils::BG_RED = "\033[41m";
const std::string ColorUtils::BG_GREEN = "\033[42m";
const std::string ColorUtils::BG_YELLOW = "\033[43m";
const std::string ColorUtils::BG_BLUE = "\033[44m";
const std::string ColorUtils::BG_MAGENTA = "\033[45m";
const std::string ColorUtils::BG_CYAN = "\033[46m";

// Bright color variants.
const std::string ColorUtils::BRIGHT_RED = "\033[91m";
const std::string ColorUtils::BRIGHT_GREEN = "\033[92m";
const std::string ColorUtils::BRIGHT_YELLOW = "\033[93m";
const std::string ColorUtils::BRIGHT_BLUE = "\033[94m";
const std::string ColorUtils::BRIGHT_MAGENTA = "\033[95m";
const std::string ColorUtils::BRIGHT_CYAN = "\033[96m";
const std::string ColorUtils::BRIGHT_WHITE = "\033[97m";

// Apply color to text if enabled.
std::string ColorUtils::colorize(const std::string &text, const std::string &color) {
    if (!isColorEnabled()) {
        return text;
    }
    return color + text + RESET;
}

// Make text bold.
std::string ColorUtils::bold(const std::string &text) { return colorize(text, BOLD); }

// Color text for error messages.
std::string ColorUtils::error(const std::string &text) { return colorize(text, BOLD + BRIGHT_RED); }

// Color text for success messages.
std::string ColorUtils::success(const std::string &text) { return colorize(text, BOLD + BRIGHT_GREEN); }

// Color text for warnings.
std::string ColorUtils::warning(const std::string &text) { return colorize(text, BOLD + BRIGHT_YELLOW); }

// Color text for informational messages.
std::string ColorUtils::info(const std::string &text) { return colorize(text, BRIGHT_BLUE); }

// Color text for highlights.
std::string ColorUtils::highlight(const std::string &text) { return colorize(text, BOLD + BRIGHT_CYAN); }

// Color text for prime numbers.
std::string ColorUtils::prime(const std::string &text) { return colorize(text, BOLD + BRIGHT_MAGENTA); }

// Color text for thread identifiers.
std::string ColorUtils::thread(const std::string &text) { return colorize(text, BRIGHT_CYAN); }

// Color text for timestamps.
std::string ColorUtils::timestamp(const std::string &text) { return colorize(text, GRAY); }

// Check if colors should be enabled.
bool ColorUtils::isColorEnabled() {
    // Check if output is a terminal and colors are enabled.
    return colorEnabled && isatty(STDOUT_FILENO);
}

// Set color enabled flag.
void ColorUtils::setColorEnabled(bool enabled) { colorEnabled = enabled; }
