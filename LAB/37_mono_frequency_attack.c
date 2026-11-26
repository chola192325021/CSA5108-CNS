#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char eng[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";
const double weights[26] = {8.2, 1.5, 2.8, 4.3, 12.7, 2.2, 2.0, 6.1, 7.0, 0.2, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0, 6.3, 9.1, 2.8, 1.0, 2.4, 0.1, 2.0, 0.1};

typedef struct {
    char text[300];
    double score;
} Cand;

int main() {
    char cipher[300] = "GDUC QDF HEDMY XEN VBEDL MEGN GDUC QDF", in[300];
    int topN = 10, counts[26] = {0}, order[26];

    printf("Enter ciphertext: ");
    if (fgets(in, sizeof(in), stdin) && in[0] != '\n') {
        in[strcspn(in, "\n")] = '\0';
        strcpy(cipher, in);
    }
    printf("Give me the top N possible plaintexts (default 10): ");
    if (scanf("%d", &topN) != 1 || topN < 1) topN = 10;

    for (int i = 0; cipher[i]; i++)
        if (isalpha(cipher[i])) counts[toupper(cipher[i]) - 'A']++;

    for (int i = 0; i < 26; i++) order[i] = i;
    for (int i = 0; i < 25; i++)
        for (int j = i + 1; j < 26; j++)
            if (counts[order[j]] > counts[order[i]]) {
                int t = order[i]; order[i] = order[j]; order[j] = t;
            }

    Cand list[15];
    int swaps[10][2] = {{0,0}, {0,1}, {2,3}, {4,5}, {1,2}, {6,7}, {0,2}, {3,4}, {8,9}, {5,6}};

    for (int s = 0; s < 10; s++) {
        char cur[27];
        strcpy(cur, eng);
        char t = cur[swaps[s][0]];
        cur[swaps[s][0]] = cur[swaps[s][1]];
        cur[swaps[s][1]] = t;

        char map[26];
        for (int i = 0; i < 26; i++) map[order[i]] = cur[i];

        list[s].score = 0;
        for (int i = 0; cipher[i]; i++) {
            if (isalpha(cipher[i])) {
                char p = isupper(cipher[i]) ? map[cipher[i] - 'A'] : tolower(map[cipher[i] - 'a']);
                list[s].text[i] = p;
                list[s].score += weights[toupper(p) - 'A'];
            } else list[s].text[i] = cipher[i];
        }
        list[s].text[strlen(cipher)] = '\0';
    }

    for (int i = 0; i < 9; i++)
        for (int j = i + 1; j < 10; j++)
            if (list[j].score > list[i].score) {
                Cand tc = list[i]; list[i] = list[j]; list[j] = tc;
            }

    printf("\nTop %d Possible Plaintexts (in order of likelihood):\n", topN);
    for (int i = 0; i < topN && i < 10; i++)
        printf("%2d. (Score: %6.1f) %s\n", i + 1, list[i].score, list[i].text);

    return 0;
}
