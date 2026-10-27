#include <stdio.h>
#include <ctype.h>

int mod(int x) { int r = x % 26; return r < 0 ? r + 26 : r; }

int main() {
    int K[2][2] = {{9, 4}, {5, 7}}, invK[2][2] = {{5, 12}, {15, 25}};
    char msg[] = "meet me at the usual place at ten rather than eight oclock";
    char p[200], c[200], d[200];
    int len = 0;

    for (int i = 0; msg[i]; i++)
        if (isalpha(msg[i])) p[len++] = toupper(msg[i]);
    if (len % 2) p[len++] = 'X';
    p[len] = '\0';

    printf("Key K: [[9,4],[5,7]], Inverse K^-1: [[5,12],[15,25]]\n\nEncrypted pairs:\n");
    for (int i = 0; i < len; i += 2) {
        int p1 = p[i] - 'A', p2 = p[i + 1] - 'A';
        c[i] = mod(K[0][0] * p1 + K[0][1] * p2) + 'A';
        c[i + 1] = mod(K[1][0] * p1 + K[1][1] * p2) + 'A';
        printf("%c%c -> %c%c  ", p[i], p[i + 1], c[i], c[i + 1]);
    }
    c[len] = '\0';
    printf("\n\nCiphertext: %s\n\nDecrypted pairs:\n", c);

    for (int i = 0; i < len; i += 2) {
        int c1 = c[i] - 'A', c2 = c[i + 1] - 'A';
        d[i] = mod(invK[0][0] * c1 + invK[0][1] * c2) + 'A';
        d[i + 1] = mod(invK[1][0] * c1 + invK[1][1] * c2) + 'A';
        printf("%c%c -> %c%c  ", c[i], c[i + 1], d[i], d[i + 1]);
    }
    d[len] = '\0';
    printf("\n\nPlaintext: %s\n", d);
    return 0;
}
