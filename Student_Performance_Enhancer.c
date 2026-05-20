#include <stdio.h>
#include <math.h>

int main() {
    int choice;
    int num_students = 0;
    float sum_before = 0.0;
    float sum_after = 0.0;
    float target_mean, target_sd;

    printf("--- Z-Score Standardization Curve Tool ---\n");
    
    // 1. Selection of Data Source
    printf("1. Use original preset scores (27, 35, 56, 44)\n");
    printf("2. Input custom student scores\n");
    printf("Enter choice (1 or 2): ");
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input token. Exiting.\n");
        return 1;
    }

    // 2. Control Stream Allocator
    if (choice == 1) {
        num_students = 4;
    } else if (choice == 2) {
        printf("\nEnter the number of students: ");
        if (scanf("%d", &num_students) != 1 || num_students <= 0) {
            printf("Invalid student count metric. Exiting.\n");
            return 1;
        }
    } else {
        printf("Invalid selection index. Exiting.\n");
        return 1;
    }

    float original_scores[num_students];
    float final_scores[num_students];

    // 3. Score Array Population Vector
    if (choice == 1) {
        float preset[] = {27.0f, 35.0f, 56.0f, 44.0f};
        for (int i = 0; i < num_students; i++) {
            original_scores[i] = preset[i];
            sum_before += preset[i];
        }
    } else {
        printf("Enter the %d scores:\n", num_students);
        for (int i = 0; i < num_students; i++) {
            printf("Student %d: ", i + 1);
            if (scanf("%f", &original_scores[i]) != 1 || original_scores[i] < 0.0f) {
                printf("Invalid score valuation parsed. Exiting.\n");
                return 1;
            }
            sum_before += original_scores[i];
        }
    }

    float avg_before = sum_before / (float)num_students;

    // 4. Target Matrix Parametric Setup
    printf("\nEnter the desired target class average (e.g., 50.0): ");
    if (scanf("%f", &target_mean) != 1 || target_mean < 0.0f || target_mean > 100.0f) {
        printf("Invalid target mean target parameter.\n");
        return 1;
    }

    printf("Enter the desired target standard deviation spread (e.g., 10.0): ");
    if (scanf("%f", &target_sd) != 1 || target_sd <= 0.0f) {
        printf("Invalid target standard deviation parameter.\n");
        return 1;
    }

    // 5. Sigma Variance Vector Computation
    float variance_sum = 0.0f;
    for (int i = 0; i < num_students; i++) {
        variance_sum += powf(original_scores[i] - avg_before, 2.0f);
    }
    float std_deviation = sqrtf(variance_sum / (float)num_students);

    // Fault Protection Rule against Division by Zero if all scores map identical
    if (std_deviation == 0.0f) {
        std_deviation = 1.0f; 
    }

    // 6. Normalization Matrix Execution Loop
    printf("\n--- Z-Score Mapping Calculations ---\n");
    for (int i = 0; i < num_students; i++) {
        // Calculate deviation offset ratio (Z-Score)
        float z_score = (original_scores[i] - avg_before) / std_deviation;
        
        // Linear map adjustment tracking
        final_scores[i] = target_mean + (z_score * target_sd);
        
        // Boundary enforcement conditions
        if (final_scores[i] > 100.0f) final_scores[i] = 100.0f;
        if (final_scores[i] < 0.0f)   final_scores[i] = 0.0f;
        
        sum_after += final_scores[i];
        printf("Student %d: Raw Score: %5.1f -> New Score: %5.1f (Z-Score: %6.2f)\n", 
               i + 1, original_scores[i], final_scores[i], z_score);
    }

    // 7. Output Metrics Profiling
    float avg_after = sum_after / (float)num_students;
    printf("\n--- Standardization Summary Metrics ---\n");
    printf("Original Sample Mean:       %.2f\n", avg_before);
    printf("Original Standard Dev:      %.2f\n", (std_deviation == 1.0f && variance_sum == 0.0f) ? 0.0f : std_deviation);
    printf("Standardized New Mean:      %.2f (Targeted: %.2f)\n", avg_after, target_mean);

    return 0;
}
