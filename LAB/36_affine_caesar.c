#include <stdio.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int modInv(int a, int m) {
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1) return x;
    return -1;
}

int main() {
    printf("Demonstrating Non-One-to-One Mapping (a = 2, b = 3):\n");
    int a_bad = 2, b_bad = 3;
    printf("E([%d, %d], 0)  = (%d*0 + %d) mod 26  = %d ('%c')\n", a_bad, b_bad, a_bad, b_bad, (a_bad * 0 + b_bad) % 26, (a_bad * 0 + b_bad) % 26 + 'A');
    printf("E([%d, %d], 13) = (%d*13 + %d) mod 26 = %d ('%c')\n", a_bad, b_bad, a_bad, b_bad, (a_bad * 13 + b_bad) % 26, (a_bad * 13 + b_bad) % 26 + 'A');
    printf("Collision: Both 0 and 13 map to 3, so decryption is impossible.\n\n");

    int a = 7, b = 3;
    printf("Valid Key (gcd(%d, 26) = %d):\n", a, gcd(a, 26));
    char str[] = "HELLO AFFINE";
    printf("Original:  %s\n", str);

    printf("Encrypted: ");
    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            int p = toupper(str[i]) - 'A';
            str[i] = ((a * p + b) % 26) + 'A';
        }
        printf("%c", str[i]);
    }
    printf("\n");

    int a_inv = modInv(a, 26);
    printf("Decrypted: ");
    for (int i = 0; str[i]; i++) {
        if (isalpha(str[i])) {
            int c = str[i] - 'A';
            str[i] = ((a_inv * (c - b + 26)) % 26) + 'A';
        }
        printf("%c", str[i]);
    }
    printf("\n");

    return 0;
}
