# Directories
PRO_DIR       := .
DRIVER_DIR    := $(PRO_DIR)/Component
OUTPUT_DIR    := $(PRO_DIR)/Output
LINKER_SCRIPT := $(PRO_DIR)/main/stm32f103xx_Linker.ld
PROJ_NAME     := STM32_RUN

# Compiler and linker
CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
CFLAGS  := -mcpu=cortex-m3 -mthumb -Wall -O3 -ffunction-sections -fdata-sections -fstack-usage --specs=nano.specs
LDFLAGS := -T $(LINKER_SCRIPT) -nostartfiles -lc -lgcc -lnosys -Wl,--gc-sections -Wl,-Map=$(OUTPUT_DIR)/firmware.map,--cref

# Scan all source folders (recursive)
SRC_DIRS := $(PRO_DIR)/main $(wildcard $(DRIVER_DIR)/*)

# Source files
SRC_FILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.[cS]))

# Object files
OBJS := $(patsubst $(PRO_DIR)/%,$(OUTPUT_DIR)/%.o, $(basename $(SRC_FILES)))

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

# Compile C and Assembly files to objects
$(OUTPUT_DIR)/%.o: $(PRO_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(OUTPUT_DIR)/%.o: $(PRO_DIR)/%.S
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

# Link objects into ELF
$(TARGET_ELF): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $@

# Convert ELF to HEX
$(TARGET_HEX): $(TARGET_ELF)
	$(OBJCOPY) -O ihex $< $@

# Flash and Run (for debugging, optional)
.PHONY: run
run:
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -ME
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -p "$(TARGET_HEX)" 0x08000000
	$(PRO_DIR)/debug/ST-LINKUtility/ST-LINK_CLI.exe -r32 0x20000000 4 | tee $(OUTPUT_DIR)/debug.log

# Clean build files
.PHONY: clean
clean:
	rm -rf $(OUTPUT_DIR)

# Dependency files
-include $(OBJS:.o=.d)

.PHONY: all clean
