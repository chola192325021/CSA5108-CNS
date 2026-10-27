#include <stdio.h>
#include <math.h>

int main() {
    double total = 1.0, log2Total = 0.0;
    for (int i = 1; i <= 25; i++) {
        total *= i;
        log2Total += log2(i);
    }
    printf("Total keys: %.4e (approx 2^%.0f)\n", total, log2Total);
    printf("Effectively unique keys (25!/25): %.4e (approx 2^%.0f)\n", total / 25.0, log2Total - log2(25.0));
    return 0;
}
