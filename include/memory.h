#ifndef __MEMORY_H__
#define __MEMORY_H__

#include "types.h"

typedef struct block_header {
  u64 size;
  struct block_header *next;
  u8 is_free;
  u64 magic;
} block_header_t;

#define BLOCK_MAGIC 0xDEADBCAFE // Helps to detect heap corruption
#define BLOCK_HEADER_SIZE sizeof(block_header_t)
#define MEM_ALIGN 16

extern u64 _heap_start;
extern u64 _heap_end;

void heap_init();
void *kmalloc(size_t size);
void *kmalloc_aligned(size_t size, size_t align);
void *kzalloc(size_t size);
void kfree(void *ptr);

// Debug functions
u64 heap_free_space(void);
u64 heap_used_space(void);
void heap_dump(void);

#endif
