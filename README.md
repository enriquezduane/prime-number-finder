# Prime Number Finder - Scaffolding

This is a scalable C++20 scaffolding for a multi-threaded prime number finder. The current implementation provides a "Hello World" foundation that demonstrates the architecture and design patterns, ready for full prime-finding logic implementation.

## Architecture

The project uses the **Strategy Pattern** with **Factory Pattern** to create a flexible, extensible system:

### Strategy Patterns Implemented

1. **Print Strategies** (`IPrintStrategy`)
   - `ImmediatePrintStrategy`: Prints primes immediately when found
   - `BatchPrintStrategy`: Collects all primes and prints them after completion

2. **Task Division Strategies** (`ITaskDivisionStrategy`)
   - `RangeDivisionStrategy`: Divides the search range equally among threads
   - `QueueDivisionStrategy`: Uses atomic counter for dynamic work distribution

### Key Components

- **Factory**: `PrimeFinderFactory` creates strategy instances based on configuration
- **Configuration**: `ConfigParser` reads TOML-like configuration files
- **Thread Safety**: Proper mutex usage for console output and shared data

## Quick Start

### Build and Run
```bash
# Show available targets
make help

# Build and run with default config
make run

# Build and run tests
make test

# Clean build artifacts
make clean

# Run demonstration with different configurations
make demo
```

### Configuration

Edit `config.toml` to customize behavior:

```toml
# Number of threads to use
threads = 4

# Upper limit for prime search
upper_limit = 1000

# Print mode: "immediate" or "batch"
print_mode = "immediate"

# Division mode: "range" or "queue"
division_mode = "range"
```

## Current "Hello World" Implementation

The scaffolding currently:
- ✅ Implements complete strategy pattern architecture
- ✅ Demonstrates multi-threading with proper synchronization
- ✅ Shows configuration file parsing
- ✅ Includes basic testing framework (doctest)
- ✅ Simulates prime finding (finds 2, 3, 5, 7 as demonstration)
- ✅ Provides timestamps at program start/end
- ✅ Thread-safe console output

## Ready for Implementation

To implement actual prime finding, you need to:

1. **Replace simulation logic** in:
   - `src/RangeDivisionStrategy.cpp`: Implement actual range-based prime checking
   - `src/QueueDivisionStrategy.cpp`: Implement actual queue-based prime checking

2. **Add prime checking algorithm**: Create a utility function for testing primality

3. **Enhance testing**: Add tests for actual prime number correctness

4. **Optional enhancements**: Add more configuration options, performance metrics, etc.

## Project Structure

```
prime-number-finder/
├── include/                    # Header files
│   ├── doctest/               # Testing framework
│   ├── IPrintStrategy.h       # Print strategy interface
│   ├── ITaskDivisionStrategy.h # Task division interface
│   ├── ImmediatePrintStrategy.h
│   ├── BatchPrintStrategy.h
│   ├── RangeDivisionStrategy.h
│   ├── QueueDivisionStrategy.h
│   ├── PrimeFinderFactory.h   # Factory for creating strategies
│   └── ConfigParser.h         # Configuration file parser
├── src/                       # Implementation files
│   ├── main.cpp              # Main program entry point
│   └── *.cpp                 # Strategy implementations
├── tests/                     # Test files
│   └── test_basic.cpp        # Basic functionality tests
├── build/                     # Build artifacts (created by make)
├── config.toml               # Configuration file
├── Makefile                  # Build system
└── IMPLEMENTATION_PLAN.md    # Original requirements
```

## Design Patterns Used

- **Strategy Pattern**: Encapsulates printing and task division algorithms
- **Factory Pattern**: Creates appropriate strategy instances
- **RAII**: Proper resource management with smart pointers and RAII containers

## Thread Safety Features

- **Mutex protection** for console output (immediate printing)
- **Atomic counters** for queue-based work distribution
- **Thread-safe collection** of results for batch printing
- **Proper thread joining** to ensure completion

## Testing

The project includes comprehensive tests using doctest:
- Configuration parsing tests
- Factory creation tests
- Strategy instantiation tests
- Mode parsing validation

Run tests with: `make test`

## Scalability Features

The architecture is designed to easily accommodate:
- Additional printing strategies
- New task division algorithms
- Different prime checking algorithms
- Enhanced configuration options
- Performance monitoring
- Different output formats

This scaffolding provides a solid foundation that follows best practices and design patterns, making it easy to implement the full prime-finding functionality according to your requirements.
