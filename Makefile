# Compiler
CC = gcc

# Flags
CFLAGS = -Wall -Wextra -I./include -g

# Directories
SRC_DIR = src
BUILD_DIR = build

# Sources
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Objects
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Output binary
TARGET = $(BUILD_DIR)/flux

# Default target
all: $(BUILD_DIR) $(TARGET)

# Create build directory if not exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Build target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build objects
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean

