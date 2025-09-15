#pragma once

#include <cmath>
#include <vector>

class PrimeUtils {
public:
    /**
     * Check if a single number is prime
     * Uses trial division with optimizations
     */
    static bool isPrime(int number);

    /**
     * Find all primes in a given range [start, end] (inclusive)
     * Uses optimized trial division
     */
    static std::vector<int> findPrimesInRange(int start, int end);

    /**
     * Get a reference list of known primes up to a limit for testing
     * Uses sieve of Eratosthenes for verification
     */
    static std::vector<int> getKnownPrimes(int limit);

private:
    /**
     * Optimized prime checking using trial division
     * Handles edge cases and uses square root optimization
     */
    static bool isPrimeTrialDivision(int number);
};
