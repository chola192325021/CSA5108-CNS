#include <stdio.h>

int extGcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extGcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

int main() {
    int e = 31, n = 3599;
    int p = 0, q = 0;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            p = i;
            q = n / i;
            break;
        }
    }

    int phi = (p - 1) * (q - 1);
    int x, y;
    extGcd(e, phi, &x, &y);
    int d = (x % phi + phi) % phi;

    printf("Public Key:  e = %d, n = %d\n", e, n);
    printf("Factoring n: p = %d, q = %d\n", p, q);
    printf("Euler's Totient phi(n) = (%d-1)*(%d-1) = %d\n", p, q, phi);
    printf("Private Key: d = %d\n\n", d);

    printf("Verification:\n");
    printf("(e * d) mod phi(n) = (%d * %d) mod %d = %d\n", e, d, phi, (e * d) % phi);

    long long m = 123;
    long long c = 1, rec = 1;
    for (int i = 0; i < e; i++) c = (c * m) % n;
    for (int i = 0; i < d; i++) rec = (rec * c) % n;

    printf("Test Message m = %lld -> Cipher c = %lld -> Recovered m = %lld\n", m, c, rec);

    return 0;
}
