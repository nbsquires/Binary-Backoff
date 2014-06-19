Binary-Backoff
==============

The purpose of a backoff algorithm is to avoid collisions in networks when more than one station wishes to send a frame in a channel. In order to do this, collision detection must be handled during a timeslot, and if a collision is detected during this time slot, any sort of backoff algorithm is used to compute the next time slot colliding stations must wait for in order to retransmit. Colliding stations are usually assigned a random value from zero to the number returned by the backoff algorithm.

==============

AUTHOR: Natasha Squires

This project was tested on Ubuntu 11.10

**FILE MANIFEST:**

*header files:*

* bckff.h - Just a header file that includes some structs and function protocols

*C files:*

* backoff.c - Source code for the simulation of the backoff algorithms.
 
*shell scripts:*

	*backoff.sh - a shell script that runs the backoff program how ever many times you like. I only really
		      used this for testing/data collection.

*Other:*

* backoff - to execute the C code
* makefile - compiles the C source code
* Report.pdf - my report
* results.dat - a file that printed out the final time slot when the program was run. This was used for data collection. The code that writes to the file is commented out.

**How to run**:

Simply type "make" into the terminal.

In order to run the program you must type ./backoff, and then the number of stations, and which backoff
algorithm.

* e.g. to run the program with 10 stations using the binary exponential backoff:
	./backoff 10 bin
* e.g. to run the program with 5 stations using the fibonacci backoff:
	./backoff 5 fib

**Issues?**

No known issues.
