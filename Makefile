ARCH = armv8-a
MCPU = cortex-a72

AS = aarch64-linux-gnu-as
CC = aarch64-linux-gnu-gcc
LD = aarch64-linux-gnu-ld
OBJCOPY = aarch64-linux-gnu-objcopy

SRC_DIR = src
AS_SRCS = $(shell find $(SRC_DIR) -name '*.S')
AS_OBJS = $(AS_SRCS:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.os)

LD_SCRIPT = linker.ld

ASFLAG = -c -g

BUILD_DIR = build
TARGET = image

ELF_FILE = kernel.elf

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(ELF_FILE)
	@mkdir -p $(BUILD_DIR)
	$(OBJCOPY) -O binary $(BUILD_DIR)/$< $(BUILD_DIR)/$@

$(ELF_FILE): $(AS_OBJS)
	@mkdir -p $(BUILD_DIR)
	$(LD) -T $(LD_SCRIPT) -o $(BUILD_DIR)/$@ $^

$(AS_OBJS): $(BUILD_DIR)/%.os: $(SRC_DIR)/%.S
	@mkdir -p $(BUILD_DIR)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) $(ASFLAG) -o $@ $<

clean:
	@rm -rf $(BUILD_DIR)
