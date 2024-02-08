# Use pkg-config to get GTK flags and libraries
GTK_FLAGS := $(shell pkg-config --cflags --libs gtk+-3.0)

# Use pkg-config to get GStreamer flags and libraries
GST_FLAGS := $(shell pkg-config --cflags --libs gstreamer-1.0)

# Set the compiler
CC := gcc

# Add header files here
HDRS :=

# Add source files here
SRCS := Main.c

# Name of the executable
EXEC := main

# Default recipe
all: $(EXEC)

# Recipe for building the final executable
$(EXEC): $(SRCS) $(HDRS) Makefile
	@echo "Compiling $(EXEC) successfully..."
	@$(CC) -o $@ $(SRCS) $(GTK_FLAGS) $(GST_FLAGS) >/dev/null 2>&1

# Recipe to clean the workspace
clean:
	rm -f $(EXEC)

.PHONY: all clean

