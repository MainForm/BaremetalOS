include $(PROJECT_PATH)/common.mk

CURRENT_DIR_NAME 	:= $(notdir $(CURDIR))

BUILD_DIR 			:= $(TARGET_BOARD_BUILD_DIR)/$(CURRENT_DIR_NAME)
SRC_DIR 			:= $(PERIPHERAL_PATH)/src

# Search the peripheral to be built depending ont the TAREGET_BOARD
C_SRCS 				:= $(foreach peripheral,$(PERIPHERAL_NAMES),$(shell find $(PERIPHERAL_PATH) -path '*/$(peripheral)/*' -name '*.c'))
C_OBJS 				:= $(C_SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

all: $(C_OBJS)
	@echo "Build complete for $(CURRENT_DIR_NAME)."

$(C_OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)

	$(CC) -march=$(ARCH) -mcpu=$(MCPU) $(CFLAG) -o $@ $< \
		-Iinclude