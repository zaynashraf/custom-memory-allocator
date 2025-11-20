#ifndef VMHELPERS_H
#define VMHELPERS_H

#include "vm.h"

size_t get_curr_status(struct block_header* block);
size_t get_prev_status(struct block_header* block);
size_t get_block_size(struct block_header* block);
struct block_header* next_block_addr(struct block_header* block);
size_t min_block_size(size_t bytes);

#endif
