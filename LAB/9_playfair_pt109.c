#include <stdio.h>
#include <string.h>
#include <ctype.h>

char mat[5][5];

void generateMatrix(const char *key) {
    int vis[26] = {0};
    vis['J' - 'A'] = 1;
    int r = 0, c = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (isalpha(ch) && !vis[ch - 'A']) {
            vis[ch - 'A'] = 1;
            mat[r][c++] = ch;
            if (c == 5) { c = 0; r++; }
        }
    }

    for (int i = 0; i < 26; i++) {
        if (!vis[i]) {
            mat[r][c++] = 'A' + i;
            if (c == 5) { c = 0; r++; }
        }
    }
}

void findPos(char ch, int *r, int *c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (mat[i][j] == ch) {
                *r = i;
                *c = j;
                return;
            }
        }
    }
}

void decryptPlayfair(char *text) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPos(text[i], &r1, &c1);
        findPos(text[i + 1], &r2, &c2);

        if (r1 == r2) {
            text[i] = mat[r1][(c1 + 4) % 5];
            text[i + 1] = mat[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            text[i] = mat[(r1 + 4) % 5][c1];
            text[i + 1] = mat[(r2 + 4) % 5][c2];
        } else {
            text[i] = mat[r1][c2];
            text[i + 1] = mat[r2][c1];
        }
    }
}

int main() {
    char key[] = "ROYAL NEW ZEALAND NAVY";
    char cipher[] = 
        "KXJEYUREBEZWEHEWRYTUHEYFS"
        "KREHEGOYFIWTTTUOLKSYCAJPO"
        "BOTEIZONTXBYBNTGONEYCUZWR"
        "GDSONSXBOUYWRHEBAAHYUSEDQ";

    generateMatrix(key);

    printf("Keyword: %s\n\n", key);
    printf("5x5 Playfair Key Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("PT-109 Ciphertext:\n%s\n\n", cipher);

    decryptPlayfair(cipher);
    printf("Decrypted PT-109 Message:\n%s\n", cipher);

    return 0;
}
