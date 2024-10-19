FROM alpine:latest

RUN apk add --no-cache \
    build-base \
    && mkdir /sudoku-solver

COPY . /sudoku-solver
WORKDIR /sudoku-solver

RUN make

ENTRYPOINT [ "./sudoku" ]