#include <stdio.h>
#include <ctype.h>

int gcd(int x, int y) {
    while (y != 0) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return x;
}

int modInverse(int a) {
    for (int x = 1; x < 26; x++) {
        if ((a * x) % 26 == 1) return x;
    }
    return -1;
}

void encrypt(char *str, int a, int b) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            str[i] = ((a * (str[i] - 'A') + b) % 26) + 'A';
        } else if (islower(str[i])) {
            str[i] = ((a * (str[i] - 'a') + b) % 26) + 'a';
        }
    }
}

void decrypt(char *str, int a, int b) {
    int a_inv = modInverse(a);
    if (a_inv == -1) return;
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) {
            str[i] = ((a_inv * (str[i] - 'A' - b + 26)) % 26 + 26) % 26 + 'A';
        } else if (islower(str[i])) {
            str[i] = ((a_inv * (str[i] - 'a' - b + 26)) % 26 + 26) % 26 + 'a';
        }
    }
}

int main() {
    printf("a. Limitations on b: b can be any integer from 0 to 25.\n\n");

    printf("b. Values of 'a' NOT allowed (gcd(a, 26) != 1):\n");
    for (int a = 0; a < 26; a++) {
        if (gcd(a, 26) != 1) printf("%d ", a);
    }
    printf("\n\nValues of 'a' allowed (gcd(a, 26) == 1):\n");
    for (int a = 0; a < 26; a++) {
        if (gcd(a, 26) == 1) printf("%d ", a);
    }
    printf("\n\n");

    char str[100];
    int a, b;
    printf("Enter string: ");
    scanf("%[^\n]", str);
    printf("Enter key (a and b): ");
    scanf("%d %d", &a, &b);

    if (gcd(a, 26) != 1) {
        printf("Invalid key 'a': gcd(a, 26) must be 1.\n");
        return 1;
    }

    encrypt(str, a, b);
    printf("Encrypted: %s\n", str);

    decrypt(str, a, b);
    printf("Decrypted: %s\n", str);

    return 0;
}
