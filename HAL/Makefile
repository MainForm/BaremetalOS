include $(PROJECT_PATH)/common.mk

CURRENT_DIR_NAME 	:= $(notdir $(CURDIR))

BUILD_DIR 			:= $(TARGET_BOARD_BUILD_DIR)/$(CURRENT_DIR_NAME)

BOARD_SRC_DIR 		:= $(TARGET_BOARD_PATH)/src

C_SRCS 				:= $(shell find $(BOARD_SRC_DIR) -name '*.c')
C_OBJS 				:= $(C_SRCS:$(BOARD_SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

INCLUDE_FLAG 		:= -Iinclude
INCLUDE_FLAG 		+= -I$(TARGET_BOARD_PATH)/include
INCLUDE_FLAG        += -I$(PERIPHERAL_PATH)/include

all: $(C_OBJS)
	@echo "Build complete for $(CURRENT_DIR_NAME)."

$(C_OBJS): $(BUILD_DIR)/%.o: $(BOARD_SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	
	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) -o $@ $< \
		$(INCLUDE_FLAG)
