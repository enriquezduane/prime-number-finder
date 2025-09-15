#include "PrimeUtils.h"
#include <algorithm>
#include <cmath>

// Check if number is prime using trial division.
bool PrimeUtils::isPrime(int number) { return isPrimeTrialDivision(number); }

// Optimized trial division prime checking.
bool PrimeUtils::isPrimeTrialDivision(int number) {
    // Handle edge cases.
    if (number < 2)
        return false;
    if (number == 2)
        return true;
    if (number % 2 == 0)
        return false;

    // Check odd divisors up to sqrt(number).
    int limit = static_cast<int>(std::sqrt(number));
    for (int i = 3; i <= limit; i += 2) {
        if (number % i == 0) {
            return false;
        }
    }

    return true;
}

// Find all primes in given range.
std::vector<int> PrimeUtils::findPrimesInRange(int start, int end) {
    std::vector<int> primes;

    // Ensure valid range.
    if (start > end || end < 2) {
        return primes;
    }

    // Adjust start to be at least 2.
    int actualStart = std::max(2, start);

    for (int i = actualStart; i <= end; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }

    return primes;
}

// Generate primes using Sieve of Eratosthenes.
std::vector<int> PrimeUtils::getKnownPrimes(int limit) {
    // Handle edge case.
    if (limit < 2) {
        return {};
    }

    // Initialize sieve array.
    std::vector<bool> isPrimeArray(limit + 1, true);
    isPrimeArray[0] = isPrimeArray[1] = false;

    // Mark composites.
    for (long long i = 2; i * i <= limit; ++i) {
        if (isPrimeArray[i]) {
            for (long long j = i * i; j <= limit; j += i) {
                isPrimeArray[j] = false;
            }
        }
    }

    // Collect primes.
    std::vector<int> primes;
    for (int i = 2; i <= limit; ++i) {
        if (isPrimeArray[i]) {
            primes.push_back(i);
        }
    }

    return primes;
}
