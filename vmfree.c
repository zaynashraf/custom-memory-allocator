#include "vm.h"
#include "vmlib.h"

size_t get_curr_status(struct block_header* block) {
     if((block->size_status & 1) == 1) { return 1; }
     return 0;
}

size_t get_prev_status(struct block_header* block) {
      if((block->size_status & 0x2) == 2) { return 1; }
      return 0;
}

size_t get_block_size(struct block_header* block) {
   size_t size = block->size_status & ~0xF;
  
   return size;
}

struct block_header* next_block_addr(struct block_header* start) {
        size_t size = get_block_size(start);
        struct block_header* ptr = (struct block_header*)((char*)start + size);
        return ptr;
}
/**
 * The vmfree() function frees the memory space pointed to by ptr,
 * which must have been returned by a previous call to vmmalloc().
 * Otherwise, or if free(ptr) has already been called before,
 * undefined behavior occurs.
 * If ptr is NULL, no operation is performed.
 */
void vmfree(void *ptr)
{
    if(ptr == NULL) { return; }

	struct block_header* block = (struct block_header*)((char*)ptr - sizeof(struct block_header));
	if(get_curr_status(block) == 0) { return; }

	block->size_status &= ~0x1;
	size_t block_size = get_block_size(block);

	struct block_footer* footer = (struct block_footer*)((char*)block + block_size - sizeof(struct block_footer));
	footer->size = block_size;

	struct block_header* next = next_block_addr(block);
	if(get_curr_status(next) == 0) {
     size_t new_size = block_size + get_block_size(next);
	 block->size_status = new_size | (block->size_status & 0x2);
	 struct block_footer* new_footer = (struct block_footer*)((char*)block + new_size - sizeof(struct block_footer));
	 new_footer->size = new_size;
	 block_size = new_size;
	}

	if(get_prev_status(block) == 0 && block != heapstart) {
     struct block_footer* prev_footer = (struct block_footer*)((char*)block - sizeof(struct block_footer));
     struct block_header* prev_header = (struct block_header*)((char*)block - prev_footer->size);
     
	 size_t new_size = get_block_size(prev_header) + get_block_size(block);
	 prev_header->size_status = new_size | (prev_header->size_status & 0x2);
	 struct block_footer* footer = (struct block_footer*)((char*)prev_header + new_size - sizeof(struct block_footer));
	 footer->size = new_size;
	 block = prev_header;
	 block_size = new_size;
	}

	struct block_header* next_block = next_block_addr(block);
	next_block->size_status &= ~0x2;
}
