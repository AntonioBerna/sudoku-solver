# Bitmasking + Backtracking Benchmarks

The following table shows the hardware and software specifications regarding my setup:

| OS                    | CPU                 | RAM       | Toolchain     |
| :---:                 | :---:               | :---:     | :---:         |
| Manjaro Linux v25.0.0 | Intel Core i7-8650U | 32GB DDR4 | clang v19.1.7 |

You can use `make test` command to generate the executable called `test`, inside `bin/` directory, and then you will need to use the `./bin/test` command to run the program. The output will be the following:

```
=================================
Problem 1 solved in 13.064 μs.
Problem 1 is valid.
=================================
Problem 2 solved in 4.071 μs.
Problem 2 is valid.
=================================
Problem 3 solved in 531.553 μs.
Problem 3 is valid.
=================================
Problem 4 solved in 23.155 μs.
Problem 4 is valid.
=================================
Problem 5 solved in 8.589 μs.
Problem 5 is valid.
=================================
Problem 6 solved in 9.722 μs.
Problem 6 is valid.
=================================
Problem 7 solved in 17.542 μs.
Problem 7 is valid.
=================================
Problem 8 solved in 19.684 μs.
Problem 8 is valid.
=================================
Problem 9 solved in 10.520 μs.
Problem 9 is valid.
=================================
Total time: 637.900 μs.
=================================
```

!!! Note
    The `test` program generate the `test/sudoku_results.log` file with the results of the tests.
