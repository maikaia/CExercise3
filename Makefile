# Compiler
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Object files
OBJS = main.o file.o

# Output program name
TARGET = registry

# Default rule
all: $(TARGET)

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Compile each .c file into .o
main.o: main.c file.h types.h
	$(CC) $(CFLAGS) -c main.c

file.o: file.c file.h types.h
	$(CC) $(CFLAGS) -c file.c

# Clean build artifacts
clean:
	rm -f $(OBJS) $(TARGET)
