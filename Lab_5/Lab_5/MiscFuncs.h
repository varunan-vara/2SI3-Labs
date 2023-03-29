#ifndef MISCFUNCS
#define MISCFUNCS

// Avoided creating a seperate cpp file using the static keyword
static bool isNumPrime(int n) {
    for (int x = 2; x <= n / 2; x++) {
        if (n % x == 0) {
            return false;
        }
    }
    return true;
}

#endif
