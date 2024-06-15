CXX = /usr/bin/g++
CXXFLAGS = -std=c++20 -Wall -fcolor-diagnostics -fansi-escape-codes -g
SRCS = Quote.cpp Bulk_quote.cpp 15p16.cpp
OBJECTS = $(patsubst %.cpp,%.o,$(SRCS))

15p16 : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJECTS) : %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@