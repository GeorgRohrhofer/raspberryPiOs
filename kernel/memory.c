#include "memory.h"
#include "uart.h"

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

void *kzalloc(size_t size) {
  void *ptr = kmalloc(size);
  if (ptr != NULL) {
    u8 *p = (u8 *)ptr;
    for (size_t i = 0; i < size; i++) {
      p[i] = 0;
    }
  }
  return ptr;
}

u64 heap_free_space() {
  u64 total = 0;
  block_header_t *block = free_list;

  while (block != NULL) {
    if (block->is_free) {
      total += block->size;
    }
    block = block->next;
  }
  
  return total;
}

u64 heap_used_space() {
  return heap_free_space() + (u64)_heap_end - (u64)_heap_start;
}

void heap_dump() {
  block_header_t *block = free_list;
  while (block != NULL) {
    if (block->is_free) {
      uart_puts("Block: 0x");
      uart_puthex((u64)block);
      uart_puts(" Size: ");
      uart_puthex(block->size);
      uart_puts(" Next: 0x");
      uart_puts("\n");
      uart_puthex((u64)(block->next));
    }
    block = block->next;
  }
}
