#include "settings.h"

#define ROW_DISPLACEMENT(i, j) (j * HALF_SIZE % SIZE + i / HALF_SIZE)
#define COL_DISPLACEMENT(i, j) (j * HALF_SIZE / HALF_SIZE - j % HALF_SIZE + i % HALF_SIZE)
bool validate(unsigned char (*grid)[SIZE][SIZE]) {
	uint16_t chk[HALF_SIZE * SIZE] = { 0 };
	uint16_t sum = 0;

	for (uint16_t i = 0; i < SIZE; ++i) {
		for (uint16_t j = 0; j < SIZE; ++j) {
			chk[j] |= 1 << ((*grid)[j][i] - 1);
			chk[SIZE + j] |= 1 << ((*grid)[i][j] - 1);
			chk[(2 * SIZE) + j] |= 1 << ((*grid)[ROW_DISPLACEMENT(i, j)][COL_DISPLACEMENT(i, j)] - 1);
		}
	}

	for (uint16_t i = 0; i < HALF_SIZE * SIZE; ++i) sum += chk[i];
	// printf("sum = %u\n", sum);
	return sum == 13797;
}
#undef ROW_DISPLACEMENT
#undef COL_DISPLACEMENT
