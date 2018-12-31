# Benchmarker-MT
Multithreaded version of the Benchmarker program. Please see Benchmarker's readme for general information about the test.

The current version of this test runs over three iterations: one with 1-second delay between each thread creation, one with two, and one with none (all the 25 threads start at the same time).
Naturally, the lowest score comes on the last part of the test, where many struggle in handling the threads properly.

# Bugs

1. The total score is always 0 [fixed in latest version]
2. The program ALWAYS crashes in the end.
3. [New] Differing outputs in the release and debug config; the program gives horribly bad output in the later (20000 points for the last part). This suggests that there is some massive heap corruption, and I'm trying to fix that bug.
