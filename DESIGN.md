# Design Questions PA4

Heap fragmentation occurs when there are many available blocks that are small-sized and not adjacent (so they cannot be coalesced).

Give an example of a program (in C or pseudocode) that sets up a situation where a 20-byte vmalloc call fails to allocate despite the heap having (in total) over 200 bytes free across many blocks. Assume all the policies and layout of the allocator from the PA are used (best fit, alignment, coalescing rules, and so on)

Give an example of a program (in C or pseudocode) where all the allocations succeed if using the best fit allocation policy (like in this PA), but some allocations would fail due to fragmentation if the first fit allocation policy was used instead, keeping everything else the same.

**Reminder** that _all_ of the answers written must be your own.



Q1: An example where a 20 byte malloc wouldn't work is one where the heap is fragmented into a series of free and allocated blocks such that there isn't enough space to allocate. Let's say we have a heap with one initial block of 480 usable bytes (excluding padding and endmark). Here is some pseudocode:

void *a = vmalloc(5); // Required size is 5 + 8 = 13, then round 13 up to nearest number divisble by 16, which is 16. Total free bytes left: 464
void *b = vmalloc(5); // Block size: 16. Total free bytes left: 448
void *c = vmalloc(5); // Block size: 16. Total free bytes left: 432
/... 

// This trend continues for 30 blocks until we reach the end of our usable memory. There will be 30 blocks in total. 30 * 16 = 480.

// Now, we free every other block.

vmfree(b); // 16 bytes freed
vmfree(d); // 16 bytes freed
/...

// This trend continues until we free every other block. 

// The final heap will contain a series of blocks where a block is allocated for 16 bytes, then followed up with a block that has 16 free bytes, and that trend is continued until the end of the heap.


void *test = vmalloc(20); // Required size is 20 + 8, then round up to nearest number divisble by 16, which is 32. However, because there isn't enough free space available in any individual block (the max amount of bytes every block contains is 16), vmalloc will fail and return NULL. Total free memory is 16 * 15 = 240 (more than 200 bytes), but vmalloc will fail because no individual block is large enough. 






Q2: Okay, let's say we have a heap with one initial free block of 128 usable bytes (excluding padding and endmark). Here's an example:

void *a = vmalloc(15); // Block size: 32. Total free bytes left: 96
void *b = vmalloc(15); // Block size: 32. Total free bytes left: 64
void *c = vmalloc(5); // Block size: 16. Total free bytes left: 48

vmfree(b); // Free 32 bytes

// So we have two free blocks here. The first block has 32 bytes and the second block (right before the end of the heap) has 48 bytes. Onto the test:

void *test1 = vmalloc(5); // Block size: 16
void *test2 = vmalloc(15); // Block size: 32
void *test3 = vmalloc(15); // Block size: 32

// Assuming we're using best-fit for malloc, it will first allocate a 16 byte block where the 48 byte free block is, leaving 32 free bytes there. It will then allocate 32 bytes where the first free block was, and finally it will allocate the last 32 bytes to where the second 32 byte block is.

// Assuming we're using first-fit for malloc, it will first allocate a 16 byte block where the 32 byte free block is, leaving 16 free bytes there. It will then allocate 32 bytes where the second free block was, leaving 16 free bytes there. However, it won't be able to allocate the last 32 bytes because the two 16 byte blocks remaining are in different places in the heap. There is no block large enough to contain the 32 bytes it wants to allocate. 


