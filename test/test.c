#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "settings.h"
#include "problems.h"

#define RED   "\033[1;31m"
#define GREEN "\033[1;32m"
#define RESET "\033[0m"

bool validate(unsigned char (*grid)[SIZE][SIZE]);
void solve(unsigned char (*problem)[SIZE][SIZE]);

typedef enum {
    TIME_SECONDS,
    TIME_MILLISECONDS,
    TIME_MICROSECONDS
} time_unit_enum;

typedef struct {
    double value;
    time_unit_enum unit;
} time_unit_t;

time_unit_t get_best_time_unit(double seconds) {
    const double milliseconds = seconds * 1e3;
    const double microseconds = seconds * 1e6;

    time_unit_t result;

    if (seconds >= 1.0) {
        result.value = seconds;
        result.unit = TIME_SECONDS;
    } else if (milliseconds >= 1.0) {
        result.value = milliseconds;
        result.unit = TIME_MILLISECONDS;
    } else {
        result.value = microseconds;
        result.unit = TIME_MICROSECONDS;
    }

    return result;
}

int32_t main(void) {
    struct timespec start, end;
    FILE *log_file = fopen("./test/sudoku_results.log", "w");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return EXIT_FAILURE;
    }

    double total_time = 0.0;
    uint8_t valid_problems = 0;

    for (uint8_t i = 1; i < NO_PROBLEMS + 1; ++i) {
        unsigned char (*problem)[SIZE][SIZE] = problems[i];

        clock_gettime(CLOCK_MONOTONIC, &start);
        solve(problem);
        clock_gettime(CLOCK_MONOTONIC, &end);

        double time = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        total_time += time;

        time_unit_t t = get_best_time_unit(time);
        bool is_valid = validate(problem);

        if (i == 1) {
            puts("=================================");
            fprintf(log_file, "=================================\n");
        }

        switch (t.unit) {
            case TIME_SECONDS:
                printf("Problem %d solved in %.9f s.\n", i, t.value);
                fprintf(log_file, "Problem %d solved in %.9f s.\n", i, t.value);
                break;
            case TIME_MILLISECONDS:
                printf("Problem %d solved in %.6f ms.\n", i, t.value);
                fprintf(log_file, "Problem %d solved in %.6f ms.\n", i, t.value);
                break;
            case TIME_MICROSECONDS:
                printf("Problem %d solved in %.3f μs.\n", i, t.value);
                fprintf(log_file, "Problem %d solved in %.3f μs.\n", i, t.value);
                break;
        }

        if (is_valid) {
            ++valid_problems;
            printf("Problem %d is " GREEN "valid" RESET ".\n", i);
        } else {
            printf("Problem %d is " RED "invalid" RESET ".\n", i);
        }
        fprintf(log_file, "Problem %d is %s.\n", i, is_valid ? "valid" : "invalid");

        puts("=================================");
        fprintf(log_file, "=================================\n");
    }

    time_unit_t total_t = get_best_time_unit(total_time);

    if (valid_problems == NO_PROBLEMS) {
        printf(GREEN "Total time: ");
        switch (total_t.unit) {
            case TIME_SECONDS:
                printf("%.9f s." RESET "\n", total_t.value);
                fprintf(log_file, "Total time: %.9f s.\n", total_t.value);
                break;
            case TIME_MILLISECONDS:
                printf("%.6f ms." RESET "\n", total_t.value);
                fprintf(log_file, "Total time: %.6f ms.\n", total_t.value);
                break;
            case TIME_MICROSECONDS:
                printf("%.3f μs." RESET "\n", total_t.value);
                fprintf(log_file, "Total time: %.3f μs.\n", total_t.value);
                break;
        }
    } else {
        printf(RED "Some problems are invalid." RESET "\n");
        fprintf(log_file, "Some problems are invalid.\n");
    }
    puts("=================================");
    fprintf(log_file, "=================================\n");

    fclose(log_file);
    return EXIT_SUCCESS;
}
