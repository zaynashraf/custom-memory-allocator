# Custom Memory Allocator

**Implementation of a dynamic memory allocator in C with best-fit allocation, block splitting, and coalescing.**

---

## Overview
This project simulates a low-level memory allocator similar to `malloc`/`free`. It demonstrates core systems programming concepts including **heap management, pointer arithmetic, memory alignment, fragmentation handling, and block metadata management**.

---

## My Contributions
- Implemented **`vmalloc`** and **`vmfree`** to allocate and free memory dynamically.
- Developed **helper functions** (`vmhelpers.c`) for:  
  - Calculating block size and alignment  
  - Navigating heap blocks with pointer arithmetic  
  - Tracking current and previous block allocation status
- Ensured **16-byte alignment**, correct block headers and footers, and safe heap traversal.
- Managed **coalescing of free blocks** to reduce heap fragmentation and handle dynamic allocation efficiently.

---

## Key Features
- **Best-fit allocation** – selects the smallest free block that fits the requested size.
- **Block splitting** – divides larger free blocks if only part is needed.
- **Coalescing** – merges adjacent free blocks to avoid fragmentation.
- **Metadata management** – headers and footers track block size and allocation status.
- **16-byte alignment** – ensures correct memory alignment for all allocations.

---

- Each block tracks its **size**, **allocation status**, and **previous block status**.
- Allocations are **16-byte aligned**, and free blocks include a **footer** for coalescing.

---

## Testing
- `vmtest.c` includes sample tests that initialize the heap, perform allocations/frees, and display the heap using `vminfo()`.
- The project was originally submitted as part of a **CSE 29 Systems Programming class** assignment.
