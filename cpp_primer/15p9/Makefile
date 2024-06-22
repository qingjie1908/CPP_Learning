# SHELL := /bin/zsh

TARGET_EXEC := main

CXX := /usr/bin/g++
CXXFLAGS := -std=c++20 -Wall -fcolor-diagnostics -fansi-escape-codes -g
SRC_DIRS := /Users/qingjie/github/CPP_Learning/cpp_primer/15p9

BUILD_DIR := $(SRC_DIRS)

# Find all the C and C++ files we want to compile
# Note the single quotes around the * expressions. The shell will incorrectly expand these otherwise, but we want to send the * directly to the find command.
SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -name '*.cpp' -or -name '*.c')

OBJS := $(patsubst %.cpp,%.o,$(SRCS))

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJS) : %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@