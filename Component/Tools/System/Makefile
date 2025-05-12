# Directories
TOOL_DIR := D:/Simple_STM32xx_IDE/build/../Component/Tools
include $(TOOL_DIR)/System/Config.mk

DRIVER_DIR    := $(PRO_DIR)/Component
OUTPUT_DIR    := $(PRO_DIR)/Output
PROJ_NAME     := STM32_RUN

# Compiler and linker
CC      := ${TOOL_DIR}/GNU_Toolchain/GCC_NEW/bin/arm-none-eabi-gcc
OBJCOPY := ${TOOL_DIR}/GNU_Toolchain/GCC_NEW/bin/arm-none-eabi-objcopy
CFLAGS  := -mcpu=cortex-m3 -mthumb -Wall -O3 -ffunction-sections -fdata-sections -fstack-usage --specs=nano.specs
LDFLAGS := -T $(LINKER_SCRIPT) -nostartfiles -lc -lgcc -lnosys -Wl,--gc-sections -Wl,-Map=$(OUTPUT_DIR)/firmware.map,--cref

# Startup file (absolute path)
STARTUP_OBJ := $(OUTPUT_DIR)/Startup.o

# Scan all source folders (recursive)
SRC_DIRS := $(PRO_DIR)/main $(wildcard $(DRIVER_DIR)/*)

# Source files
SRC_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.[cS]))

# Object files
PROJ_OBJS := $(patsubst $(PRO_DIR)/%,$(OUTPUT_DIR)/%.o, $(basename $(SRC_FILES)))
OBJS := $(PROJ_OBJS) $(STARTUP_OBJ)

# Include paths
INCLUDE_DIRS := $(foreach dir, $(SRC_DIRS), -I$(dir))
CFLAGS += $(INCLUDE_DIRS)

# Output files
TARGET_ELF := $(OUTPUT_DIR)/$(PROJ_NAME).elf
TARGET_HEX := $(OUTPUT_DIR)/$(PROJ_NAME).hex

# Create output directory
$(shell mkdir -p $(OUTPUT_DIR))

# Default target
all: $(TARGET_HEX)

# Compile C files to objects
$(OUTPUT_DIR)/%.o: $(PRO_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "Compiled $< to $@"

# Compile Assembly files to objects
$(OUTPUT_DIR)/%.o: $(PRO_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "Compiled $< to $@"

# Compile Startup.c explicitly (using absolute path)
$(STARTUP_OBJ): $(STARTUP_FILE)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "Compiled Startup.c to $(STARTUP_OBJ)"

# Link objects into ELF
$(TARGET_ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@
	@echo "Linked objects into $(TARGET_ELF)"

# Convert ELF to HEX
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@
	@echo "Converted $(TARGET_ELF) to $(TARGET_HEX)"

# Flash and Run (for debugging, optional)
.PHONY: run
run:
	$(TOOL_DIR)/ST-LINKUtility/ST-LINK_CLI.exe -ME
	$(TOOL_DIR)/ST-LINKUtility/ST-LINK_CLI.exe -p "$(TARGET_HEX)" 0x08000000
	$(TOOL_DIR)/ST-LINKUtility/ST-LINK_CLI.exe -r32 0x20000000 4 | tee $(OUTPUT_DIR)/debug.log

# Clean build files
.PHONY: clean
clean:
	rm -rf $(OUTPUT_DIR)

# Dependency files
-include $(OBJS:.o=.d)

.PHONY: all clean