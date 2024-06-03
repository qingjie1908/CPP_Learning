# SRC_DIRS = ./
# SRCS = 


CXX = /usr/bin/g++
CXXFLAGS = -std=c++20 -Wall -fcolor-diagnostics -fansi-escape-codes -g
# OBJECTS = $(filter %.cpp)

13p44 : ${wildcard *.cpp}
	$(CXX) $(CXXFLAGS) $^ -o $@

# $(wildcard *.o) : $(wildcard *.cpp)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# obj_files = foo.result bar.o lose.o
# src_files = foo.raw bar.c lose.c

# all: $(obj_files)
# # Note: PHONY is important here. Without it, implicit rules will try to build the executable "all", since the prereqs are ".o" files.
# .PHONY: all 

# # Ex 1: .o files depend on .c files. Though we don't actually make the .o file.
# $(filter %.o,$(obj_files)): %.o: %.c
# 	echo "target: $@ prereq: $^"

# # Ex 2: .result files depend on .raw files. Though we don't actually make the .result file.
# $(filter %.result,$(obj_files)) %.result: %.raw
# 	echo "target: $@ prereq: $^" 

# %.c %.raw:
# 	touch $@

# clean:
# 	rm -f $(src_files)
