# Design Questions PA4

Heap fragmentation occurs when there are many available blocks that are small-sized and not adjacent (so they cannot be coalesced).

Give an example of a program (in C or pseudocode) that sets up a situation where a 20-byte vmalloc call fails to allocate despite the heap having (in total) over 200 bytes free across many blocks. Assume all the policies and layout of the allocator from the PA are used (best fit, alignment, coalescing rules, and so on)

Give an example of a program (in C or pseudocode) where all the allocations succeed if using the best fit allocation policy (like in this PA), but some allocations would fail due to fragmentation if the first fit allocation policy was used instead, keeping everything else the same.

**Reminder** that _all_ of the answers written must be your own.
