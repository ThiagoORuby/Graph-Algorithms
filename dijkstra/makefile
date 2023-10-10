CXX = g++
CXXFLAGS = -Wall
SRCS = dijkstra.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = dijkstra

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS) $(EXEC)
