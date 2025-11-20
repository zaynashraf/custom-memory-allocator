#include "vmhelpers.h"

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
