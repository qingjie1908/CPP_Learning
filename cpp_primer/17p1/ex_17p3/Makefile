CPPFLAGS := -std=c++20 -Wall -fcolor-diagnostics -fansi-escape-codes -g
CXX := /usr/bin/g++
SRC_DIRS := /Users/qingjie/github/CPP_Learning/cpp_primer/17p1/ex_17p3
BUILD_DIR := $(SRC_DIRS)

TARGET_EXEC := 17p3


SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -name '*'.cpp -or -name '*'.c)
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

$(BUILD_DIR)/$(TARGET_EXEC) : $(OBJS)
	$(CXX) $(CPPFLAGS) $^ -o $(TARGET_EXEC)

$(OBJS) : %.o : %.cpp
	$(CXX) $(CPPFLAGS) -c $^ -o $@
# $(OBJS) : $(SRCS)
# 	$(CXX) $(CPPFLAGS) -c $^ -o $@