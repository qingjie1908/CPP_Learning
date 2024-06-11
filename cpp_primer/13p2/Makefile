CXX = /usr/bin/g++
CXXFLAGS = -std=c++20 -Wall -fcolor-diagnostics -fansi-escape-codes -g
SRCS = StrBlob.cpp StrBlobPtr.cpp constStrBlobPtr.cpp StrBlobPtrPtr.cpp 13p26.cpp
OBJECTS = $(patsubst %.cpp,%.o,$(SRCS))

13p26 : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJECTS) : %.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $^ -o $@