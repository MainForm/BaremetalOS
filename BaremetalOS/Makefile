include $(PROJECT_PATH)/common.mk

CURRENT_DIR_NAME 	:= $(notdir $(CURDIR))

BUILD_DIR 			:= $(TARGET_BOARD_BUILD_DIR)/$(CURRENT_DIR_NAME)

SRC_DIR 			:= $(OS_PATH)/src
KERNEL_ARCH_DIR 	:= $(SRC_DIR)/arch/$(KERNEL_ARCH)

ARCH_AS_SRCS 	    := $(shell find $(SRC_DIR)/arch/$(KERNEL_ARCH) -name '*.S')
ARCH_AS_OBJS 	    := $(ARCH_AS_SRCS:$(SRC_DIR)/%.S=$(BUILD_DIR)/%.os)

ARCH_C_SRCS 	    := $(shell find $(SRC_DIR)/arch/$(KERNEL_ARCH) -name '*.c')
ARCH_C_OBJS 	    := $(ARCH_C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

KERNEL_C_SRCS 	    := $(shell find $(SRC_DIR)/kernel -name '*.c')
KERNEL_C_OBJS 	    := $(KERNEL_C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

LIB_C_SRCS 	    	:= $(shell find $(SRC_DIR)/lib -name '*.c')
LIB_C_OBJS 	    	:= $(LIB_C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

AS_OBJS 			:= $(ARCH_AS_OBJS)
C_OBJS 				:= $(ARCH_C_OBJS) $(KERNEL_C_OBJS) $(LIB_C_OBJS)

INCLUDE_FLAG		:= -I$(HAL_PATH)/include
INCLUDE_FLAG		+= -I$(OS_PATH)/include

all: $(AS_OBJS) $(C_OBJS)
	@echo "Build complete for $(CURRENT_DIR_NAME)."

$(AS_OBJS): $(BUILD_DIR)/%.os: $(SRC_DIR)/%.S
	@mkdir -p $(dir $@)
	$(AS) -march=$(ARCH) -mcpu=$(MCPU) $(ASFLAG) -o $@ $<

$(C_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) -o $@ $< \
		$(INCLUDE_FLAG)

