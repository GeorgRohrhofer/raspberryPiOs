#include "memory.h"

static block_header_t *free_list = NULL;

void heap_init() {
  free_list = (block_header_t *)_heap_start;

  free_list->magic = BLOCK_MAGIC;
  free_list->size = _heap_end - _heap_start;
  free_list->next = NULL;
  free_list->is_free = 1;
}

void *kmalloc(size_t size) {
  block_header_t *block = free_list;

  // ALign size to 16 bytes
  size = (size + MEM_ALIGN - 1) & ~(MEM_ALIGN - 1);

  while (block != NULL) {
    if (block->is_free && block->size >= size) {
      if (block->size >= size + BLOCK_HEADER_SIZE + MEM_ALIGN) {
        block_header_t *new_block = (block_header_t *)((u64)block + size + BLOCK_HEADER_SIZE);

        new_block->magic = BLOCK_MAGIC;
        new_block->size = block->size - size - BLOCK_HEADER_SIZE;
        new_block->next = block->next;
        new_block->is_free = 1;

        block->size = size;
        block->next = new_block;
      }

      block->is_free = 0;

      return (void *)((u64)block + BLOCK_HEADER_SIZE);
    }     
    block = block->next;
  }

  // No block found
  return NULL;
}

void kfree(void *ptr) {
  if (ptr == NULL) 
    return;

  block_header_t *block = (block_header_t *)((u64)ptr - BLOCK_HEADER_SIZE);
  if (block->magic != BLOCK_MAGIC) {
    // Heap corruption
    return;
  }

  block->is_free = 1;

  // Merge  adjacent free blocks
  block_header_t *current = free_list;
  while (current != NULL) {
    if (current->is_free && current->next != NULL && current->next->is_free) {
      current->size += current->next->size + BLOCK_HEADER_SIZE;
      current->next = current->next->next;

      continue;
    }

    current = current->next;
  }
}
