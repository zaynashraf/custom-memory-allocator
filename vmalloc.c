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

struct block_header* next_block_addr(struct block_header* start){
    size_t size = get_block_size(start);
    struct block_header* ptr = (struct block_header*)((char*)start + size);
    return ptr;
}

size_t min_block_size(size_t bytes) {
    size_t size = 0;
    if(bytes == 0) { return size; }

    size = bytes + sizeof(size_t);
    while(size % 16 != 0) {
     size += 1;
    }

    return size;
}

void *vmalloc(size_t size)
{
    if(size == 0) { return NULL; }

    size_t required_size = min_block_size(size);

	struct block_header* curr = heapstart;
    struct block_header* best = NULL;
	size_t best_size = SIZE_MAX;

	while(get_block_size(curr) != 0) {
     if(get_curr_status(curr) == 0) {
      size_t curr_size = get_block_size(curr);
	  if(curr_size >= required_size && curr_size < best_size) {
       best = curr;
	   best_size = curr_size;
	  }
	 }
	 curr = next_block_addr(curr);
	}

	if(best == NULL) { return NULL; }

	size_t leftover_bytes = best_size - required_size;

	if(leftover_bytes >= 16) {
     struct block_header* new_block = (struct block_header*)((char*)best + required_size);
     new_block->size_status = leftover_bytes | 0x2;
     
	 struct block_footer* footer = (struct block_footer*)((char*)new_block + leftover_bytes - sizeof(size_t));
	 footer->size = leftover_bytes;

	 best->size_status = required_size | (best->size_status & 0x2);
	}
	else {
	 struct block_header* next = next_block_addr(best);
	 next->size_status |= 0x2;
	}

	best->size_status |= 0x1;
	return (void*)((char*)best + sizeof(struct block_header));

}
