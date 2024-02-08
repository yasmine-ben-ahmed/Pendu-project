GTK_INCLUDE := $(shell pkg-config --cflags gtk+-3.0)
GTK_LIBS := $(shell pkg-config --libs gtk+-3.0)
GST_INCLUDE := $(shell pkg-config --cflags gstreamer-1.0)
GST_LIBS := $(shell pkg-config --libs gstreamer-1.0)

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
	$(CC) -o $@ $(SRCS) $(GTK_INCLUDE) $(GTK_LIBS) $(GST_INCLUDE) $(GST_LIBS)

# Recipe to clean the workspace
clean:
	rm -f $(EXEC)

.PHONY: all clean

