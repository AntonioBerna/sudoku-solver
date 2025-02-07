FROM alpine:3.20

RUN apk add --no-cache \
    build-base \
    clang \
    && mkdir /sudoku-solver

COPY . /sudoku-solver
WORKDIR /sudoku-solver

RUN make

ENTRYPOINT [ "./bin/sudoku" ]