# Compiler and flags
WARNING = -Wall -Wshadow --pedantic
ERROR = -Wvla -Werror
GCC = gcc -std=c11 -g $(WARNING) $(ERROR)

# Source and object files
SRCS = main.c
OBJS = $(SRCS:%.c=%.o)

# Target executable
TARGET = window_manager

# Default build target
$(TARGET): $(OBJS)
	$(GCC) $(OBJS) -o $(TARGET)

# Rule to compile source files into object files
%.o: %.c
	$(GCC) -c $< -o $@

# Phony targets
.PHONY: clean test testall

# Test the program by running it
test: $(TARGET)
	./$(TARGET)

# Run the program and save output to a file
test_to_text: $(TARGET)
	./$(TARGET) > results.txt

# Run all test cases and compare with expected outputs
testall: test1 test2 test3 test4

# Individual test case rules
test1: $(TARGET)
	./$(TARGET) < inputs/test1 > output1
	diff -u output1 expected/expected1 || echo "Test 1 Failed!"

test2: $(TARGET)
	./$(TARGET) < inputs/test2 > output2
	diff -u output2 expected/expected2 || echo "Test 2 Failed!"

test3: $(TARGET)
	./$(TARGET) < inputs/test3 > output3
	diff -u output3 expected/expected3 || echo "Test 3 Failed!"

test4: $(TARGET)
	./$(TARGET) < inputs/test4 > output4
	diff -u output4 expected/expected4 || echo "Test 4 Failed!"

# Clean up object files and generated output
clean: 
	rm -f $(TARGET) *.o output* results.txt *~
