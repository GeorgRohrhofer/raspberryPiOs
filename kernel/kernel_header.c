#include "kernel.h"

extern u8 _kernel_size[];

__attribute__((section(".kernel_header"), used))
const kernel_header_t kernel_header = {
    .magic0 = KERNEL_MAGIC_0,
    .magic1 = KERNEL_MAGIC_1,
    .version_major = KERNEL_VERSION_MAJOR,
    .version_minor = KERNEL_VERSION_MINOR,
    .version_patch = KERNEL_VERSION_PATCH,
    .header_size = sizeof(kernel_header_t),
    .kernel_size = 0,  /* Filled at runtime or by build tool */
    .flags = 0,
    .checksum = 0
};

int kernel_verify_header(const kernel_header_t *header)
{
    if (!header)
        return -1;

    /* Check primary magic */
    if (header->magic0 != KERNEL_MAGIC_0)
        return -2;

    /* Check secondary magic */
    if (header->magic1 != KERNEL_MAGIC_1)
        return -3;

    /* Check header size matches expected */
    if (header->header_size != sizeof(kernel_header_t))
        return -4;

    return 0;  /* Success */
}

void kernel_get_version(char *buf, u32 buf_size)
{
    if (!buf || buf_size < 12)
        return;

    /* Simple version string: "v0.1.0" */
    buf[0] = 'v';
    buf[1] = '0' + KERNEL_VERSION_MAJOR;
    buf[2] = '.';
    buf[3] = '0' + KERNEL_VERSION_MINOR;
    buf[4] = '.';
    buf[5] = '0' + KERNEL_VERSION_PATCH;
    buf[6] = '\0';
}
