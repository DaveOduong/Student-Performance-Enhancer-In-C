#include <stdio.h>

int main() {
    int scores[] = {27, 35, 56, 44};
    int num_students = 4;
    int threshold = 50;
    int bonus = 5;
    int sum_before = 0, sum_after = 0;

    // Calculate sum before bonus
    for (int i = 0; i < num_students; i++) {
        sum_before += scores[i];
    }

    // Apply bonus if needed
    for (int i = 0; i < num_students; i++) {
        if (scores[i] < threshold) {
            scores[i] += bonus;
        }
        sum_after += scores[i];
    }

    // Calculate averages
    float avg_before = (float)sum_before / num_students;
    float avg_after = (float)sum_after / num_students;

    // Print results
    printf("Average before bonus: %.2f\n", avg_before);
    printf("Average after bonus: %.2f\n", avg_after);

    return 0;
}
