#include <stdio.h>

long long modExp(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long extGcd(long long a, long long b, long long *x, long long *y) {
    if (b == 0) { *x = 1; *y = 0; return a; }
    long long x1, y1;
    long long g = extGcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

int main() {
    long long q = 353, a = 3;
    long long xA = 45, xB = 78;

    long long YA = modExp(xA, a, q);
    long long YB = modExp(xB, a, q);

    printf("Public Parameters: Prime q = %lld, Exponent a = %lld\n", q, a);
    printf("Alice secret xA = %lld -> Sends YA = xA^a mod q = %lld\n", xA, YA);
    printf("Bob secret   xB = %lld -> Sends YB = xB^a mod q = %lld\n\n", xB, YB);

    long long K_Alice = (modExp(YA, 1, q) * YB) % q;
    long long K_Bob   = (YA * modExp(YB, 1, q)) % q;
    printf("Shared Key Candidate: (YA * YB) mod q = %lld\n\n", K_Alice);

    long long x, y;
    extGcd(a, q - 1, &x, &y);
    long long d = (x % (q - 1) + (q - 1)) % (q - 1);

    long long eve_xA = modExp(YA, d, q);
    long long eve_xB = modExp(YB, d, q);

    printf("--- EVE'S CRYPTANALYSIS ---\n");
    printf("Eve computes inverse exponent d = a^-1 mod (q-1) = %lld\n", d);
    printf("Eve extracts Alice secret: YA^d mod q = %lld\n", eve_xA);
    printf("Eve extracts Bob secret:   YB^d mod q = %lld\n\n", eve_xB);

    printf("Answers to Questions:\n");
    printf("1. What happens: The scheme changes from discrete log to a-th root extraction.\n");
    printf("2. Key agreement: Alice and Bob can compute K = (YA * YB) mod q = (xA*xB)^a mod q.\n");
    printf("3. Can Eve break without secrets? YES, Eve also computes (YA * YB) mod q directly.\n");
    printf("4. Can Eve find secrets? YES, since q is prime, Eve computes d = a^-1 mod (q-1)\n");
    printf("   and finds xA = YA^d mod q and xB = YB^d mod q easily.\n");

    return 0;
}
