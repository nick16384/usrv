SRC_DIR = src
BUILD_DIR = build
INCLUDE_DIR = include
BIN_DIR = bin
TARGET = $(BIN_DIR)/main

SRC_FILES:=$(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES:=$(SRC_FILES:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)

CC = gcc
CFLAGS = -I$(INCLUDE_DIR) -Wall -Wextra -O2

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)/* $(TARGET)

run-server: all
	$(TARGET) server

run-client: all
	$(TARGET) client

.PHONY: all clean