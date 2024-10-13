
CC = gcc

CFLAGS = -Wall -g -Iinclude -Itest_include

TARGET = run

SRC_DIRS = src tests

# Find all .c files in the listed source directories
SRCS = $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))

# Automatically create the list of object files in the build directory
OBJS = $(patsubst %.c, build/%.o, $(SRCS))

# Rule to build the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Rule to compile each .c file into an object file in the build directory
build/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build and target files
.PHONY: clean
clean:
	rm -rf build $(TARGET)

