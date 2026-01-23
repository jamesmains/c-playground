# Variables to make changes easier later
CC = gcc
CFLAGS = -Wall -g
OBJ = main.o database.o word.o

# The name of your final game
TARGET = hangman

# The "all" rule: this is what happens when you just type 'make'
all: $(TARGET)

# Link the object files together to create the executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compile each .c file into a .o (object) file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the folder (remove compiled files)
clean:
	rm -f $(OBJ) $(TARGET)