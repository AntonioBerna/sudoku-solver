# sudoku-solver

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/1c00f9216d36419b86f0584dd6dafbc4)](https://app.codacy.com/gh/AntonioBerna/sudoku-solver/dashboard?utm_source=gh&utm_medium=referral&utm_content=&utm_campaign=Badge_grade)

> [!NOTE]
> The `src/solver.c` file contains a detailed explanation of the algorithm I used to solve the Sudoku.

> [!NOTE]
> The result of the benchmarks is saved in the `benchmarks-results.txt` file.

## mini docs

If you want to try my code I must first clone the repository using the command:

```
git clone https://github.com/AntonioBerna/sudoku-solver.git
```

Now you can use the `make` command to generate the executable called  `sudoku` and then you will need to use the `./sudoku n` command to run the program, where `n` is a number between 1 and 9 (depending on the Sudoku to be solved in `problems.h` file). For example, the command `./sudoku 3` generates the following output:

```
-------------------------
| 4 9 6 | 1 7 3 | 8 2 5 | 
| 2 7 8 | 5 9 6 | 4 1 3 | 
| 3 1 5 | 8 4 2 | 6 7 9 | 
-------------------------
| 9 8 1 | 3 5 7 | 2 6 4 | 
| 5 4 3 | 2 6 8 | 1 9 7 | 
| 6 2 7 | 9 1 4 | 3 5 8 | 
-------------------------
| 1 6 4 | 7 3 5 | 9 8 2 | 
| 7 3 2 | 6 8 9 | 5 4 1 | 
| 8 5 9 | 4 2 1 | 7 3 6 | 
-------------------------
main return value: 0
```

If you want to add more sudoku you will have to fix the code present in the `problems.h` file (adding new matrices) and also the `NO_PROBLEMS` macro present in the `settings.h` file. Please don't forget to update the following sudoku matrix (present at the bottom of the `problems.h` file):

```c
static unsigned char (*problems[NO_PROBLEMS + 1])[SIZE][SIZE] = {
    NULL,
    &problem1, &problem2, &problem3,
    &problem4, &problem5, &problem6,
    &problem7, &problem8, &problem9
};
```

That's it!

## hyperfine benchmarks

There is a script in the repository called `benchmarks.sh` that can be used to test the solving of multiple Sudoku puzzles. To use the `benchmarks.sh` script you can use the `./benchmarks.sh` command or the `sh benchmarks.sh` command. What you see below are the results I get using the [hyperfine](https://github.com/sharkdp/hyperfine) library (written in Rust and Python):

| Command | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 1` | 1.0 ± 0.6 | 0.4 | 2.9 | 1.00 |

| Command | Mean [µs] | Min [µs] | Max [µs] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 2` | 638.3 ± 83.8 | 487.3 | 2038.0 | 1.00 |

| Command | Mean [ms] | Min [ms] | Max [ms] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 3` | 3.6 ± 0.4 | 3.1 | 6.2 | 1.00 |

| Command | Mean [µs] | Min [µs] | Max [µs] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 4` | 807.1 ± 182.6 | 524.7 | 2376.4 | 1.00 |

| Command | Mean [µs] | Min [µs] | Max [µs] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 5` | 646.4 ± 149.3 | 444.7 | 2655.0 | 1.00 |

| Command | Mean [µs] | Min [µs] | Max [µs] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 6` | 646.0 ± 109.9 | 451.2 | 2131.2 | 1.00 |

| Command | Mean [µs] | Min [µs] | Max [µs] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 7` | 794.7 ± 273.9 | 474.1 | 2546.8 | 1.00 |

| Command | Mean [µs] | Min [µs] | Max [µs] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 8` | 826.9 ± 299.8 | 533.7 | 3008.3 | 1.00 |

| Command | Mean [µs] | Min [µs] | Max [µs] | Relative |
|:---|---:|---:|---:|---:|
| `./sudoku 9` | 622.0 ± 110.1 | 476.9 | 2386.1 | 1.00 |


