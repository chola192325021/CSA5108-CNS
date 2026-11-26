#include <stdio.h>

long long gcd(long long a, long long b) {
    while (b) {
        long long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

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
    long long p = 61, q = 53;
    long long n = p * q;
    long long e = 17;

    long long M = 2 * p;
    long long C = modExp(M, e, n);

    printf("Public Parameters: n = %lld, e = %lld\n", n, e);
    printf("Plaintext block M has common factor with n: M = %lld\n", M);
    printf("Transmitted Ciphertext: C = M^e mod n = %lld\n\n", C);

    long long factor = gcd(C, n);

    printf("--- ATTACK WITHOUT PRIVATE KEY ---\n");
    printf("Attacker computes gcd(C, n) = %lld\n", factor);

    long long p_found = factor;
    long long q_found = n / p_found;
    long long phi = (p_found - 1) * (q_found - 1);
    long long x, y;
    extGcd(e, phi, &x, &y);
    long long d = (x % phi + phi) % phi;

    printf("Secret primes revealed: p = %lld, q = %lld\n", p_found, q_found);
    printf("Recovered Private Key: d = %lld\n", d);

    long long decrypted = modExp(C, d, n);
    printf("Decrypted Plaintext:   M = %lld\n\n", decrypted);

    printf("Conclusion:\n");
    printf("YES, this completely breaks RSA. Since n = p*q, any common factor with n\n");
    printf("is a prime factor (p or q). Computing gcd(C, n) instantly factors n and\n");
    printf("allows calculating the private key d, exposing all encrypted blocks.\n");

    return 0;
}
