# COMMENTS BEGIN WITH A HASH
# THE NAME OF YOUR EXECUTABLE
TARGET = A1

# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp

# NO EDITS NEEDED BELOW THIS LINE
CXX = g++
CXXFLAGS_DEBUG = -g
CXXFLAGS_WARN = -Wall -Wextra -Wconversion -Wdouble-promotion -Wunreachable-code -Wshadow -Wpedantic
CPPVERSION = -std=c++17
OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(shell echo 'Windows'), 'Windows')
	TARGET := $(TARGET).exe
	DEL = del
else
	DEL = rm -f
endif

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

.PHONY: all clean run runclean