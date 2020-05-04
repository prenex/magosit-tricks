I always use these tricks at multiple places....

# Linear turbo sorting algorithm family

Radix sorting is well known for numbers, but can be done for geometric problems too.
Imagine you want to sort by polar cordinates. You can sort the values usually with 
a qsort, merge sort or whatever sort in O(n logn) time or you could use a hashing 
oriented sort:

- Lets suppose the domain is 0..360 degrees integers
- Create hash buckets for every x degree (every 10 degree for understanding, 360/16 for division = bitshift)
- When adding a value, first add it to the relevant bucket, by dividing the value in 10 and adding to the bucket
- Sort the buckets individually.

If the buckets are small enough there will be always a limited number of elements in them.
For example if we really suppose the domain in the above example is 0..36 integers, then 
having 360 buckets literally solves the problem and we get "bucket count linear sort".

Really similar is if we do radix sorting on the values - should work as well!

# Linear turbo heap

As you can see the above boils down to a heap structure if needed and can be done "online".

In the normal "heap" data structure we have an "ordered set" and find the insertion spot
of the element by binary search - which is O(log n) time per insertion. Heapsort thus do 
its stuff in O(n logn) because we put in n elements (of course the first element will take 
linear time though and the second is pretty easy).

Our algorithm practically helps to make an informed decision when searching to the insertion
point: We can jump to the bucket (or just calculate insertion index directly in some other
implementations) and we know we can insert close to this spot.

We can then either have 36 (=360/10) buckets of regular heaps described above and do the job
much faster than a regular big heap - or we can actually have our linear turbo heap in the 
buckets of our own heap (making it a recursive data structure).

# Performance

With proper setup: Avarage time linear - which is much faster than usual!

Tips:

* For best performance it is best to have as many buckets as it is sensible (maybe 128 or 1024 buckets)
* For best performance use POT values
* For best performance use underlying second level heap that is manually-wired-linked-list in a small array instead of using malloc to allocate list elements.
* The above arrays should be preallocated for all buckets. If the array gets filled up only then go and use a properly linked structure.

For most industrial uses the easy implementation is just hashing into already existing heap implementations.

# Name

I invented this years ago and named PrenexTurboSort and PrenexTurboHeap. Sometimes RadixTurboSorting and such.
