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

--
