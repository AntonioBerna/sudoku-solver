#include "settings.h"
#include "problems.h"

bool validate(unsigned char (*grid)[SIZE][SIZE]);
void solve(unsigned char (*problem)[SIZE][SIZE]);

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

int main(int argc, char **argv) {
	unsigned char (*problem)[SIZE][SIZE];
	int no;

	if (argc != 2) return -1;

	no = atoi(argv[1]);
	if (no < 1 || no > NO_PROBLEMS) return -1;
	problem = problems[no];

	solve(problem);
	print_grid(problem);
	printf("main return value: %d\n", !validate(problem));
	return !validate(problem);
}
