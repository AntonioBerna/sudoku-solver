#include "settings.h"
#include "problems.h"

bool validate(unsigned char (*grid)[SIZE][SIZE]);
void solve(unsigned char (*problem)[SIZE][SIZE]);

#define BASE 10
static bool to_uint8(const char *buffer, uint8_t *value) {
    char *endptr;
    errno = 0;
    *value = (uint8_t)strtoul(buffer, &endptr, BASE);
    return !(errno == ERANGE || endptr == buffer || (*endptr && *endptr != '\n') || *value < 1 || *value > NO_PROBLEMS);
}
#undef BASE

static void print_grid(unsigned char (*problem)[SIZE][SIZE]) {
	printf("-------------------------\n");
	for (uint16_t i = 0; i < SIZE; ++i) {
		printf("| ");
		for (uint16_t j = 0; j < SIZE; ++j) {
			printf("%d %s", (*problem)[i][j], j % HALF_SIZE == 2 ? "| " : "");
		}
		printf("\n");
		if (i % HALF_SIZE == 2) printf("-------------------------\n");
	}
}

int32_t main(int32_t argc, const char **argv) {
	unsigned char (*problem)[SIZE][SIZE];
	uint8_t no;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <problem number>\n", *argv);
		exit(EXIT_FAILURE);
	}

	if (!to_uint8(argv[1], &no)) {
		fprintf(stderr, "Invalid problem number.\n");
		exit(EXIT_FAILURE);
	}

	problem = problems[no];

	solve(problem);
	print_grid(problem);

	bool is_valid = !validate(problem);
	printf("main return value: %d\n", is_valid);
	return is_valid;
}
