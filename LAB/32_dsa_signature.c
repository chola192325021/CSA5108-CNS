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

long long modInv(long long a, long long m) {
    long long x, y;
    extGcd(a, m, &x, &y);
    return (x % m + m) % m;
}

int main() {
    long long p = 283, q = 47, g = 60;
    long long x = 24;
    long long hm = 19;

    long long k1 = 15;
    long long r1 = modExp(g, k1, p) % q;
    long long s1 = (modInv(k1, q) * (hm + x * r1)) % q;

    long long k2 = 25;
    long long r2 = modExp(g, k2, p) % q;
    long long s2 = (modInv(k2, q) * (hm + x * r2)) % q;

    printf("DSA Parameter: p = %lld, q = %lld, g = %lld\n", p, q, g);
    printf("Message Hash H(M) = %lld, Private Key x = %lld\n\n", hm, x);

    printf("Signature 1 (with k1 = %lld): r1 = %lld, s1 = %lld\n", k1, r1, s1);
    printf("Signature 2 (with k2 = %lld): r2 = %lld, s2 = %lld\n\n", k2, r2, s2);

    long long rsa_d = 2753, rsa_n = 3599;
    long long rsa_sig1 = modExp(hm, rsa_d, rsa_n);
    long long rsa_sig2 = modExp(hm, rsa_d, rsa_n);

    printf("RSA Signature 1: %lld\n", rsa_sig1);
    printf("RSA Signature 2: %lld (Always identical)\n\n", rsa_sig2);

    printf("Implications of this difference:\n");
    printf("1. Randomized Signatures: In DSA, identical messages produce different valid\n");
    printf("   signatures, preventing eavesdroppers from linking identical signed messages.\n");
    printf("2. Critical Hazard of k: In DSA, k must be truly random and never repeated.\n");
    printf("   If the same k is used twice, an attacker can directly extract the private key x.\n");
    printf("3. In RSA, signature generation is deterministic and does not require a random nonce.\n");

    return 0;
}
