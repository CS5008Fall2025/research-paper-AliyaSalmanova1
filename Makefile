

CC = gcc   # which compiler to use
CFLAGS = -Wall  # command line arguments

#source files
TEST_SRC = test.c # list of files to compile to test
RUNNER_SRC = runner.c  # list of files to gather data

# Detect the OS, must use .exe for windows, but can use .out for linux/mac
ifeq ($(OS),Windows_NT)
	EXT = .exe
else
	EXT = .out
endif


test: $(TEST_FILES) 
	$(CC) $(CFLAGS) -O3 -o test$(EXT) $(TEST_SRC) $^

runner: $(RUNNER_FILES)  
	$(CC) $(CFLAGS) -O3 -o runner$(EXT) $(RUNNER_SRC) $^


clean: #clean target - removes all the .exe/.out files, called via "make clean"
	rm  *$(EXT)