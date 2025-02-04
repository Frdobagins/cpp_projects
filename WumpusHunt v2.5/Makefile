# COMMENTS BEGIN WITH A HASH
# THE NAME OF YOUR EXECUTABLE
TARGET = A2

# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = wumpus_main.cpp wumpus_functions.cpp

# NO EDITS NEEDED BELOW THIS LINE
CXX = g++
CXXFLAGS_DEBUG = -g
CXXFLAGS_WARN = -Wall -Wextra -Wconversion -Wdouble-promotion -Wunreachable-code -Wshadow -Wpedantic
CPPVERSION = -std=c++17
OBJECTS = $(SRC_FILES:.cpp=.o)

#ifeq ($(shell echo 'Windows'), 'Windows')
#	TARGET := $(TARGET).exe
#	DEL = del
#else
#	DEL = rm -f
#endif

TARGET := $(TARGET).exe
DEL = del

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^

.cpp.o:
	$(CXX) $(CPPVERSION) $(CXXFLAGS_DEBUG) $(CXXFLAGS_WARN) -o $@ -c $<

clean:
	$(DEL) $(TARGET) $(OBJECTS)

run: $(TARGET)
	./$(TARGET)

runclean: $(TARGET)
	make run
	make clean

gdb: $(TARGET)
	make
	gdb
.PHONY: all clean run runclean gdb