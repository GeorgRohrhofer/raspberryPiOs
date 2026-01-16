#ifndef _KERNEL_H
#define _KERNEL_H

#include "types.h"

/* Kernel magic numbers - "RPOS" in ASCII */
#define KERNEL_MAGIC_0      0x52504F53  /* "RPOS" */
#define KERNEL_MAGIC_1      0xDEADBEEF  /* Secondary validation */

/* Kernel version */
#define KERNEL_VERSION_MAJOR    0
#define KERNEL_VERSION_MINOR    1
#define KERNEL_VERSION_PATCH    0

/* Kernel header structure - placed at start of kernel image */
typedef struct {
    u32 magic0;             /* Primary magic number */
    u32 magic1;             /* Secondary magic number */
    u32 version_major;
    u32 version_minor;
    u32 version_patch;
    u32 header_size;        /* Size of this header */
    u64 kernel_size;        /* Total kernel image size */
    u32 flags;              /* Reserved for future use */
    u32 checksum;           /* Reserved for future checksum */
} kernel_header_t;

/* Verify kernel header integrity */
int kernel_verify_header(const kernel_header_t *header);

/* Get kernel version string */
void kernel_get_version(char *buf, u32 buf_size);

#endif
