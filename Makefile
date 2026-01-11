CROSS   = aarch64-none-elf-
CC      = $(CROSS)gcc
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS  = -Wall -O2 -ffreestanding -nostdlib -nostartfiles \
          -Iinclude

LDFLAGS = -T linker.ld

BUILD   = build

SRCS = \
  boot/start.S \
  kernel/main.c \
  kernel/uart.c

OBJS = $(SRCS:%=$(BUILD)/%.o)

all: kernel8.img

kernel8.img: $(OBJS)
	$(LD) $(LDFLAGS) -o $(BUILD)/kernel.elf $(OBJS)
	$(OBJCOPY) $(BUILD)/kernel.elf -O binary kernel8.img

# C source
$(BUILD)/%.c.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# ASM source
$(BUILD)/%.S.o: %.S
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) kernel8.img

