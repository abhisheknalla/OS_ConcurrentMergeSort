# OS_ConcurrentMergeSort

Problem
Concurrent Merge Sort
1. Given a number n and n numbers, sort the numbers using Merge Sort.
2. Recursively make two child processes, one for the left half, one for the right half. If the number of
elements in the array for a process is less than 5, perform a selection sort.
3. The parent of the two children then merges the result and returns back to the parent and so on.
4. Compare the performance of the merge sort with a normal merge sort implementation and make a
report.
5. You must use the shmget, shmat functions as taught in the tutorial.

Bonus:
6. Use threads in place of processes for the Problem. Add the performance comparison to the above report.


Solution Explanation:
# Code Report for Merge Sort:

Timing the code and comparing its performance with the traditional sequential code shows that the sequential sort performs better.
When, say left child, accesses the left array, the array is loaded into the cache of a processor. Now when the right array is 

accessed (because of concurrent accesses), there is a cache miss since the cache is filled with left segment and then right 

segment is copied to the cache memory. This to-and-fro process continues and it degrades the performance to such a level that 

it performs poorer than the sequential code.

There are ways to reduce the cache misses by controlling the workflow of the code. But they cannot be avoided completely.

# Code Report for Merge Sort (using threads):

Timing the code and comparing its performance with the traditional sequential code shows that the sequential sort performs 

better.

When, say left child, accesses the left array, the array is loaded into the cache of a processor. Now when the right array is 

accessed (because of concurrent accesses), there is a cache miss since the cache is filled with left segment and then right 

segment is copied to the cache memory. This to-and-fro process continues and it degrades the performance to such a level that 

it performs poorer than the sequential code.

There are ways to reduce the cache misses by controlling the workflow of the code. But they cannot be avoided completely.

The one with threads works slower than the code using fork().


