CROSS   = aarch64-none-elf-
CC      = $(CROSS)gcc
LD      = $(CROSS)ld
OBJCOPY = $(CROSS)objcopy

CFLAGS  = -Wall -O2 -ffreestanding -nostdlib -nostartfiles -Iinclude
LDFLAGS = -T linker.ld

BUILD   = build

# Quell-Dateien
SRCS = \
  boot/start.S \
  boot/vectors.S \
  kernel/main.c \
  kernel/uart.c \
  kernel/exceptions.c \
  kernel/panic.c \
  kernel/kernel_header.c

# Objekte mit build-Verzeichnis
OBJS = $(SRCS:%.c=$(BUILD)/%.o)
OBJS := $(OBJS:%.S=$(BUILD)/%.o)

# Alle build-Unterverzeichnisse automatisch erzeugen
$(shell mkdir -p $(sort $(dir $(OBJS))))

all: kernel8.img

# Kernel erzeugen
kernel8.img: $(OBJS)
	$(LD) $(LDFLAGS) -o $(BUILD)/kernel.elf $(OBJS)
	$(OBJCOPY) $(BUILD)/kernel.elf -O binary kernel8.img

# Rule für C-Quellen
$(BUILD)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule für ASM-Quellen
$(BUILD)/%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD) kernel8.img

