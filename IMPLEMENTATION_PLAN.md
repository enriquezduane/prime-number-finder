# Requirements

**Task:** Create a program that utilizes a specified number of threads (x) to find all prime numbers up to a given number (y). The values for 'x' and 'y' must be configurable through a separate configuration file.

**Requirements:**

**A. Different printing variations:**

*   **I. Print immediately:**
    *   When a prime number is found, it should be printed to the console instantly.
    *   Each printout must include the ID of the thread that found the number and a timestamp.
*   **II. Wait and print:**
    *   The program should wait until all threads have completed their search.
    *   Once all threads are finished, the program should print all the found prime numbers at once.

**B. Different task division schemes:**

*   **I. Straight division of search range:**
    *   The total range of numbers to be checked for primes should be divided equally among the available threads.
    *   For example, if the range is 1 to 1000 and there are 4 threads, the division will be:
        *   Thread 1: 1 - 250
        *   Thread 2: 251 - 500
        *   Thread 3: 501 - 750
        *   Thread 4: 751 - 1000
*   **II. Linear search with divisibility testing:**
    *   The program will iterate through numbers linearly.
    *   The threads will be responsible for performing the divisibility tests for each individual number.

**General Requirement:**

*   A timestamp must be printed at the absolute start AND end of every program execution.

# Testable Deterministic Properties

## Applicable to All Test Cases
- Correctness of the Prime Number List: For a given input y, the program must always produce the exact same list of prime numbers.
- Handling of Edge Cases:
    - Input y less than 2: The program should return an empty list of primes.
    - Input y being a prime number: The list should correctly include y.
    - Large input y: Large enough to cause issues
- Configuration File Parsing: The function responsible for reading the number of threads (x) and the upper limit (y) from the configuration file should be tested to ensure it parses the values correctly and handles potential errors like a missing file or invalid data.

## Straight Division of Search Range (A1B1 and A2B1)
- Correct Range Division:  Given a total range and a number of threads, the test should assert that the sub-ranges are calculated correctly and cover the entire range without any overlaps or gaps.
- Completeness of Results (for A2B1): After the threads have run, the test can compare the size and content of the resulting list against a known correct list for the given range.

## Linear Search with Divisibility Testing (A1B2 and A2B2)
- No Duplicate Primes: Final list of prime numbers contains no duplicates.
- Completeness of Final Prime List (for A2B2): Similar to A2B1, the test should confirm that the final list of primes is accurate and complete for the given input y.


