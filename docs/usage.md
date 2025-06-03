# Usage

## Classic way

If you want to try my code you need to clone the repository using the command:

```
git clone https://github.com/AntonioBerna/sudoku-solver.git
```

Now you can use the `make` command to generate the executable called `sudoku`, inside `bin/` directory, and then you will need to use the `./bin/sudoku <problem number>` command to run the program, where `<problem number>` is a number between 1 and 9 (depending on the Sudoku to be solved in `include/problems.h` file). For example, the command `./bin/sudoku 3` generates the following output:

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

If you want to add more sudoku you will have to fix the code present in the `include/problems.h` file (adding new matrices) and also the `NO_PROBLEMS` macro present in the `include/settings.h` file. Please don't forget to update the following sudoku matrix (present at the bottom of the `include/problems.h` file):

```c linenums="1"
static unsigned char (*problems[NO_PROBLEMS + 1])[SIZE][SIZE] = {
    NULL,
    &problem1, &problem2, &problem3,
    &problem4, &problem5, &problem6,
    &problem7, &problem8, &problem9
};
```

Finally, if you want to remove the executable and object files, you can use the `make clean` command.

That's it!

## Docker way

Another solution is to download my docker image from the `Docker Hub` registry using the following command:

```
docker pull antonioberna/sudoku-solver
```

Now you can run the container using the following command:

```
docker run --rm antonioberna/sudoku-solver 3
```

!!! Note
    The command above will solve the third Sudoku present in the `include/problems.h` file. If you want to solve another Sudoku, just change the number `3` to another number between 1 and 9.

Finally, if you want to remove the image from your machine, you can use the `docker rmi antonioberna/sudoku-solver` command.