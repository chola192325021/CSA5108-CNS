#include <stdio.h>
#include <math.h>

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
    long long phi = (p - 1) * (q - 1);
    long long e = 17, d = 2753;

    printf("Original Parameters: n = %lld, e = %lld, leaked d = %lld\n\n", n, e, d);

    long long kPhi = e * d - 1;
    long long k = (kPhi + n - 1) / n;
    long long recPhi = kPhi / k;

    long long s = n - recPhi + 1;
    long long diff = (long long)sqrt(s * s - 4 * n);
    long long recP = (s + diff) / 2;
    long long recQ = (s - diff) / 2;

    printf("--- ATTACK USING LEAKED (e, d) ---\n");
    printf("Estimated k = %lld, Recovered phi(n) = %lld\n", k, recPhi);
    printf("Factored Modulus: p = %lld, q = %lld\n\n", recP, recQ);

    long long e_new = 31;
    long long x, y;
    extGcd(e_new, recPhi, &x, &y);
    long long d_new = (x % recPhi + recPhi) % recPhi;

    printf("Bob creates new public key e_new = %lld with SAME n\n", e_new);
    printf("Attacker calculates Bob's new private key d_new = %lld\n\n", d_new);

    printf("Conclusion:\n");
    printf("It is NOT SAFE. Leaking private key d allows factoring the modulus n.\n");
    printf("Once n is factored, any new private key d_new can be computed immediately.\n");
    printf("Bob MUST generate a new modulus n with brand new prime numbers.\n");

    return 0;
}
