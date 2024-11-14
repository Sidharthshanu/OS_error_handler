CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
SIM_DIR = src/simulations
BUILD_DIR = build
LOG_DIR = logs

# Create necessary directories
$(shell mkdir -p $(BUILD_DIR) $(LOG_DIR))

# Source files
SRC_FILES = $(SRC_DIR)/logger.c \
            $(SRC_DIR)/reporter.c \
            $(SRC_DIR)/recovery.c \
            $(SRC_DIR)/error_handler.c

SIM_FILES = simulate_memory_error simulate_file_error simulate_device_error

# Compile all simulations
all: $(SIM_FILES)

simulate_memory_error: $(SIM_DIR)/simulate_memory_error.c $(SRC_FILES)
        $(CC) $(CFLAGS) $(SIM_DIR)/simulate_memory_error.c $(SRC_FILES) -o $(BUILD_DIR)/simulate_memory_error

simulate_file_error: $(SIM_DIR)/simulate_file_error.c $(SRC_FILES)
        $(CC) $(CFLAGS) $(SIM_DIR)/simulate_file_error.c $(SRC_FILES) -o $(BUILD_DIR)/simulate_file_error

simulate_device_error: $(SIM_DIR)/simulate_device_error.c $(SRC_FILES)
        $(CC) $(CFLAGS) $(SIM_DIR)/simulate_device_error.c $(SRC_FILES) -o $(BUILD_DIR)/simulate_device_error

clean:
        rm -rf $(BUILD_DIR)/*

.PHONY: all clean