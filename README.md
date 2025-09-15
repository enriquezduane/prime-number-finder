# Prime Number Finder

## Video Demo

https://github.com/user-attachments/assets/abe8f090-8a9b-48a8-a7a4-da63efa24365

## Technology Used

- **C++20**
- **Standard Library**
- **doctest**: Lightweight testing framework
- **TOML**: Simple configuration file format for easy customization

## High-Level Architecture

The program follows clean design principles using design patterns.

### Strategy Patterns

**Print Strategies** decide when to show results:
- **Immediate Printing**: Shows each prime as soon as it's found, with thread ID and timestamp
- **Batch Printing**: Collects all primes and displays them neatly at the end

**Task Division Strategies** decide how to split work:
- **Range Division**: Divides the number range equally among threads (like 1-250, 251-500, etc.)
- **Queue Division**: Uses an atomic counter so threads grab work dynamically as they finish

### Factory Pattern

A factory creates the strategies based on your configuration file.

## Getting Started

### Quick Start
```bash

# Compile and Run
make run

# Run all tests
make test
```

### Configuration

Edit `config.toml` to customize:

```toml
threads = 8
upper_limit = 10000
print_mode = "immediate"
division_mode = "queue"
```

### Available Commands

- `make run` - Build and run the prime finder
- `make test` - Run comprehensive tests (160 assertions)
- `make clean` - Remove build artifacts
- `make help` - Show all available targets

## Testing & Validation

The program includes extensive tests covering:
- **Basic prime checking**: Individual numbers and ranges
- **Strategy correctness**: Both division methods produce identical results
- **Thread safety**: No duplicates or race conditions
- **Edge cases**: Numbers less than 2, large ranges, high thread counts
- **Performance**: Tested with up to 25,000 primes and 16 threads

All 160 test assertions pass.
