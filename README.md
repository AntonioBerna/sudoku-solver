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

```
Benchmark 1: ./sudoku 1
  Time (mean ± σ):       1.0 ms ±   0.6 ms    [User: 0.7 ms, System: 0.2 ms]
  Range (min … max):     0.4 ms …   2.9 ms    3664 runs
 
Benchmark 1: ./sudoku 2
  Time (mean ± σ):     638.3 µs ±  83.8 µs    [User: 472.7 µs, System: 63.4 µs]
  Range (min … max):   487.3 µs … 2038.0 µs    4801 runs
 
Benchmark 1: ./sudoku 3
  Time (mean ± σ):       3.6 ms ±   0.4 ms    [User: 3.1 ms, System: 0.3 ms]
  Range (min … max):     3.1 ms …   6.2 ms    796 runs
 
Benchmark 1: ./sudoku 4
  Time (mean ± σ):     807.1 µs ± 182.6 µs    [User: 616.1 µs, System: 78.9 µs]
  Range (min … max):   524.7 µs … 2376.4 µs    3984 runs
 
Benchmark 1: ./sudoku 5
  Time (mean ± σ):     841.1 µs ± 405.2 µs    [User: 598.7 µs, System: 115.1 µs]
  Range (min … max):   495.7 µs … 3852.2 µs    3470 runs
 
Benchmark 1: ./sudoku 6
  Time (mean ± σ):     675.2 µs ± 233.9 µs    [User: 506.1 µs, System: 69.2 µs]
  Range (min … max):   451.2 µs … 2815.7 µs    4879 runs
 
Benchmark 1: ./sudoku 7
  Time (mean ± σ):     794.7 µs ± 273.9 µs    [User: 594.0 µs, System: 87.7 µs]
  Range (min … max):   482.1 µs … 2546.8 µs    4238 runs
 
Benchmark 1: ./sudoku 8
  Time (mean ± σ):       1.1 ms ±   0.7 ms    [User: 0.8 ms, System: 0.2 ms]
  Range (min … max):     0.5 ms …   2.8 ms    1272 runs
 
Benchmark 1: ./sudoku 9
  Time (mean ± σ):     895.0 µs ± 570.8 µs    [User: 611.3 µs, System: 153.0 µs]
  Range (min … max):   458.3 µs … 2484.8 µs    4972 runs
```
