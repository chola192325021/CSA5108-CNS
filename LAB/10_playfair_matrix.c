#include <stdio.h>
#include <ctype.h>

char mat[5][5] = {"MFHIK", "UNOPQ", "ZVWXY", "ELARG", "DSTBC"};

void pos(char c, int *r, int *col) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (mat[i][j] == c) { *r = i; *col = j; return; }
}

int main() {
    char msg[] = "Must see you over Cadogan West. Coming at once.";
    char p[200], c[200];
    int len = 0;

    for (int i = 0; msg[i]; i++)
        if (isalpha(msg[i])) p[len++] = toupper(msg[i]) == 'J' ? 'I' : toupper(msg[i]);

    int k = 0;
    for (int i = 0; i < len; i += 2) {
        c[k++] = p[i];
        if (i + 1 == len) { c[k++] = 'X'; break; }
        if (p[i] == p[i + 1]) { c[k++] = 'X'; i--; }
        else c[k++] = p[i + 1];
    }
    c[k] = '\0';

    printf("Plaintext: %s\nPrepared:  %s\nCipher:    ", msg, c);
    for (int i = 0; i < k; i += 2) {
        int r1, c1, r2, c2;
        pos(c[i], &r1, &c1);
        pos(c[i + 1], &r2, &c2);
        if (r1 == r2) printf("%c%c", mat[r1][(c1 + 1) % 5], mat[r2][(c2 + 1) % 5]);
        else if (c1 == c2) printf("%c%c", mat[(r1 + 1) % 5][c1], mat[(r2 + 1) % 5][c2]);
        else printf("%c%c", mat[r1][c2], mat[r2][c1]);
    }
    printf("\n");
    return 0;
}
