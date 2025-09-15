# Makefile for Prime Number Finder

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -O2 -pthread
DEBUG_FLAGS = -g -DDEBUG
INCLUDE_DIR = include
SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
MAIN_SOURCES = $(filter-out $(SRC_DIR)/main.cpp, $(SOURCES))
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)

# Object files
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
MAIN_OBJECTS = $(MAIN_SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)
TEST_OBJECTS = $(TEST_SOURCES:$(TEST_DIR)/%.cpp=$(BUILD_DIR)/test_%.o)

# Executables
TARGET = $(BUILD_DIR)/prime_finder
TEST_TARGET = $(BUILD_DIR)/test_runner

# Default target
.PHONY: all
all: $(TARGET)

# Create build directory
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build main executable
$(TARGET): $(OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# Build object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build test object files
$(BUILD_DIR)/test_%.o: $(TEST_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Build test executable
$(TEST_TARGET): $(MAIN_OBJECTS) $(TEST_OBJECTS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) $^ -o $@

# Debug build
.PHONY: debug
debug: CXXFLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

# Run the program
.PHONY: run
run: $(TARGET)
	@echo "=== Running Prime Number Finder ==="
	./$(TARGET)

# Run tests
.PHONY: test
test: $(TEST_TARGET)
	@echo "=== Running Tests ==="
	./$(TEST_TARGET)

# Run tests with large numbers (slower but comprehensive)
.PHONY: test-large
test-large: $(TEST_TARGET)
	@echo "=== Running Comprehensive Tests with Large Numbers ==="
	@echo "This may take a while as it tests up to 10,000..."
	./$(TEST_TARGET)

# Run with different configurations
.PHONY: demo
demo: $(TARGET)
	@echo "=== Demo: Range Division with Immediate Print ==="
	@echo "threads = 4" > config.toml
	@echo "upper_limit = 20" >> config.toml
	@echo "print_mode = \"immediate\"" >> config.toml
	@echo "division_mode = \"range\"" >> config.toml
	./$(TARGET)
	@echo ""
	@echo "=== Demo: Queue Division with Batch Print ==="
	@echo "threads = 2" > config.toml
	@echo "upper_limit = 15" >> config.toml
	@echo "print_mode = \"batch\"" >> config.toml
	@echo "division_mode = \"queue\"" >> config.toml
	./$(TARGET)
	@echo ""
	@echo "Restoring original config..."
	@git checkout config.toml 2>/dev/null || echo "threads = 4" > config.toml && echo "upper_limit = 1000" >> config.toml && echo "print_mode = \"immediate\"" >> config.toml && echo "division_mode = \"range\"" >> config.toml

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)

# Show help
.PHONY: help
help:
	@echo "Prime Number Finder - Available targets:"
	@echo "  all     - Build the main executable (default)"
	@echo "  debug   - Build with debug flags"
	@echo "  run     - Build and run the program"
	@echo "  test    - Build and run tests"
	@echo "  demo    - Run demonstration with different configurations"
	@echo "  clean   - Remove build artifacts"
	@echo "  help    - Show this help message"
	@echo ""
	@echo "Configuration:"
	@echo "  Edit config.toml to change program parameters"
	@echo "  - threads: number of worker threads"
	@echo "  - upper_limit: find primes up to this number"
	@echo "  - print_mode: 'immediate' or 'batch'"
	@echo "  - division_mode: 'range' or 'queue'"

# Dependencies
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/ConfigParser.h $(INCLUDE_DIR)/PrimeFinderFactory.h
$(BUILD_DIR)/ConfigParser.o: $(SRC_DIR)/ConfigParser.cpp $(INCLUDE_DIR)/ConfigParser.h
$(BUILD_DIR)/PrimeFinderFactory.o: $(SRC_DIR)/PrimeFinderFactory.cpp $(INCLUDE_DIR)/PrimeFinderFactory.h
$(BUILD_DIR)/PrimeUtils.o: $(SRC_DIR)/PrimeUtils.cpp $(INCLUDE_DIR)/PrimeUtils.h
$(BUILD_DIR)/ColorUtils.o: $(SRC_DIR)/ColorUtils.cpp $(INCLUDE_DIR)/ColorUtils.h
$(BUILD_DIR)/ImmediatePrintStrategy.o: $(SRC_DIR)/ImmediatePrintStrategy.cpp $(INCLUDE_DIR)/ImmediatePrintStrategy.h $(INCLUDE_DIR)/ColorUtils.h
$(BUILD_DIR)/BatchPrintStrategy.o: $(SRC_DIR)/BatchPrintStrategy.cpp $(INCLUDE_DIR)/BatchPrintStrategy.h $(INCLUDE_DIR)/ColorUtils.h
$(BUILD_DIR)/RangeDivisionStrategy.o: $(SRC_DIR)/RangeDivisionStrategy.cpp $(INCLUDE_DIR)/RangeDivisionStrategy.h $(INCLUDE_DIR)/PrimeUtils.h $(INCLUDE_DIR)/ColorUtils.h
$(BUILD_DIR)/QueueDivisionStrategy.o: $(SRC_DIR)/QueueDivisionStrategy.cpp $(INCLUDE_DIR)/QueueDivisionStrategy.h $(INCLUDE_DIR)/PrimeUtils.h $(INCLUDE_DIR)/ColorUtils.h
$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(INCLUDE_DIR)/ConfigParser.h $(INCLUDE_DIR)/PrimeFinderFactory.h $(INCLUDE_DIR)/ColorUtils.h
