Authors: Jeffrey Jordan
Creation: 2/12/2020
File: Sudoku.c

Program uses multithreading to quickly check every row, collumn, and 3x3 square of a sudoku board for validity.
Takes in a board from a text file, reads it in, then performs the threads and checks.

Requirements:
User will need a text file in the following format:
1 2 3 4 5 6 7 8 9
1 1 1 1 1 1 1 1 1
....
and so on until a 9x9 row and collumn table could be filled.

Instructions for use:

Text file must be read in at compilation as a command argument.
i.e.
./file text.txt

Program handles everything else.

Known bugs:
There are no known bugs upon release.

Challenges during development:
There was an abundance of example code, videos, and documentation across the internet, as well as much
of the thread code provided by Professor. We had one issue with figuring out return values to a void pointer,
but a reference to linux manual pages solved the issue.

Program completion:
To the best of our current knowledge, the program has met all requirements for safe execution.
