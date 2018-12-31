# Benchmarker-MT
Multithreaded version of the Benchmarker program. Please see Benchmarker's readme for general information about the test.

The current version of this test runs over three iterations: one with 1-second delay between each thread creation, one with two, and one with none (all the 25 threads start at the same time).
Naturally, the lowest score comes on the last part of the test, where many struggle in handling the threads properly.

The current version has a known bug: the total score (supposed to be the average of the three iterations) is always zero, and the program will always crash at the end after giving the scores. 
