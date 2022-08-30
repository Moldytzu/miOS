BINDIR := ../bin
OBJDIR := obj

KERNEL := $(BINDIR)/kernel.elf

# use default c compiler (todo: use a cross compiler)
CC := cc

# use default nasm (todo: use a cross compiler)
LD := ld

# use nasm
ASM := nasm

# User controllable CFLAGS.
CFLAGS ?= -O2 -g

# User controllable LDFLAGS
LDFLAGS ?=

# User controllable ASMFLAGS
ASMFLAGS ?=

# Internal C flags that should not be changed by the user.
INTERNALCFLAGS :=        \
    -std=gnu11           \
    -ffreestanding       \
    -fno-stack-protector \
    -fno-stack-check     \
    -fno-lto             \
    -fno-pie             \
    -fno-pic             \
    -m64                 \
    -march=x86-64        \
    -mabi=sysv           \
    -mno-red-zone        \
    -mcmodel=kernel      \
    -MMD                 \
    -Wall                \
    -O2                  \
    -I.

# Internal linker flags that should not be changed by the user.
INTERNALLDFLAGS :=         \
	-T../linker.ld         \
	-nostdlib              \
	-zmax-page-size=0x1000 \
	-static

# Internal ASM flags that should not be changed by the user.
INTERNALASMFLAGS := \
	-felf64

# Use find to glob all *.c files in the directory and extract the object names.
CFILES := $(shell find . -type f -name '*.c')
ASMFILES := $(shell find . -type f -name '*.asm')
OBJ := $(CFILES:.c=.o)
OBJ += $(ASMFILES:.asm=.o)
HEADER_DEPS := $(CFILES:.c=.d)
HEADER_DEPS += $(ASMFILES:.asm=.d)

# Default target.
.PHONY: all
all: $(KERNEL)

limine.h:
	curl https://raw.githubusercontent.com/limine-bootloader/limine/trunk/limine.h -o $@

# Link rules for the final kernel executable.
$(KERNEL): $(OBJ)
	cd obj && $(LD) $(OBJ) $(LDFLAGS) $(INTERNALLDFLAGS) -o ../$@

# Compilation rules for *.c files.
-include $(HEADER_DEPS)
%.o: %.c limine.h
	@ mkdir -p $(dir $(OBJDIR)/$@)
	$(CC) $(CFLAGS) $(INTERNALCFLAGS) -c $< -o $(OBJDIR)/$@

# Compilation rules for *.asm files.
-include $(HEADER_DEPS)
%.o: %.asm limine.h
	@ mkdir -p $(dir $(OBJDIR)/$@)
	$(ASM) $(ASMFLAGS) $(INTERNALASMFLAGS) $< -o $(OBJDIR)/$@

# Remove object files and the final executable.
.PHONY: clean distclean
clean:
	rm -rf $(KERNEL) $(OBJDIR)

distclean:
	rm -rf limine.h