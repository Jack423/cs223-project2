//
// Created by Jack Butler on 4/10/18.
//

#ifndef CS223_PROJECT2_PRIMEGENERATION_H
#define CS223_PROJECT2_PRIMEGENERATION_H

#include <cmath>

class PrimeGeneration {

    /**
     * Sieve of Eratosthenes method for generating primes
     */
public:
    static int getLargestBoundedPrime(int n) {

        bool prime[n + 1];
        for (int i = 0; i < n; i++)
            prime[i] = true;

        for (int p = 2; p <= sqrt(n); p++) {
            // If prime[p] is not changed, then it is a prime
            if (prime[p]) {
                // Update all multiples of p
                for (int i = p * 2; i <= n; i += p)
                    prime[i] = false;
            }
        }

        // Get Largest Prime <= n
        for (int i = n; i >= 2; i--) {
            if (prime[i])
                return i;
        }
        return 2;
    }
};

#endif //CS223_PROJECT2_PRIMEGENERATION_H
