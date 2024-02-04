GTK_INCLUDE = `pkg-config --cflags gtk+-3.0`
GTK_LIBS = `pkg-config --libs gtk+-3.0`

# Set the compiler
CC := gcc

# Add header files here
HDRS :=

# Add source files here
SRCS := Main.c

# Name of the executable
EXEC := main

# Flags for GTK
GTKFLAGS := $(shell pkg-config --cflags --libs gtk+-3.0)

# Default recipe
all: $(EXEC)

# Recipe for building the final executable
$(EXEC): $(SRCS) $(HDRS) Makefile
	$(CC) -o $@ $(SRCS) $(GTK_INCLUDE) $(GTK_LIBS)

# Recipe to clean the workspace
clean:
	rm -f $(EXEC)

.PHONY: all clean

