#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char engOrder[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
const double f[26] = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.1, 2.0, 0.1};

typedef struct {
    char plain[300];
    double score;
} Result;

int main() {
    char cipher[300] = "GDUC QDF HEDMY XEN VBEDL MEGN GDUC QDF";
    char in[300];
    int topN = 10, counts[26] = {0}, cOrder[26];

    printf("Enter ciphertext: ");
    if (fgets(in, sizeof(in), stdin) && in[0] != '\n') {
        in[strcspn(in, "\n")] = '\0';
        strcpy(cipher, in);
    }
    printf("Enter number of top plaintexts: ");
    if (scanf("%d", &topN) != 1 || topN < 1) topN = 10;

    for (int i = 0; cipher[i]; i++)
        if (isalpha(cipher[i])) counts[toupper(cipher[i]) - 'A']++;

    for (int i = 0; i < 26; i++) cOrder[i] = i;
    for (int i = 0; i < 25; i++)
        for (int j = i + 1; j < 26; j++)
            if (counts[cOrder[j]] > counts[cOrder[i]]) {
                int t = cOrder[i]; cOrder[i] = cOrder[j]; cOrder[j] = t;
            }

    Result res[20];
    int totalRes = 0;

    for (int s = 0; s < 10 && totalRes < 20; s++) {
        char map[26];
        char curEng[27];
        strcpy(curEng, engOrder);
        if (s == 1) { char t = curEng[0]; curEng[0] = curEng[1]; curEng[1] = t; }
        if (s == 2) { char t = curEng[2]; curEng[2] = curEng[3]; curEng[3] = t; }
        if (s == 3) { char t = curEng[4]; curEng[4] = curEng[5]; curEng[5] = t; }
        if (s == 4) { char t = curEng[1]; curEng[1] = curEng[2]; curEng[2] = t; }
        if (s == 5) { char t = curEng[6]; curEng[6] = curEng[7]; curEng[7] = t; }
        if (s == 6) { char t = curEng[0]; curEng[0] = curEng[2]; curEng[2] = t; }
        if (s == 7) { char t = curEng[3]; curEng[3] = curEng[4]; curEng[4] = t; }
        if (s == 8) { char t = curEng[8]; curEng[8] = curEng[9]; curEng[9] = t; }
        if (s == 9) { char t = curEng[5]; curEng[5] = curEng[6]; curEng[6] = t; }

        for (int i = 0; i < 26; i++) map[cOrder[i]] = curEng[i];

        res[totalRes].score = 0;
        for (int i = 0; cipher[i]; i++) {
            if (isalpha(cipher[i])) {
                char p = isupper(cipher[i]) ? map[cipher[i] - 'A'] : tolower(map[cipher[i] - 'a']);
                res[totalRes].plain[i] = p;
                res[totalRes].score += f[toupper(p) - 'A'];
            } else {
                res[totalRes].plain[i] = cipher[i];
            }
        }
        res[totalRes].plain[strlen(cipher)] = '\0';
        totalRes++;
    }

    for (int i = 0; i < totalRes - 1; i++)
        for (int j = i + 1; j < totalRes; j++)
            if (res[j].score > res[i].score) {
                Result t = res[i]; res[i] = res[j]; res[j] = t;
            }

    printf("\nTop %d Candidate Plaintexts:\n", topN);
    for (int i = 0; i < topN && i < totalRes; i++)
        printf("%2d. (Score: %6.1f) %s\n", i + 1, res[i].score, res[i].plain);

    return 0;
}
