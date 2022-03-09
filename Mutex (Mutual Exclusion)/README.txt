Author: Jeffrey Jordan
Date: 2/20/2020
File: mutex.c

Description:
Program creates a total of 4 threads to split evenly among two bank functions (withdraw and deposit).
Using mutex, the threads will lock and unlock the critical region so that no two threads can act upon the global balance.

Things to know:
Program will start itself upon compiling and executing. No further action is required.

Known bugs:
There is a possible bug with the thread ID's. The number for them is quite large. I wasn't able to find any documentation on whether or not this was normal.

Problems during development:
I had an issue with printing the ID. I wanted to use a pointer to an address to get rid of compiler warnings. I emailed my professor about it, and he said to cast it as an integer.
