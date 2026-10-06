#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

/* Check whether a character is already present */
int exists(char ch, char str[])
{
    int i;

    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ch)
            return 1;
    }

    return 0;
}

/* Create the 5 x 5 Playfair matrix */
void createMatrix(char key[])
{
    char used[26] = "";
    char alphabet[] = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    int i, j, k = 0;

    /* Add unique letters from keyword */
    for (i = 0; key[i] != '\0'; i++)
    {
        char ch = toupper(key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' && !exists(ch, used))
        {
            int len = strlen(used);
            used[len] = ch;
            used[len + 1] = '\0';
        }
    }

    /* Add remaining alphabet letters */
    for (i = 0; alphabet[i] != '\0'; i++)
    {
        char ch = alphabet[i];

        if (!exists(ch, used))
        {
            int len = strlen(used);
            used[len] = ch;
            used[len + 1] = '\0';
        }
    }

    /* Fill matrix */
    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            matrix[i][j] = used[k++];
        }
    }
}

/* Find the row and column of a character */
void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

/* Encrypt a pair of characters */
void encryptPair(char a, char b, char *x, char *y)
{
    int r1, c1, r2, c2;

    findPosition(a, &r1, &c1);
    findPosition(b, &r2, &c2);

    if (r1 == r2)
    {
        /* Same row */
        *x = matrix[r1][(c1 + 1) % 5];
        *y = matrix[r2][(c2 + 1) % 5];
    }
    else if (c1 == c2)
    {
        /* Same column */
        *x = matrix[(r1 + 1) % 5][c1];
        *y = matrix[(r2 + 1) % 5][c2];
    }
    else
    {
        /* Rectangle rule */
        *x = matrix[r1][c2];
        *y = matrix[r2][c1];
    }
}

int main()
{
    char key[100];
    char plaintext[200];
    char prepared[400] = "";
    char ciphertext[400] = "";
    int i, len = 0;

    printf("Enter the keyword: ");
    scanf("%99s", key);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);

    /* Create matrix */
    createMatrix(key);

    printf("\nPlayfair Matrix:\n");

    for (i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    /* Prepare plaintext */
    for (i = 0; plaintext[i] != '\0'; i++)
    {
        char ch = toupper(plaintext[i]);

        if (ch >= 'A' && ch <= 'Z')
        {
            if (ch == 'J')
                ch = 'I';

            prepared[len++] = ch;
        }
    }

    prepared[len] = '\0';

    /* Insert X between repeated letters */
    char temp[400] = "";
    int t = 0;

    for (i = 0; i < len; i++)
    {
        temp[t++] = prepared[i];

        if (i + 1 < len && prepared[i] == prepared[i + 1])
        {
            temp[t++] = 'X';
        }
    }

    /* If length is odd, add X */
    if (t % 2 != 0)
    {
        temp[t++] = 'X';
    }

    temp[t] = '\0';

    /* Encrypt pairs */
    for (i = 0; i < t; i += 2)
    {
        char x, y;

        encryptPair(temp[i], temp[i + 1], &x, &y);

        ciphertext[i] = x;
        ciphertext[i + 1] = y;
    }

    ciphertext[t] = '\0';

    printf("\nPrepared Plaintext: %s\n", temp);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}
