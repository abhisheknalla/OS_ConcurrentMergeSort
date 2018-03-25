# OS_ConcurrentMergeSort

Problem
Concurrent Merge Sort
 Given a number n and n numbers, sort the numbers using Merge Sort.
 Recursively make two child processes, one for the left half, one for the right half. If the number of
 elements in the array for a process is less than 5, perform a selection sort.
The parent of the two children then merges the result and returns back to the parent and so on.
 Compare the performance of the merge sort with a normal merge sort implementation and make a
 report.
You must use the shmget, shmat functions as taught in the tutorial.

Bonus:
 Use threads in place of processes for the Problem. Add the performance comparison to the above report.
